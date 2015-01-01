/*
 *
 * File:    libc/src/include/stdio.h
 * Author:  Christoph Landgraf
 * Purpose: The libc stdio.h header file
 *          Provides functions for input and output
 *
 */

#ifndef LIBC_STDIO_H_INCLUDED
#define LIBC_STDIO_H_INCLUDED

int putchar(int ic);
int printf(const char * fmt, ...);

#endif
