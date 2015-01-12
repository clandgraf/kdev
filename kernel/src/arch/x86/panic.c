/* 
 * 
 * File:    kernel/src/arch/x86/panic.c
 * Author:  Christoph Landgraf
 * Purpose: Hang the kernel on unrecoverable error
 * 
 */

#include <kernel/panic.h>
#include <kernel/klog.h>

void panic(void)
{
    klog_info("Kernel Panic\n");
    asm volatile("cli; hlt");
}
