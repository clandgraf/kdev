/*
 *
 * File:    kernel/src/kmain.c
 * Author:  Christoph Landgraf
 * Purpose: Defines kmain, the main function of the kernel
 *
 */

#include <kernel/console.h>
#include <stdio.h>

#if defined(__cplusplus)
extern "C"
#endif
void kmain()
{
    con_init();
    
    int i;
    for (int i = 0; i < 24; i++) {
	printf("Hello %x.\n", i);
    }
}
