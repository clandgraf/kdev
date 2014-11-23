	/*
	 *
	 * File:    kernel/src/arch/i386/boot.s
	 * Author:  Christoph Landgraf
	 * Purpose: Bootstrapping Code for i386 processors using a multiboot bootloader
	 *          (see http://www.gnu.org/software/grub/manual/multiboot/multiboot.html#Specification)
	 *
	 */ 

	/* Constants for Multiboot Header Section */
	.set ALIGN,    1<<0
	.set MEMINFO,  1<<1
	.set FLAGS,    ALIGN | MEMINFO
	.set MAGIC,    0x1BADB002
	.set CHECKSUM, -(MAGIC + FLAGS)

	/* Multiboot Header Section */
	.section .multiboot
	.align 4
	.long MAGIC
	.long FLAGS
	.long CHECKSUM

	/* Setup 16Kb Stack for bootstrap */
	.section .bootstrap_stack, "aw", @nobits
stack_bottom:
	.skip 16384
stack_top:

	/* From kernel/src/arch/i386/gdt.c */
	.global gdt_install
	
	/* Entry Point of the kernel */
	.section .text
	.global _start
	.type _start, @function
_start:
	movl $stack_top, %esp
	call gdt_install
	call kmain

	cli
	hlt
.Lhang:
	jmp .Lhang

	/* Install Global Descriptor Table */
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
	
	.size _start, . - _start
