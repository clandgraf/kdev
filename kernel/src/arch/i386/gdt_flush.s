	/*
	 *
	 * File:    kernel/src/arch/i386/gdt_flush.s
	 * Author:  Christoph Landgraf
	 * Purpose: Defines gdt_flush (declared in gdt.c)
	 *          Sets up a GDT as initialized by gdt_init
	 *
	 */

	/* void gdt_flush(void); */
	.section .text
	.extern gdtp
	.global gdt_flush
	.type gdt_flush, @function
	
gdt_flush:
	lgdt gdtp
	movw $0x10, %ax
	movw %ax, %ds
	movw %ax, %es
	movw %ax, %fs
	movw %ax, %gs
	movw %ax, %ss
	ljmp $0x08, $flush2
flush2:
	ret
