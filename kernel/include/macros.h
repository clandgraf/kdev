/*
 *
 * File:    kernel/include/macros.h
 * Author:  Christoph Landgraf
 * Purpose: Useful Macros
 *
 */

#ifndef KERNEL_MACROS_H_INCLUDED
#define KERNEL_MACROS_H_INCLUDED

#define _STRINGIFY(a) #a
#define STRINGIFY(a) _STRINGIFY(a)
#define CONCAT3(a, b, c) a/b/c

/* Include an architecture dependent header */
#define arch_header(x) STRINGIFY(CONCAT3(kernel/arch, ARCH, x))

#endif
