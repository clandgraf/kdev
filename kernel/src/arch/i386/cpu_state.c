/*
 *
 * File:    kernel/src/arch/i386/cpu_state.c
 * Author:  Christoph Landgraf
 * Purpose: Dumping the cpu_state_t to klog
 *
 */ 

#include <kernel/arch/i386/cpu_state.h>
#include <kernel/klog.h>

void klog_cpu_state(cpu_state_t * cpu_state)
{
    klog_info("EAX %x | ", cpu_state->eax);
    klog_info("EBX %x | ", cpu_state->ebx);
    klog_info("ECX %x | ", cpu_state->ecx);
    klog_info("EDX %x\n", cpu_state->edx);

    klog_info("ESP %x | ", cpu_state->old_esp);
    klog_info("EBP %x\n", cpu_state->ebp);

    klog_info("EIP %x | ", cpu_state->eip);
    klog_info("EFL %x | ", cpu_state->eflags);
    klog_info("ESP %x | ", cpu_state->esp);
    klog_info("\n");    
}
