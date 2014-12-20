/*
 *
 * File:    kernel/src/arch/i386/isr.c
 * Author:  Christoph Landgraf
 * Purpose: Interrupt Service Routines
 *
 */

#include <stdint.h>

/*
   In the Interrupt Handler Stubs first an error code,
   then the Interrupt Number is pushed.

   The pusha instruction pushes eax first, so it 
   is the last field in the cpu_state structure.
 */

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

#include <stdio.h>

void isr_dispatch(cpu_state_t cpu_state)
{
    printf("Received Interrupt %x: Error %x!\n", cpu_state.intr, cpu_state.err);
}
