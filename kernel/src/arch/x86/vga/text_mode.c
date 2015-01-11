/*
 *
 * File:    kernel/src/arch/x86/vga/text_mode.c
 * Author:  Christoph Landgraf
 * Purpose: VGA text mode driver
 *
 */

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/arch/x86/vga/text_mode.h>
#include <kernel/arch/x86/io.h>

static const size_t VGA_CRTC_CTRL = 0x3d4;
static const size_t VGA_CRTC_DATA = 0x3d5;

static const size_t VGA_CURSOR_HI = 0x0e;
static const size_t VGA_CURSOR_LO = 0x0f;

static const size_t VGA_TM_WIDTH  = 80;
static const size_t VGA_TM_HEIGHT = 25;

size_t      vga_tm_row;
size_t      vga_tm_column;

vga_tm_attrib_t vga_tm_attrib;  /* Stores the current attributes used */
vga_tm_cell_t * vga_tm_buffer;  /* Stores the RAM Area for Text-Mode */


#define VGA_TM_INDEX(x, y) (y * VGA_TM_WIDTH + x)


vga_tm_attrib_t vga_tm_make_attrib(vga_tm_color_t foreground, vga_tm_color_t background)
{
    return foreground | background << 4;
}


vga_tm_cell_t vga_tm_make_cell(char c, vga_tm_attrib_t color)
{
    uint16_t chr16 = c;
    uint16_t col16 = color;
    
    return chr16 | col16 << 8;
}


void vga_tm_setcursor(int row, int col)
{
    uint16_t idx = VGA_TM_INDEX(col, row);
    
    outb(VGA_CRTC_CTRL, VGA_CURSOR_LO); // Select low port
    outb(VGA_CRTC_DATA, (uint8_t) idx & 0xff);

    outb(VGA_CRTC_CTRL, VGA_CURSOR_HI); // Select hi port
    outb(VGA_CRTC_DATA, (uint8_t) (idx >> 8) & 0xff);
}


void con_clear()
{
    for (size_t y = 0; y < VGA_TM_HEIGHT; y++)
	for (size_t x = 0; x < VGA_TM_WIDTH; x++)
	    vga_tm_buffer[VGA_TM_INDEX(x, y)] = 
		vga_tm_make_cell(' ', vga_tm_make_attrib(COLOR_LIGHT_GREY, COLOR_BLACK));

    vga_tm_row = 0;
    vga_tm_column = 0;

    vga_tm_setcursor(vga_tm_row, vga_tm_column);
}

void vga_tm_setcolor(vga_tm_attrib_t attrib)
{
    vga_tm_attrib = attrib;
}


void vga_tm_setcellat(char c, vga_tm_attrib_t attrib, int x, int y)
{
    vga_tm_buffer[VGA_TM_INDEX(x, y)] = vga_tm_make_cell(c, attrib);
}

/* Initialize the Framebuffer */
void con_init()
{
    vga_tm_attrib = vga_tm_make_attrib(COLOR_LIGHT_GREY, COLOR_BLACK);
    vga_tm_buffer = (uint16_t *) 0xB8000;    // TODO this is different for monochrome screens

    con_clear();
}

void con_newline()
{
    vga_tm_column = 0;
    if (++vga_tm_row == VGA_TM_HEIGHT) {
	// Make room for new row
	memmove(vga_tm_buffer,
		vga_tm_buffer + VGA_TM_INDEX(0, 1),
		VGA_TM_WIDTH * (VGA_TM_HEIGHT - 1) * 2);
	vga_tm_row--;

	// Clear new row
	for (unsigned int col = 0; col < VGA_TM_WIDTH; col++)
	    vga_tm_setcellat(' ', vga_tm_attrib, col, vga_tm_row);
    }
}


void con_putchar(char c)
{
    switch (c) {
    case '\n':
	con_newline();
	break;
    case '\t': {
	int indent = 4 - (vga_tm_column % 4);
	for (int i = 0; i < indent; i++)
	    con_putchar(' ');
	break;
    }
    default:
	vga_tm_setcellat(c, vga_tm_attrib, vga_tm_column, vga_tm_row);

	if (++vga_tm_column == VGA_TM_WIDTH)
	    con_newline();
	break;
    }

    vga_tm_setcursor(vga_tm_row, vga_tm_column);
}
