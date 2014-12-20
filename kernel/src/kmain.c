/*
 *
 * File:    kernel/src/kmain.c
 * Author:  Christoph Landgraf
 * Purpose: Defines kmain, the main function of the kernel
 *
 */

#include <kernel/arch.h>
#include <kernel/console.h>
#include <kernel/multiboot.h>
#include <stdio.h>

extern void isr0(void);

#if defined(__cplusplus)
extern "C"
#endif
void kmain(mboot_info_t * mbinfo)
{
    arch_init();
    con_init();

    printf("Multiboot Version:\t%x\n", mbinfo->flags);
    printf("Memory (Low/High):\t%d/%d\n", mbinfo->mem_lo, mbinfo->mem_hi);

    asm volatile("int $0x0");
    asm volatile("int $0x1");
    asm volatile("int $0x2");
}
