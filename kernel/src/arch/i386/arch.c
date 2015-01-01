/*
 *
 * File:    kernel/src/arch/i386/arch.c
 * Author:  Christoph Landgraf
 * Purpose: Architecture initialization implementation 
 *          for the i386 architecture.
 *
 */

#include <kernel/arch/i386/io.h>
#include <kernel/config.h>

extern void gdt_init(void);            /* kernel/src/arch/i386/gdt.c */
extern void idt_init(void);            /* kernel/src/arch/i386/idt.c */
extern void timer_init(uint32_t freq); /* kernel/src/arch/i386/timer.c */
extern void kbc_init(void);            /* kernel/src/arch/i386/kbc.c */

/* Called before platform-independent kernel initialization */
void arch_init(void)
{
    gdt_init();
    idt_init();
    timer_init(TIMER_HZ);
    kbc_init();
}

/* Called after platform-independent kernel initialization */
void arch_start(void)
{
    asm volatile("sti");
}
