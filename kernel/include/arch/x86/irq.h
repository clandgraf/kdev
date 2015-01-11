/*
 *
 * File:    kernel/include/arch/x86/irq.h
 * Author:  Christoph Landgraf
 * Purpose: Management of Interrupt handlers
 *
 */ 

#ifndef KERNEL_ARCH_X86_IRQ_H_INCLUDED
#define KERNEL_ARCH_X86_IRQ_H_INCLUDED

#include <stdint.h>

#define IRQ_BASE 0x20
#define IRQ_PIT  IRQ_BASE + 0x00
#define IRQ_KBC  IRQ_BASE + 0x01

typedef void (*irq_handler_t)(uint8_t irq);

void irq_register_handler(uint8_t irq, irq_handler_t handler);

#endif
