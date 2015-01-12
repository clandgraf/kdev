/*
 * File:    kernel/src/arch/x86/idt.c
 * Author:  Christoph Landgraf
 * Purpose: Definitions for setting up the IDT.
 */

#include <stdint.h>
#include <stdlib.h>
#include <kernel/arch/x86/io.h>
#include <kernel/arch/x86/irq.h>
#include <kernel/arch/x86/cpu_state.h>
#include <kernel/klog.h>
#include <kernel/panic.h>

/* IDT Parameters */
#define IDT_TYPE_INT_16  0x6
#define IDT_TYPE_TRAP_16 0x7
#define IDT_TYPE_TASK_32 0x5
#define IDT_TYPE_INT_32  0xe
#define IDT_TYPE_TRAP_32 0xf

/* IRQ IO Ports */
#define IRQ_MASTER_CTRL  0x20
#define IRQ_MASTER_DATA  0x21
#define IRQ_SLAVE_CTRL   0xa0
#define IRQ_SLAVE_DATA   0xa1

/* IRQ ICW1 */
#define IRQ_ICW1_ICW4    0x01
#define IRQ_ICW1_SINGLE  0x02
#define IRQ_ICW1_INIT    0x10

/* IRQ ICW4 */
#define IRQ_ICW4_PC      0x01
#define IRQ_ICW4_AUTOEOI 0x02

/* IRQ Commands */
#define IRQ_CMD_RESET    0x20


/* CPU Exceptions */
#define EXC_DIV_BY_ZERO  0x00
#define EXC_DEBUG        0x01
#define EXC_NMI          0x02
#define EXC_BREAK        0x03
#define EXC_OVERFLOW     0x04
#define EXC_BOUND_RANGE  0x05
#define EXC_INVALID_OPC  0x06

#define EXC_DOUBLE_FAULT 0x08

const char * exception_strings[] = {
    "Divide By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Overflow",
    "Bound Range",
    "Invalid Opcode",
    NULL,
    "Double Fault",
};


struct idt_entry {
    uint16_t base_lo;
    uint16_t selector;
    uint8_t  zero;
    uint8_t  type_attr;
    uint16_t base_hi;   
};

struct idt_ptr {
    uint16_t lmt;
    void * base;

} __attribute__((packed));

#define IDT_SIZE 48

struct idt_entry idt[IDT_SIZE];
struct idt_ptr   idtp;

extern void idt_flush(void);


void fault_panic(uint8_t irq)
{
    klog_info("Unhandled Hardware Fault! IRQ 0x%x\n", irq);

    const char * exc = exception_strings[irq];
    if (exc)
	klog_info("%s\n", irq);

    panic();
}


void idt_set_gate(int idx, uint32_t base, uint16_t selector, uint8_t gate_type, uint8_t attributes)
{
    idt[idx].base_lo   = base & 0xffff;
    idt[idx].base_hi   = (base >> 16) & 0xffff;
    idt[idx].selector  = selector;
    idt[idx].type_attr = (attributes << 4) | gate_type;
    idt[idx].zero      = (uint8_t) 0x0;
}


#include "idt_isr_defs.h"
#define IDT_DEFFAULT(idx) (idt_set_gate(idx, (uint32_t) &isr##idx, 0x08, IDT_TYPE_INT_32, 0x8))


void idt_init(void)
{
    /* Remap PIC */
    outb(IRQ_MASTER_CTRL, IRQ_ICW1_INIT | IRQ_ICW1_ICW4);
    outb(IRQ_MASTER_DATA, 0x20); // Masters IRQs start with 0x20
    outb(IRQ_MASTER_DATA, 0x04); // Bitmask: Line 2 has Slave IRQs
    outb(IRQ_MASTER_DATA, IRQ_ICW4_PC);

    outb(IRQ_SLAVE_CTRL, IRQ_ICW1_INIT | IRQ_ICW1_ICW4);
    outb(IRQ_SLAVE_DATA, 0x28); // Slave IRQs start with 0x28
    outb(IRQ_SLAVE_DATA, 0x02); // Slave is connected to Master line 2
    outb(IRQ_SLAVE_DATA, 0x01);

    /* Demask IRQs */
    outb(IRQ_MASTER_CTRL, 0x00);
    outb(IRQ_SLAVE_CTRL,  0x00);

    /* Setup IDT */
    idtp.lmt  = sizeof(struct idt_entry) * IDT_SIZE - 1;
    idtp.base = &idt[0];

    /* Setup gates for hardware faults */
    IDT_DEFFAULT(0);  IDT_DEFFAULT(1);  IDT_DEFFAULT(2);  IDT_DEFFAULT(3);
    IDT_DEFFAULT(4);  IDT_DEFFAULT(5);  IDT_DEFFAULT(6);  IDT_DEFFAULT(7);
    IDT_DEFFAULT(8);  IDT_DEFFAULT(9);  IDT_DEFFAULT(10); IDT_DEFFAULT(11);
    IDT_DEFFAULT(12); IDT_DEFFAULT(13); IDT_DEFFAULT(14); IDT_DEFFAULT(15);
    IDT_DEFFAULT(16); IDT_DEFFAULT(17); IDT_DEFFAULT(18); IDT_DEFFAULT(19);
    IDT_DEFFAULT(20); IDT_DEFFAULT(21); IDT_DEFFAULT(22); IDT_DEFFAULT(23);
    IDT_DEFFAULT(24); IDT_DEFFAULT(25); IDT_DEFFAULT(26); IDT_DEFFAULT(27);
    IDT_DEFFAULT(28); IDT_DEFFAULT(29); IDT_DEFFAULT(30); IDT_DEFFAULT(31);

    /* Setup gates for IRQs */
    IDT_DEFFAULT(32); IDT_DEFFAULT(33); IDT_DEFFAULT(34); IDT_DEFFAULT(35);
    IDT_DEFFAULT(36); IDT_DEFFAULT(37); IDT_DEFFAULT(38); IDT_DEFFAULT(39);
    IDT_DEFFAULT(40); IDT_DEFFAULT(41); IDT_DEFFAULT(42); IDT_DEFFAULT(43);
    IDT_DEFFAULT(44); IDT_DEFFAULT(45); IDT_DEFFAULT(46); IDT_DEFFAULT(47);

    /* Update IDT Register */
    idt_flush();

    /* Install Handler for Hardware Faults */
    irq_register_handler(EXC_DIV_BY_ZERO,  &fault_panic);
    irq_register_handler(EXC_DOUBLE_FAULT, &fault_panic);
}


/*
   In the Interrupt Handler Stubs first an error code,
   then the Interrupt Number is pushed.

   The pusha instruction pushes eax first, so it 
   is the last field in the cpu_state structure.
 */

irq_handler_t irq_handlers[0x100] = {
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,

    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
};

extern cpu_state_t * task_sched(cpu_state_t * new_state);

cpu_state_t * isr_dispatch(cpu_state_t * cpu_state)
{
    klog_debug("Received Interrupt %x: Error %x!\n", cpu_state->intr, cpu_state->err);
    
    /* Reset PIC */
    if (cpu_state->intr >= 0x20 && cpu_state->intr <= 0x2f) {
	if (cpu_state->intr >= 0x28)
	    outb(IRQ_SLAVE_CTRL, IRQ_CMD_RESET);

	outb(IRQ_MASTER_CTRL, IRQ_CMD_RESET);
    }

    /* Invoke Interrupt Handler */
    irq_handler_t handler = irq_handlers[cpu_state->intr];
    if (handler)
	handler(cpu_state->intr);

    /* Switch task */
    if (cpu_state->intr == IRQ_PIT)
	return task_sched(cpu_state);

    return cpu_state;
}

void irq_register_handler(uint8_t irq, irq_handler_t handler)
{
    irq_handlers[irq] = handler;
}
