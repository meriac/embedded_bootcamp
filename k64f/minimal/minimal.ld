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
		KEEP(*(.vtor))
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
