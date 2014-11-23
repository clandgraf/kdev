/*
 *
 * File:    string.h
 * Author:  Christoph Landgraf
 * Purpose: Defines the libc function memmove.
 *
 */

#include <string.h>

void * memmove(void * dest, void * src, size_t n)
{
    if (dest > src && dest < src + n) { 	// Copy from behind.
	uint8_t * dest_ = dest + n;
	uint8_t * src_ = src + n;
	
	while (n-- > 0)
	    *--dest_ = *--src_;
	    
	return dest;
    }

    return memcpy(dest, src, n); // We assume memcpy copies from start.
}
