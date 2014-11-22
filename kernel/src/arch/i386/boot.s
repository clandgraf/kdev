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

/* Entry Point of the kernel */
.section .text
.global _start
.type _start, @function
_start:
	movl $stack_top, %esp

	call kmain

	cli
	hlt
.Lhang:
	jmp .Lhang

.size _start, . - _start
