#
# File:    kernel/src/Makefile
# Author:  Christoph Landgraf
# Purpose: Compiles the kernel binary and copies the kernel headers to img/usr/include/kernel.
#

include ../../config.mk

CFLAGS=-std=gnu99 --sysroot $(SYS_ROOT) -isystem $(SYS_ROOT)/usr/include/ -ffreestanding -O2 -Wall -Wextra -Wpadded
LDFLAGS=-ffreestanding -O2 

../obj/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) -c $< -o $@ $(CFLAGS) -D__IS_KERNEL
../obj/%.s.o: %.s
	mkdir -p $(dir $@)
	$(AS) $< -o $@

OBJECTS=$(addsuffix .o, $(addprefix ../obj/, \
		$(shell find . -path "./arch" -prune -name "*.s" -printf "%P\n" -o -name "*.c" -printf "%P\n") \
		$(shell find arch/$(ARCH)/ -name "*.s" -o -name "*.c")))
	# kmain.o \
	# arch/$(ARCH)/boot.o \
	# arch/$(ARCH)/io.o \
	# arch/$(ARCH)/vga/text_mode.o \
	# arch/$(ARCH)/gdt.o \
	# arch/$(ARCH)/gdt_flush.o)
BINARY=$(SYS_ROOT)/boot/kdev.bin

.PHONY:	all clean

all:	$(BINARY)

$(BINARY):	$(OBJECTS) $(SYS_ROOT)/usr/lib/libk.a
	mkdir -p $(SYS_ROOT)/boot
	$(CC) -T arch/i386/linker.ld -o $@ $(CFLAGS) $(OBJECTS) -nostdlib -lk -lgcc

clean:
	rm -rf ../obj $(BINARY)
