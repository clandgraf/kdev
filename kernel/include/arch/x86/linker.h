
/*
 *
 * File:    kernel/include/arch/x86/linker.h
 * Author:  Christoph Landgraf
 * Purpose: C Declarations from kernel/src/arch/x86/linker.ld
 *
 */

#ifndef KERNEL_ARCH_X86_LINKER_H_INCLUDED
#define KERNEL_ARCH_X86_LINKER_H_INCLUDED

extern const void kernel_start_;
#define KERNEL_START ((uint32_t) (&kernel_start_))

extern const void kernel_end_;
#define KERNEL_END ((uint32_t) (&kernel_end_))

#endif
