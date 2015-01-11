
	/* void idt_flush(void); */
	.section .text
	.extern idtp
	.global idt_flush
	.type idt_flush, @function
idt_flush:
	lidt idtp
	ret
