#
# File:    kernel/src/Makefile
# Author:  Christoph Landgraf
# Purpose: Compiles the kernel binary and copies the kernel headers to img/usr/include/kernel.
#

include ../../config.mk

CFLAGS=-std=gnu99 -DARCH=$(ARCH) --sysroot $(SYS_ROOT) -isystem $(SYS_ROOT)/usr/include/ -ffreestanding -O2 -Wall -Wextra -Wpadded
LDFLAGS=-ffreestanding -O2 

../obj/%.c.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -c $< -o $@ $(CFLAGS) -D__IS_KERNEL
../obj/%.s.o: %.s
	@mkdir -p $(dir $@)
	$(AS) $< -o $@

OBJECTS=$(addsuffix .o, $(addprefix ../obj/, \
		$(call file_list, ., , '*.s', arch) \
		$(call file_list, ., , '*.c', arch) \
		$(call file_list, ., arch/$(ARCH), '*.s') \
		$(call file_list, ., arch/$(ARCH), '*.c') \
		))

BINARY=$(SYS_ROOT)/boot/kdev.bin

.PHONY:	all clean

all:	$(BINARY)

$(BINARY):	$(OBJECTS) $(SYS_ROOT)/usr/lib/libk.a
	@mkdir -p $(SYS_ROOT)/boot
	$(CC) -T arch/$(ARCH)/linker.ld -o $@ $(CFLAGS) $(OBJECTS) -nostdlib -lk -lgcc

clean:
	rm -rf ../obj $(BINARY)
