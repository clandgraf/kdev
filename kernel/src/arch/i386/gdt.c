/*
 * File:    kernel/src/arch/i386/gdt.c
 * Author:  Christoph Landgraf
 * Purpose: This file contains definitions and functions for 
 *          setting up the Global Descriptor Table.
 */

#include <stdint.h>

/* Flags */

#define GDT_OPSIZE_16 0x0
#define GDT_OPSIZE_32 0x4

#define GDT_GRAN_1B   0x0
#define GDT_GRAN_4K   0x8

/* Access Byte */

#define GDT_ACC_ACCESS  0x01 /* Bit 0:   Access Bit, is set by cpu on access */
#define GDT_ACC_RWABLE  0x02 /* Bit 1:   Read-/writeable: If set, code segment is readable, datasegment is writable */
#define GDT_ACC_DIRCONF 0x04 /* Bit 2:   Direction/Conforming Bit: Depends on wether this is code or datasegment */
#define GDT_ACC_EXEC    0x08 /* Bit 3:   Executable: Set if this is a code segment */
#define GDT_ACC_SEGMENT 0x10 /* Bit 4:   Segment: Set if this is a code-/data-segment */
#define GDT_ACC_RING0   0x00 /* Bit 5-6: Ring Level */
#define GDT_ACC_RING1   0x20
#define GDT_ACC_RING2   0x40
#define GDT_ACC_RING3   0x60
#define GDT_ACC_PRESENT 0x80 /* Bit 7:   Set if entry should be active */

struct gdt_entry {
    unsigned int lmt_lo  : 16;
    unsigned int base_lo : 24;
    unsigned int access  :  8;
    unsigned int lmt_hi  :  4;
    unsigned int flags   :  4;
    unsigned int base_hi :  8;

} __attribute__((packed));

struct gdt_ptr {
    uint16_t lmt;
    void * base;

} __attribute__((packed));

struct gdt_entry gdt[3];
struct gdt_ptr gdtp;

/* defined in kernel/src/arch/i386/boot.s */
extern void gdt_flush(void);

void gdt_set_gate(int idx, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags)
{
    gdt[idx].base_lo = base & 0xffffff;      /* Base */
    gdt[idx].base_hi = (base >> 24) & 0xff;
    
    gdt[idx].lmt_lo  = limit & 0xffff;       /* Limit */
    gdt[idx].lmt_hi  = (limit >> 16) & 0x0f;

    gdt[idx].flags   = flags & 0x0f;         /* Granularity */
    gdt[idx].access  = access;               /* Access */
}

/* called in kernel/src/arch/i386/boot.s */
extern void gdt_init(void)
{
    gdtp.lmt = sizeof(struct gdt_entry) * 3 - 1;
    gdtp.base  = (void *) &gdt[0];

    gdt_set_gate(0, 0, 0, 0, 0);
    gdt_set_gate(1, 0, 0xffffffff, /* Code Segment */
		 GDT_ACC_RING0 | GDT_ACC_PRESENT | GDT_ACC_SEGMENT | GDT_ACC_EXEC | GDT_ACC_RWABLE, // 0x9a
		 GDT_OPSIZE_32 | GDT_GRAN_4K);

    gdt_set_gate(2, /* Data Segment */
		 0, 0xffffffff,
		 GDT_ACC_RING0 | GDT_ACC_PRESENT | GDT_ACC_SEGMENT | GDT_ACC_RWABLE, // 0x92
		 GDT_OPSIZE_32 | GDT_GRAN_4K);

    gdt_flush();
}
