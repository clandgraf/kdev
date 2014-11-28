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
    
} __attribute((packed))__;

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
    idt[idx].selector  = selector
    idt[idx].type_attr = (attributes << 4) & gate_type
    idt[idx].zero      = (uint8_t) 0x0;
}

extern void isr00(void);
// ...

void idt_init(void)
{
    idtp.lmt  = sizeof(idt_entry) * 32 - 1;
    idtp.base = &idt[0];

    idt_set_gate(0,  &isr00, 0x08, IDT_TYPE_INT_32, 0x8);
    idt_set_gate(1,  &isr01, 0x08, IDT_TYPE_INT_32, 0x8);
    idt_set_gate(2,  &isr02, 0x08, IDT_TYPE_INT_32, 0x8);
    idt_set_gate(3,  &isr03, 0x08, IDT_TYPE_INT_32, 0x8);
    idt_set_gate(4,  &isr04, 0x08, IDT_TYPE_INT_32, 0x8);
    idt_set_gate(5,  &isr05, 0x08, IDT_TYPE_INT_32, 0x8);
    idt_set_gate(6,  &isr06, 0x08, IDT_TYPE_INT_32, 0x8);
    idt_set_gate(7,  &isr07, 0x08, IDT_TYPE_INT_32, 0x8);
    idt_set_gate(8,  &isr08, 0x08, IDT_TYPE_INT_32, 0x8);
    idt_set_gate(9,  &isr09, 0x08, IDT_TYPE_INT_32, 0x8);
    idt_set_gate(10, &isr10, 0x08, IDT_TYPE_INT_32, 0x8);
    idt_set_gate(11, &isr11, 0x08, IDT_TYPE_INT_32, 0x8);
    idt_set_gate(12, &isr12, 0x08, IDT_TYPE_INT_32, 0x8);
    idt_set_gate(13, &isr13, 0x08, IDT_TYPE_INT_32, 0x8);
    idt_set_gate(14, &isr14, 0x08, IDT_TYPE_INT_32, 0x8);
    idt_set_gate(15, &isr15, 0x08, IDT_TYPE_INT_32, 0x8);
    idt_set_gate(16, &isr16, 0x08, IDT_TYPE_INT_32, 0x8);
    idt_set_gate(17, &isr17, 0x08, IDT_TYPE_INT_32, 0x8);
    idt_set_gate(18, &isr18, 0x08, IDT_TYPE_INT_32, 0x8);
    idt_set_gate(19, &isr19, 0x08, IDT_TYPE_INT_32, 0x8);
    idt_set_gate(20, &isr20, 0x08, IDT_TYPE_INT_32, 0x8);
    idt_set_gate(21, &isr21, 0x08, IDT_TYPE_INT_32, 0x8);
    idt_set_gate(22, &isr22, 0x08, IDT_TYPE_INT_32, 0x8);
    idt_set_gate(23, &isr23, 0x08, IDT_TYPE_INT_32, 0x8);
    idt_set_gate(24, &isr24, 0x08, IDT_TYPE_INT_32, 0x8);
    idt_set_gate(25, &isr25, 0x08, IDT_TYPE_INT_32, 0x8);
    idt_set_gate(26, &isr26, 0x08, IDT_TYPE_INT_32, 0x8);
    idt_set_gate(27, &isr27, 0x08, IDT_TYPE_INT_32, 0x8);
    idt_set_gate(28, &isr28, 0x08, IDT_TYPE_INT_32, 0x8);
    idt_set_gate(29, &isr29, 0x08, IDT_TYPE_INT_32, 0x8);
    idt_set_gate(30, &isr30, 0x08, IDT_TYPE_INT_32, 0x8);
    idt_set_gate(31, &isr31, 0x08, IDT_TYPE_INT_32, 0x8);

    idt_flush();
}
