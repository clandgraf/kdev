	/*
	 *
	 * File:    kernel/src/arch/x86/idt_isr.s
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
	push %esp
	call isr_dispatch       /* Call C level ISR Handler */
	mov %eax, %esp          /* switch stack: isr_dispatch returns new task stack if .. */
	                        /* .. task is scheduled, else the pointer passed. .. */
	                        /* .. no need to pop parameter here, since esp already points .. */
	                        /* .. to the cpu_state_t object */
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
	/* Hardware Faults */
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

	/* IRQs */
	isr_noerr 32
	isr_noerr 33
	isr_noerr 34
	isr_noerr 35
	isr_noerr 36
	isr_noerr 37
	isr_noerr 38
	isr_noerr 39
	isr_noerr 40
	isr_noerr 41
	isr_noerr 42
	isr_noerr 43
	isr_noerr 44
	isr_noerr 45
	isr_noerr 46
	isr_noerr 47
