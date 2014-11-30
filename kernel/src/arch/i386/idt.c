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
    idt[idx].type_attr = (attributes << 4) & gate_type;
    idt[idx].zero      = (uint8_t) 0x0;
}

#include "idt_isr_defs.h"
#define IDT_DEFFAULT(fn) (idt_set_gate(0, (uint32_t) &fn, 0x08, IDT_TYPE_INT_32, 0x8))

void idt_init(void)
{
    idtp.lmt  = sizeof(struct idt_entry) * 32 - 1;
    idtp.base = &idt[0];

    /* Setup gates for hardware faults */
    IDT_DEFFAULT(isr0);  IDT_DEFFAULT(isr1);  IDT_DEFFAULT(isr2);  IDT_DEFFAULT(isr3);
    IDT_DEFFAULT(isr4);  IDT_DEFFAULT(isr5);  IDT_DEFFAULT(isr6);  IDT_DEFFAULT(isr7);
    IDT_DEFFAULT(isr8);  IDT_DEFFAULT(isr9);  IDT_DEFFAULT(isr10); IDT_DEFFAULT(isr11);
    IDT_DEFFAULT(isr12); IDT_DEFFAULT(isr13); IDT_DEFFAULT(isr14); IDT_DEFFAULT(isr15);
    IDT_DEFFAULT(isr16); IDT_DEFFAULT(isr17); IDT_DEFFAULT(isr18); IDT_DEFFAULT(isr19);
    IDT_DEFFAULT(isr20); IDT_DEFFAULT(isr21); IDT_DEFFAULT(isr22); IDT_DEFFAULT(isr23);
    IDT_DEFFAULT(isr24); IDT_DEFFAULT(isr25); IDT_DEFFAULT(isr26); IDT_DEFFAULT(isr27);
    IDT_DEFFAULT(isr28); IDT_DEFFAULT(isr29); IDT_DEFFAULT(isr30); IDT_DEFFAULT(isr31);

    idt_flush();
}
