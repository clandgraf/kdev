/*
 *
 * File:    libc/src/include/stdio.h
 * Author:  Christoph Landgraf
 * Purpose: Provides the libc printf function.
 *
 */

#include <stdio.h>
#include <stdarg.h>

static const char digit_to_char[] = {
    '0', '1', '2', '3', '4', '5', '6', '7', 
    '8', '9', 'a', 'b', 'c', 'd', 'e', 'f',  
};

static unsigned int print_signed(signed int i, unsigned int base)
{
    if (i == 0)
	return 0;

    //TODO this might be problematic due to how % treats negative numbers
    unsigned int cnt = print_signed(i / base, base) + 1;
    putchar(digit_to_char[i % base]);
    return cnt;
}

static unsigned int print_unsigned(unsigned int i, unsigned int base)
{
    if (i == 0)
	return 0;
    
    unsigned int cnt = print_unsigned(i / base, base) + 1;
    putchar(digit_to_char[i % base]);
    return cnt;
}

int printf(const char * fmt, ...)
{
    va_list varargs;
    va_start(varargs, fmt);
    
    int cnt = 0;
    while (*fmt) {
	if (*fmt != '%') {
	    // Output character and continue with next
	    putchar(*fmt);
	    cnt++; fmt++;
	    continue;
	}
	
	fmt++;
	
	// Get conversion string, convert and output vararg
	// TODO support flags, field width, precision and length
	switch (*fmt++) {
	case '%':
	    putchar('%');
	    cnt++;
	    break;
	case 'd':
	case 'i':
	    cnt += print_signed(va_arg(varargs, signed int), 10);
	    break;
	case 'o':
	    cnt += print_unsigned(va_arg(varargs, unsigned int), 8);
	    break;
	case 'u':
	    cnt += print_unsigned(va_arg(varargs, unsigned int), 10);
	    break;
	case 'x':
	case 'X':
	    cnt += print_unsigned(va_arg(varargs, unsigned int), 16);
	    break;
	}
    }
    
    return cnt;
}
