/*
 *
 * File:    kernel/src/timer.c
 * Author:  Christoph Landgraf
 * Purpose: Utilizing the system timer.
 *          Architecture-dependent code is found in 
 *          kernel/src/arch/$(ARCH)/timer.c
 *
 */

#include <kernel/timer.h>

uint32_t jiffies = 0;

// TODO make linkedlist when memory available
timer_handler_t handlers = { 0, 0 };


void timer_register_handler(uint32_t interval, timer_handler_fn handler)
{
    handlers.interval = interval;
    handlers.handler = handler;
}


void timer_unregister_handler(timer_handler_fn handler)
{
    handlers.interval = 0;
    handlers.handler = 0;
}


void timer_run_handlers(void)
{
    if (handlers.handler) {
        if ((jiffies % handlers.interval) == 0)
            handlers.handler();
    }
}


uint32_t timer_get_jiffies(void)
{
    return jiffies;
}
