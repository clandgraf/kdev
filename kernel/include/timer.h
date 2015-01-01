/*
 *
 * File:    kernel/include/timer.h
 * Author:  Christoph Landgraf
 * Purpose: Utilizing the system timer.
 *          Architecture-dependent code is found in 
 *          kernel/src/arch/$(ARCH)/timer.c
 *
 */

#ifndef KERNEL_TIMER_H_INCLUDED
#define KERNEL_TIMER_H_INCLUDED

#include <stdint.h>

uint32_t timer_get_jiffies(void);

#endif
