/*
 *
 * File:    kernel/include/bits.h
 * Author:  Christoph Landgraf
 * Purpose: Bit manipulation utilities
 *
 */

#ifndef KERNEL_BITS_H_INCLUDED
#define KERNEL_BITS_H_INCLUDED

#define BITS_MASK(b)      (1 << b)
#define BITS_IS_SET(b, v) (v & BITS_MASK(b))

#endif
