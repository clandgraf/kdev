/*
 *
 * File:    kernel/include/arch/i386/irq.h
 * Author:  Christoph Landgraf
 * Purpose: Management of Interrupt handlers
 *
 */ 

#ifndef KERNEL_ARCH_I386_IRQ_H_INCLUDED
#define KERNEL_ARCH_I386_IRQ_H_INCLUDED

#include <stdint.h>

typedef void (*irq_handler_t)(uint8_t irq);

void irq_register_handler(uint8_t irq, irq_handler_t handler);

#endif
