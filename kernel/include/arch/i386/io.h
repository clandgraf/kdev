/*
 *
 * File:    kernel/src/arch/i386/io.h
 * Author:  Christoph Landgraf
 * Purpose: Provides functions for reading and writing to IA32 i/o-ports.
 *
 */

#ifndef __IO_H__
#define __IO_H__

#include <stdint.h>

uint8_t  inb(uint16_t port);
uint16_t inw(uint16_t port);
uint32_t inl(uint16_t port);

void outb(uint16_t port, uint8_t value);
void outw(uint16_t port, uint8_t value);
void outl(uint16_t port, uint8_t value);

#endif
