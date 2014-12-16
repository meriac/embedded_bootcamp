PROJECT:=hello_world
ARCH:=MK64F
CPU:=$(ARCH)N1M0XXX12
CONFIG:=-DNOSYSTEM

APP_CLEAN:=
APP_CFLAGS:=-Isrc -I. $(CONFIG)
APP_SRC:=\
	src/isr.c\
	src/main.c

include ../../core/Makefile.rules
