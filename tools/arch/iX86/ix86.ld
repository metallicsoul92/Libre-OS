ENTRY (_start)

SECTIONS
{
	/* The kernel will live at 3GB + 1MB in the virtual address space, */
	/* which will be mapped to 1MB in the physical address space. */
	/* Note that we page-align the sections. */
	. = 1M;
	/* Add a symbol that indicates the start address of the kernel. */
	kernel_begin = .;
	.text ALIGN (4K):
	{
		*(.multiboot)
		*(.text)
	}
	.rodata ALIGN (4K):
	{
		*(.rodata)
	}
	.data ALIGN (4K):
	{
		*(.data)
    PROVIDE(kernel_symbols_start = .);
    PROVIDE(kernel_symbols_end = .);
	}
	.bss ALIGN (4K):
	{
		*(COMMON)
		*(.bss)
		*(.bootstrap_stack)
	}
	/* Add a symbol that indicates the end address of the kernel. */
	kernel_end = .;
}
