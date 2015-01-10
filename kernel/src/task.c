/*
 *
 * File:    kernel/src/task.c
 * Author:  Christoph Landgraf
 * Purpose: Architecture independent task definitions
 *
 */

#include <kernel/task.h>
#include <kernel/klog.h>

void task_idle_fn(void)
{
    while(1) {
        printf("Idle\n");
        task_break();
    }
}
