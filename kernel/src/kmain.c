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
#include <kernel/task.h>


void timer_test(void)
{
    klog_info("Tick %d\n", timer_get_jiffies());
}


extern void init_tasks(void);

#if defined(__cplusplus)
extern "C"
#endif
void kmain(mboot_info_t * mbinfo)
{
    arch_init();
    con_init();

    klog_info("Multiboot Version:\t%x\n", mbinfo->flags);
    klog_info("Memory (Low/High):\t%d/%d\n", mbinfo->mem_lo, mbinfo->mem_hi);

    task_init();
    arch_start();
    
    task_idle();
}
