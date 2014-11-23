#
# File:    kernel/src/Makefile
# Author:  Christoph Landgraf
# Purpose: Compiles the kernel binary and copies the kernel headers to img/usr/include/kernel.
#

include ../../config.mk

.SUFFIXES:
.SUFFIXES: .c .o .s .h .bin

CFLAGS=-std=gnu99 --sysroot ../../img -isystem ../../img/usr/include/ -ffreestanding -O2 -Wall -Wextra
LDFLAGS=-ffreestanding -O2 

../obj/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) -c $< -o $@ $(CFLAGS) -D__IS_KERNEL
../obj/%.o: %.s
	mkdir -p $(dir $@)
	$(AS) $< -o $@

OBJECTS=$(addprefix ../obj/, fb.o kmain.o arch/$(ARCH)/boot.o arch/$(ARCH)/io.o)
BINARY=../../img/boot/kdev.bin

.PHONY:	all clean

all:	$(BINARY)

$(BINARY):	$(OBJECTS) ../../img/usr/lib/libk.a
	mkdir -p ../../img/boot
	$(CC) -T arch/i386/linker.ld -o $@ $(CFLAGS) $(OBJECTS) -nostdlib -lk -lgcc

clean:
	rm -rf ../obj $(BINARY)
