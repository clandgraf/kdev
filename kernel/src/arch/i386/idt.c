/*
 * File:    kernel/src/arch/i386
 * Author:  Christoph Landgraf
 * Purpose: Definitions for setting up the IDT.
 */

#include <stdint.h>

#define IDT_TYPE_INT_16  0x6
#define IDT_TYPE_TRAP_16 0x7
#define IDT_TYPE_TASK_32 0x5
#define IDT_TYPE_INT_32  0xe
#define IDT_TYPE_TRAP_32 0xf

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

struct idt_entry idt[32];
struct idt_ptr   idtp;

extern void idt_flush(void);

void idt_set_gate(int idx, uint32_t base, uint16_t selector, uint8_t gate_type, uint8_t attributes)
{
    idt[idx].base_lo   = base & 0xffff;
    idt[idx].base_hi   = (base >> 16) & 0xffff;
    idt[idx].selector  = selector;
    idt[idx].type_attr = (attributes << 4) | gate_type;
    idt[idx].zero      = (uint8_t) 0x0;
}


#include "idt_isr_defs.h"
#define IDT_DEFFAULT(idx, fn) (idt_set_gate(idx, (uint32_t) &fn, 0x08, IDT_TYPE_INT_32, 0x8))


void itest(void) 
{ 
    printf("Received Interrupt!");
    while (1); 
}


void idt_init(void)
{
    idtp.lmt  = sizeof(struct idt_entry) * 32 - 1;
    idtp.base = &idt[0];

    /* Setup gates for hardware faults */
    IDT_DEFFAULT(0, isr0);  IDT_DEFFAULT(1, isr1);  IDT_DEFFAULT(2, isr2);  IDT_DEFFAULT(3, isr3);
    IDT_DEFFAULT(4, isr4);  IDT_DEFFAULT(5, isr5);  IDT_DEFFAULT(6, isr6);  IDT_DEFFAULT(7, isr7);
    IDT_DEFFAULT(8, isr8);  IDT_DEFFAULT(9, isr9);  IDT_DEFFAULT(10,isr10); IDT_DEFFAULT(11,isr11);
    IDT_DEFFAULT(12,isr12); IDT_DEFFAULT(13,isr13); IDT_DEFFAULT(14,isr14); IDT_DEFFAULT(15,isr15);
    IDT_DEFFAULT(16,isr16); IDT_DEFFAULT(17,isr17); IDT_DEFFAULT(18,isr18); IDT_DEFFAULT(19,isr19);
    IDT_DEFFAULT(20,isr20); IDT_DEFFAULT(21,isr21); IDT_DEFFAULT(22,isr22); IDT_DEFFAULT(23,isr23);
    IDT_DEFFAULT(24,isr24); IDT_DEFFAULT(25,isr25); IDT_DEFFAULT(26,isr26); IDT_DEFFAULT(27,isr27);
    IDT_DEFFAULT(28,isr28); IDT_DEFFAULT(29,isr29); IDT_DEFFAULT(30,isr30); IDT_DEFFAULT(31,isr31);

    idt_flush();
}
