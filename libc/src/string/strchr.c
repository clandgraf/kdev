/*
 *
 * File:    libc/src/string/strchr.c
 * Author:  Christoph Landgraf
 * Purpose: Provides the libc function strchr
 *
 */

#include <string.h>

char * strchr(const char * str, int c)
{
    uint8_t c_ = (uint8_t) c;

    while (*str)
	if (*str++ == c_)
	    return (char *) str;

    return NULL;
}
