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
#include <kernel/timer.h>
#include <kernel/klog.h>


void timer_test(void)
{
    klog_info("Tick %d\n", timer_get_jiffies());
}


#if defined(__cplusplus)
extern "C"
#endif
void kmain(mboot_info_t * mbinfo)
{
    arch_init();
    con_init();

    klog_info("Multiboot Version:\t%x\n", mbinfo->flags);
    klog_info("Memory (Low/High):\t%d/%d\n", mbinfo->mem_lo, mbinfo->mem_hi);

    timer_register_handler(100, &timer_test);
    arch_start();
}
