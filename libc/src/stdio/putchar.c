/*
 *
 * File:    libc/src/stdio/putchar.c
 * Author:  Christoph Landgraf
 * Purpose: Defines the libc putchar function
 *
 */

#include <stdio.h>
#ifdef __IS_KERNEL
#include <kernel/fb.h>
#endif

int putchar(int ic)
{
    char c = (char) ic;
    
#ifdef __IS_KERNEL
    fb_putchar(c);
#else
    // TODO Implement putchar
#warning "'putchar.c' is missing definition for libc!"
#endif
    
    return ic;
}
