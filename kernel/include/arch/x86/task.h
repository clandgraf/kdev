/*
 *
 * File:    kernel/src/arch/x86/task.h
 * Author:  Christoph Landgraf
 * Purpose: Archtitecture dependent interface for tasks
 *
 */

#ifndef KERNEL_ARCH_X86_TASK_H_INCLUDED
#define KERNEL_ARCH_X86_TASK_H_INCLUDED

inline void task_break(void)
{
    asm volatile("hlt");
}

#endif
