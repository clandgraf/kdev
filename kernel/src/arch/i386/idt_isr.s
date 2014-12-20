	/*
	 *
	 * File:    kernel/src/arch/i386/idt_isr.s
	 * Author:  Christoph Landgraf
	 * Purpose: Interrupt Service Routines: Defines
	 *          Assembler Level Interrupt Handlers
	 *
	 */

	
	/* macro for exceptions without errno */

	.section .text
	.extern isr_dispatch
isr_common:
	pusha			/* Save Registers */
	call isr_dispatch       /* Call C level ISR Handler */
	popa			/* Restore Registers */
	add $8, %esp		/* Remove Interrupt ID and Error Code */
	iret

	
	/* isr_noerr: Macro for ISRs that push no error code; push a dummy value */

	.macro isr_noerr nr
	.global isr\nr
	.type isr\nr, @function
isr\nr:
	pushl $0
	pushl $\nr
	jmp isr_common
	.endm
	
	/* isr_err: Macro for ISRs with error code. */

	.macro isr_err nr
	.global isr\nr
	.type isr\nr, @function
isr\nr:
	pushl $\nr
	jmp isr_common
	.endm
	
	/* isr entry points */
	isr_noerr 0
	isr_noerr 1
	isr_noerr 2
	isr_noerr 3
	isr_noerr 4
	isr_noerr 5
	isr_noerr 6
	isr_noerr 7
	isr_err 8
	isr_noerr 9
	isr_err 10
	isr_err 11
	isr_err 12
	isr_err 13
	isr_err 14
	isr_noerr 15
	isr_noerr 16
	isr_noerr 17
	isr_noerr 18
	isr_noerr 19
	isr_noerr 20
	isr_noerr 21
	isr_noerr 22
	isr_noerr 23
	isr_noerr 24
	isr_noerr 25
	isr_noerr 26
	isr_noerr 27
	isr_noerr 28
	isr_noerr 29
	isr_noerr 30
	isr_noerr 31
