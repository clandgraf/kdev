/*
 *
 * File:    strlen.c
 * Author:  Christoph Landgraf
 * Purpose: Defines the libc function strlen.
 *
 */

#include <string.h>

size_t strlen(const char * str) 
{
    size_t len = 0;
    
    while (*str++)
	len++;
  
    return len;
}
