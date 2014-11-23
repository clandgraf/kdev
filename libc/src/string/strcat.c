/*
 *
 * File:    libc/src/string/strcat.c
 * Author:  Christoph Landgraf
 * Purpose: Provides the libc function strcat
 *
 */

#include <string.h>

char * strcat(char * dest, const char * src)
{
    char * dest_ = dest;
    char * src_ = (char *) src;

    while (*dest_)
	dest_++;

    while (*src_)
	*dest_++ = *src_++;
    
    *dest_ = '\0';

    return dest;
}
