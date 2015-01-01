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

#define KBC_STATUS 0x64
#define KBC_BUFFER 0x60

void kbc_init()
{
    while (inb(KBC_STATUS) & 0x01)
	inb(0x60);

    while (inb(KBC_STATUS) & 0x02);
    outb(KBC_BUFFER, 0xf4);
}

/* Called before platform-independent kernel initialization */
void arch_init(void)
{
    gdt_init();
    idt_init();
    timer_init(TIMER_HZ);
    //kbc_init();
}

/* Called after platform-independent kernel initialization */
void arch_start(void)
{
    asm volatile("sti");
}
