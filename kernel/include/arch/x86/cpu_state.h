/*
 *
 * File:    kernel/include/arch/x86/cpu_state.h
 * Author:  Christoph Landgraf
 * Purpose: Defines structures for storing the cpu-state on x86 machines
 *
 */ 

#ifndef KERNEL_ARCH_X86_CPU_STATE_H_INCLUDED
#define KERNEL_ARCH_X86_CPU_STATE_H_INCLUDED

#include <stdint.h>

typedef struct cpu_state {
    // Pushed by pusha
    uint32_t edi;
    uint32_t esi;
    
    uint32_t ebp;
    uint32_t old_esp;

    uint32_t ebx;
    uint32_t edx;
    uint32_t ecx;
    uint32_t eax;

    // Pushed by isr stubs
    uint32_t intr;
    uint32_t err;

    // Pushed by Processor
    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
    uint32_t esp;
    uint32_t ss;
    
} cpu_state_t;

void klog_cpu_state(cpu_state_t * cpu_state);

#endif
