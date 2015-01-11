/*
 *
 * File:    kernel/src/arch/x86/io.h
 * Author:  Christoph Landgraf
 * Purpose: Provides functions for reading and writing to IA32 i/o-ports.
 *
 */

#ifndef KERNEL_ARCH_X86_IO_H_INCLUDED
#define KERNEL_ARCH_X86_IO_H_INCLUDED

#include <stdint.h>

uint8_t  inb(uint16_t port);
uint16_t inw(uint16_t port);
uint32_t inl(uint16_t port);

void outb(uint16_t port, uint8_t value);
void outw(uint16_t port, uint8_t value);
void outl(uint16_t port, uint8_t value);

#endif
