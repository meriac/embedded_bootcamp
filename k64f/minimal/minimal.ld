ENTRY(OnReset)

MEMORY
{
	FLASH (rx) : ORIGIN = (0x00000000), LENGTH = 0x100000
	RAM (rwx)  : ORIGIN = (0x1FFF0000), LENGTH = 0x40000
}

SECTIONS
{
	.text :
	{
		/* interrupt vector table */
		KEEP(*(.vtor))

		/* reserve memory for K64F security fuses */
		. = 0x400;
		KEEP(*(.nv_config))
		FILL(0xFF)
		. = 0x410;
		FILL(0x00)

		/* rest of code & const data */
		*(.text*)
		*(.rodata*)
	} >FLASH

	.bss :
	{
		*(.data*)
		*(.bss*)
		*(COMMON)
		StackTop = ORIGIN(RAM) + LENGTH(RAM);
	} > RAM
}
