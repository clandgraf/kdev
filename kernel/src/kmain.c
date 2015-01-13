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
#include <kernel/panic.h>
#include arch_header(linker.h)
#include <kernel/mm.h>

void timer_test(void)
{
    klog_info("Tick %d\n", timer_get_jiffies());
}

void check_multiboot(uint32_t magic, multiboot_info_t * mbinfo)
{
    if (magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        klog_info("magic: 0x%x\n", magic);
        klog_info("Unsupported Bootloader.\n");
        panic();
    }
}

extern void init_tasks(void);

#if defined(__cplusplus)
extern "C"
#endif
void kmain(uint32_t magic, multiboot_info_t * mbinfo)
{
    arch_init();
    con_init();

    check_multiboot(magic, mbinfo);

    mm_init(mbinfo);

    klog_info("Kernel Location:   %x, %x\n", KERNEL_START, KERNEL_END);
    klog_info("Multiboot Version: %x\n", mbinfo->flags);
    klog_info("Memory (Low/High): %d/%d\n", mbinfo->mem_lower, mbinfo->mem_upper);
    klog_info("Version: %s-%s %s\n", BUILD_VERSION_BRANCH, BUILD_VERSION_REV, BUILD_VERSION_DATE);

    task_init();
    arch_start();
    
    task_idle_fn();
}
