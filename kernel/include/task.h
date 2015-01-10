/*
 *
 * File:    kernel/include/task.h
 * Author:  Christoph Landgraf
 * Purpose: Architecture independent interface for tasks
 *
 */

#ifndef KERNEL_TASK_H_INCLUDED
#define KERNEL_TASK_H_INCLUDED

#include <kernel/macros.h>
#include arch_header(task.h)

void task_idle(void);
void task_init(void); /* Defined in arch/i386/task.c */

#endif
