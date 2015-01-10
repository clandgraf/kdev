/*
 *
 * File:    kernel/src/task.c
 * Author:  Christoph Landgraf
 * Purpose: Architecture independent task definitions
 *
 */

#include <kernel/task.h>

void task_idle(void)
{
    while(1)
        task_break();
}
