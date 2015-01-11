/*
 *
 * File:    kernel/src/arch/x86/io.h
 * Author:  Christoph Landgraf
 * Purpose: Assembly Routines from accessing IA-32 i/o-ports from Assembly
 * 
 * TODO implement io functions
 *
 */

	.section .text

	.globl inb
	.type inb, @function
inb:
	movw 4(%esp), %dx
	inb %dx
	ret

	.globl inw
	.type inw, @function
inw:
	ret

	.globl inl
	.type inl, @function
inl:
	ret

	.globl outb
	.type outb, @function
outb:
	movw 4(%esp), %dx
	movb 8(%esp), %al
	outb %al, %dx
	ret

	.globl outw
	.type outw, @function
outw:
	ret

	.globl outl
	.type outl, @function
outl:
	ret
