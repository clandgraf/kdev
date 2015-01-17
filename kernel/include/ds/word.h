/* 
 * 
 * File:    kernel/include/ds/word.h
 * Author:  Christoph Landgraf
 * Purpose: Define structures for assembly level datatypes
 * 
 */

#ifndef WORD_H
#define WORD_H

#include <stdint.h>

typedef uint8_t byte_t;

typedef union word_struct {
  struct {
    byte_t lo;
    byte_t hi;
  };

  uint16_t v;
} word_t;

typedef union lword_struct {
  struct {
    word_t lo;
    word_t hi;
  };

  uint32_t v;
} lword_t;

#endif /* WORD_H */
