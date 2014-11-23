/*
 *
 * File:    libc/src/string/memchr.c
 * Author:  Christoph Landgraf
 * Purpose: Defines the libc function memchr.
 *
 */

#include <string.h>

void * memchr(const void * addr, int chr, size_t n)
{
    uint8_t * addr_ = (uint8_t *) addr;
    uint8_t chr_ = chr;

    while (n-- > 0)
	if (*addr_ == chr_)
	    return (void *) addr_;
	else
	    addr_++;

    return NULL;
}
