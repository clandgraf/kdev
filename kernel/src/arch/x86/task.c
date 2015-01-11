/*
 * 
 * File:    kernel/src/arch/x86/task.c
 * Author:  Christoph Landgraf
 * Purpose: Tasks and Scheduling for x86 platform
 * 
 */

#include <kernel/arch/x86/cpu_state.h>
#include <kernel/arch/x86/task.h>
#include <kernel/klog.h>
#include <kernel/ds/list.h>
#include <stdint.h>

#define TASK_GRP_IDLE   0
#define TASK_GRP_NORMAL 1

#define TASK_STACK_SIZE 4096

typedef void (*task_entry_t)(void);

typedef struct task_struct {
    cpu_state_t * state;

    LIST_T
} task_t;

task_t * current_task = 0;
task_t task_idle;

// Tasks

#include <stdio.h>
#include <kernel/timer.h>

uint8_t task_stacks[2][TASK_STACK_SIZE];
task_t tasks[2];

void task_a_fn(void)
{
    while (1) {
	klog_info("a: %d\n", timer_get_jiffies());
	task_break();
    }
}

void task_b_fn(void)
{
    while (1) {
	printf("b: %d\n", timer_get_jiffies());
	task_break();
    }
}

// ---

void task_init_task(int id, task_entry_t entry)
{
    // Create cpu_state at end of stack, and initialize process state
    cpu_state_t * new_state = (cpu_state_t *) (task_stacks[id] + 4096 - sizeof(cpu_state_t));
    new_state->eax = 0x00; /* GP Registers to NULL */
    new_state->ebx = 0x00;
    new_state->ecx = 0x00;
    new_state->edx = 0x00;
    new_state->esi = 0x00;
    new_state->edi = 0x00;
    new_state->ebp = 0x00;

    new_state->eip    = (uint32_t) entry; /* Instruction Pointer points to tasks entry point */
    new_state->cs     = 0x08;             /* Load Ring-0 Code Segment */
    new_state->eflags = 0x202;            /* Enable Interrupts on iret */

    // Setup task_t object of task
    tasks[id].state = new_state;
}

cpu_state_t * task_sched(cpu_state_t * new_state)
{
    // Update cpu_state of current task
    // except if it is kmain
    current_task->state = new_state;

    // Update task index
    current_task = list_entry_next(current_task);
    
    // And return cpu_state of next task
    return current_task->state;
}


void task_init(void)
{
    task_init_task(0, &task_a_fn);
    task_init_task(1, &task_b_fn);

    // Make list circular
    list_node(task_idle).next = &list_node(task_idle);
    list_node(task_idle).prev = &list_node(task_idle);
    current_task = &task_idle;

    // Insert Task A and B
    list_insert(&list_node(*current_task),
                &list_node(tasks[1]));
    list_insert(&list_node(*current_task),
                &list_node(tasks[0]));
}
