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
    
    int i;
    for (int i = 0; i < 24; i++) {
	printf("Hello %x.\n", i);
    }
}
