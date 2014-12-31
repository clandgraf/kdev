/*
 *
 * File:    kernel/src/arch/i386/timer.c
 * Author:  Christoph Landgraf
 * Purpose: Initialization of PIT and IRQ handler for PIT Interrupt
 *
 */

#include <kernel/arch/i386/io.h>
#include <kernel/arch/i386/irq.h>

/* Registers */
#define PIT_COMMAND   0x43 /* Command Register */
#define PIT_CNT_CHAN0 0x40 /* Set Counter for Channels 0-2 */
#define PIT_CNT_CHAN1 0x41
#define PIT_CNT_CHAN2 0x42

/* Base Frequency */
#define PIT_BASE   1193180

/* Initialization Flags */
#define PIT_FORMAT_BIN   0x00        /* Bit 0:   Format is Binary */
#define PIT_FORMAT_BCD   0x01        /*          Format is Binary Coded Decimal */
#define PIT_MODE(m)      (m << 1)    /* Bit 1-3: Mode 0-5 */
#define PIT_SET_INTERNAL (0x00 << 4) /* Bit 4-5: Counter is in internal register*/
#define PIT_SET_LSB_ONLY (0x01 << 4) /*          Read only LSB */
#define PIT_SET_MSB_ONLY (0x02 << 4) /*          Read only MSB */
#define PIT_SET_LSB_MSB  (0x03 << 4) /*          Read LSB, then MSB */
#define PIT_CHANNEL(c)   (c << 6)    /* Bit 6-7: Channel 0-2 */


uint32_t cnt = 0;

#include <stdio.h>
void timer_handle(uint8_t irq)
{
    if (cnt++ == 50) {
	printf("Tick!\n");
	cnt = 0;
    }
}


void timer_init(uint32_t frequency)
{
   uint32_t divisor = PIT_BASE / frequency;

   // Send the command byte.
   outb(PIT_COMMAND, 
	PIT_CHANNEL(0) | PIT_MODE(2) | PIT_FORMAT_BIN | PIT_SET_LSB_MSB);

   // Send the frequency divisor.
   outb(PIT_CNT_CHAN0, (uint8_t)(divisor & 0xFF));
   outb(PIT_CNT_CHAN0, (uint8_t)((divisor>>8) & 0xFF));

   // Setup Timer IRQ Handler
   irq_register_handler(0x20, &timer_handle);
}
