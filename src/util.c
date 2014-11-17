/*
 *
 * File:   util.c
 * Author: Christoph Landgraf
 *
 */

#include "util.h"

size_t strlen(const char * str)
{
  size_t len = 0;

  while (*str++)
    len++;

  return len;
}
