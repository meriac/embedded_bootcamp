PROJECT:=swo_printf
ARCH:=MK64F
CPU:=$(ARCH)N1M0XXX12

SOURCES:= \
	tfp_printf.c \
	main.c

# toolchain settings
TOOLCHAIN:=arm-none-eabi-
CC:=$(TOOLCHAIN)gcc
OBJDUMP:=$(TOOLCHAIN)objdump
OBJCOPY:=$(TOOLCHAIN)objcopy

# debug settings
JLINK:=$(SEGGER)JLinkExe
JLINK_VIEWER:=$(SEGGER)JLinkSWOViewer
JLINK_VIEWER_MASK:=0x7
JLINK_PARAM:=-Device $(CPU) -if SWD

# gcc & ld compiler flags
FLAGS:=-mcpu=cortex-m4 -mthumb
CFLAGS:=$(FLAGS) -I../includes -fno-common -Os -g3 -Wall -Werror -ffunction-sections
LDFLAGS:=$(FLAGS) -Tmain.ld -nostartfiles -nostdlib -lnosys -Wl,--gc-sections

include Makefile.scripts

.PHONY: asm

$(PROJECT).bin: $(PROJECT).elf
	$(OBJCOPY) $< -O binary $@

$(PROJECT).elf: $(SOURCES:.c=.o)
	$(CC) $(LDFLAGS) -o $@ $^
	$(OBJDUMP) -d $@ > $(PROJECT).asm

flash: $(PROJECT).bin
	@echo "$$__SCRIPT_FLASH" | $(JLINK) $(JLINK_PARAM)

swo: flash
	$(JLINK_VIEWER) $(JLINK_PARAM) -itmmask $(JLINK_VIEWER_MASK) $(JLINK_SWO_PARAM)

reset:
	@echo "$$__SCRIPT_RESET" | $(JLINK) $(JLINK_PARAM)

clean:
	rm -f *.o *.elf *.bin *.asm
