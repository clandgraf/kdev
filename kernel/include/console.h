/*
 * File:    console.h
 * Author:  Christoph Landgraf
 * Purpose: Provides functions for accessing the system-console.
 *          These functions are implemented by the VGA-driver.
 *
 */

#ifndef KERNEL_CONSOLE_H_INCLUDED
#define KERNEL_CONSOLE_H_INCLUDED

/**
 * @brief Initialize the system-console.
 */
void con_init();

/**
 * @brief Clear the system-console.
 */
void con_clear();

/**
 * @brief Put char \a c to the system-console 
 *        at the current cursor-position.
 */
void con_putchar(char c);

#endif
