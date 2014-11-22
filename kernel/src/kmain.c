/*
 *
 * File:   kernel/src/kmain.c
 * Author: Christoph Landgraf
 *
 */

#include <kernel/fb.h>
#include <stdio.h>

#if defined(__cplusplus)
extern "C"
#endif
void kmain()
{
    fb_init();
    
    printf("Hello, Plan %x.\nNewline", 9);
}
