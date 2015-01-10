/*
 *
 * File:    kernel/src/arch/i386/task.h
 * Author:  Christoph Landgraf
 * Purpose: Archtitecture dependent interface for tasks
 *
 */

#ifndef KERNEL_ARCH_I386_TASK_H_INCLUDED
#define KERNEL_ARCH_I386_TASK_H_INCLUDED

inline void task_break(void)
{
    __asm__ __volatile__("hlt");
}

#endif
