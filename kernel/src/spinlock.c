/*
 *
 * File:    kernel/src/spinlock.c
 * Author:  Christoph Landgraf
 * Purpose: Spinlock Implementation
 *
 */

#include <kernel/spinlock.h>
#include <kernel/task.h>

void spinlock_enter(spinlock_t * spinlock)
{
    while (__sync_lock_test_and_set(spinlock, 1))
        task_break();
}

void spinlock_exit(spinlock_t * spinlock)
{
    __sync_lock_release(spinlock);
}
