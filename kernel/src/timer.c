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


uint32_t timer_get_jiffies(void)
{
    return jiffies;
}
