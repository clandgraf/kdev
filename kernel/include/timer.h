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

typedef void (*timer_handler_fn)(void);
typedef struct timer_handler_struct {
    uint32_t interval;
    timer_handler_fn handler;
    
} timer_handler_t;

void timer_register_handler(uint32_t interval, timer_handler_fn handler);
void timer_unregister_handler(timer_handler_fn handler);
void timer_run_handlers(void);

uint32_t timer_get_jiffies(void);

#endif
