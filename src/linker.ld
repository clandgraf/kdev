/* Entry Point is _start in boot.s */
ENTRY(_start)

SECTIONS
{
	/* Load the kernel at 1MB */
	. = 1M;
	
	/* First put the .multiboot header, than the .text sections */
	.text BLOCK(4K) : ALIGN(4K)
	{
		*(.multiboot)
		*(.text)
	}

	/* Read-Only Data */
	.rodata BLOCK(4K) : ALIGN(4K)
	{
		*(.rodata)
	}

	.data BLOCK(4K) : ALIGN(4K)
	{
		*(.data)
	}

	.bss BLOCK(4K) : ALIGN(4K)
	{
		*(COMMON)
		*(.bss)
		*(.bootstrap_stack)
	}
}
