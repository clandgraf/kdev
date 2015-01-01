#ifndef KERNEL_ARCH_I386_CPU_STATE_H_INCLUDED
#define KERNEL_ARCH_I386_CPU_STATE_H_INCLUDED

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

#endif
