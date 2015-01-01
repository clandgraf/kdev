/*
 * File:    kernel/include/arch.h
 * Author:  Christoph Landgraf
 * Purpose: Architecture independent interface 
 *          for architecture initialization
 */

#ifndef KERNEL_ARCH_H_INCLUDED
#define KERNEL_ARCH_H_INCLUDED

void arch_init(void);
void arch_start(void);

#endif
