/*
 *
 * File:    kernel/src/arch/i386/arch.c
 * Author:  Christoph Landgraf
 * Purpose: Architecture initialization implementation 
 *          for the i386 architecture.
 *
 */

#include <kernel/arch/i386/io.h>
#include <kernel/arch/i386/irq.h>

extern void gdt_init(void);
extern void idt_init(void);

#define KBC_STATUS 0x64
#define KBC_BUFFER 0x60

void kbc_init()
{
    while (inb(KBC_STATUS) & 0x01)
	inb(0x60);

    while (inb(KBC_STATUS) & 0x02);
    outb(KBC_BUFFER, 0xf4);
}

#define PIT_BASE   1193180
#define PIT_CMD    0x43
#define PIT_CNT_0  0x40

#include <stdio.h>
void timer_handler(uint8_t irq)
{
    printf("Timer: %d\n", irq);
}

void timer_init(uint32_t frequency)
{
   uint32_t divisor = PIT_BASE / frequency;

   // Send the command byte.
   outb(PIT_CMD, 0x36);

   // Divisor has to be sent byte-wise, so split here into upper/lower bytes.
   uint8_t l = (uint8_t)(divisor & 0xFF);
   uint8_t h = (uint8_t)((divisor>>8) & 0xFF);

   // Send the frequency divisor.
   outb(PIT_CNT_0, l);
   outb(PIT_CNT_0, h);

   // Setup Timer IRQ Handler
   irq_register_handler(0x20, &timer_handler);
}

/* Call before platform-independent kernel initialization */
void arch_init(void)
{
    gdt_init();
    idt_init();
    timer_init(1);
    //kbc_init();
}

/* Call after platform-independent kernel initialization */
void arch_start(void)
{
    asm volatile("sti");
}
