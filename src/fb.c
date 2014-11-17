/*
 *
 * File:   fb.c
 * Author: Christoph Landgraf
 *
 */

#include <stddef.h>

#include "fb.h"

static const size_t FB_WIDTH  = 80;
static const size_t FB_HEIGHT = 25;

size_t fb_row;
size_t fb_column;

uint8_t   fb_color;
uint16_t* fb_buffer;


void uint8_t fb_make_color(fb_color_t foreground, fb_color_t background)
{
  return foreground | background << 4;
}


void uint8_t fb_make_cell(char c, uint8_t color)
{
  uint16 chr16 = c;
  uint16 col16 = color;

  return chr16 | col16 << 8;
}


void fb_clear()
{
  for (size_t y = 0; y < FB_HEIGHT; y++) {
    for (size_t x = 0; x < FB_WIDTH; x++) {
      const size_t index = y * FB_WIDTH + x;
      fb_buffer[index] = fb_make_cell(' ', make_color(COLOR_LIGHT_GREY, COLOR_BLACK));
    }
  }

  fb_row = 0;
  fb_column = 0;
}


void fb_init()
{
  fb_color  = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
  fb_buffer = (uint16_t *) 0xB8000;
  fb_clear();
}
