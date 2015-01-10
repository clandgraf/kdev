/*
 *
 * File:    kernel/include/spinlock.h
 * Author:  Christoph Landgraf
 * Purpose: Interface of Spinlock
 *
 */

#ifndef KERNEL_SPINLOCK_H_INCLUDED
#define KERNEL_SPINLOCK_H_INCLUDED

#include <stdint.h>

#define spinlock_init(sl) (sl = 0)

typedef volatile uint32_t spinlock_t;

void spinlock_enter(spinlock_t * spinlock);
void spinlock_exit(spinlock_t * spinlock);

#endif
