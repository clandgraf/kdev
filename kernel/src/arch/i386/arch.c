/*
 *
 * File:    kernel/src/arch/i386/arch.c
 * Author:  Christoph Landgraf
 * Purpose: Architecture initialization implementation 
 *          for the i386 architecture.
 *
 */

#include <kernel/arch/i386/io.h>

extern void gdt_init(void);
extern void idt_init(void);
extern void timer_init(uint32_t frequency);

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
    timer_init(20);
    //kbc_init();
}

/* Called after platform-independent kernel initialization */
void arch_start(void)
{
    asm volatile("sti");
}
