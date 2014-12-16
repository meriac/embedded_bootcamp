PROJECT:=minimal

TOOLCHAIN:=arm-none-eabi-
CC:=$(TOOLCHAIN)gcc
OBJDUMP:=$(TOOLCHAIN)objdump
OBJCOPY:=$(TOOLCHAIN)objcopy

CPU:=-mcpu=cortex-m4 -mthumb
CFLAGS:=$(CPU) -fno-common -Os -g3 -Wall -Werror
LDFLAGS:=$(CPU) -T$(PROJECT).ld -nostartfiles -nostdlib -lnosys

$(PROJECT).bin: $(PROJECT).elf
	$(OBJCOPY) $< -O binary $@

$(PROJECT).elf: $(PROJECT).o
	$(CC) $(LDFLAGS) -o $@ $<
	$(OBJDUMP) -d $@ > $(PROJECT).asm

clean:
	rm -f *.o *.elf *.bin *.asm