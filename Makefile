#
# File:    Makefile
# Author:  Christoph Landgraf
# Purpose: Top level makefile. Use target run to start a vm booting the os
#

include config.mk

.PHONY:	all run disc-image kernel libs clean install-headers

all:	kdev.iso

run:	kdev.iso
	qemu-system-i386 -cdrom kdev.iso

kdev.iso:	$(SYS_ROOT)/boot/kdev.bin
	mkdir -p $(SYS_ROOT)/boot/grub
	cp grub.cfg $(SYS_ROOT)/boot/grub
	grub-mkrescue -o $@ img

$(SYS_ROOT)/boot/kdev.bin:	install-headers libs
	cd kernel/src && $(MAKE)

install-headers:
	cd libc && $(MAKE) install-headers
	cd kernel && $(MAKE) install-headers

libs:	
	cd libc && $(MAKE)

clean:
	cd kernel && $(MAKE) clean
	cd libc && $(MAKE) clean
	rm -rf $(SYS_ROOT)
	rm -f kdev.iso
	find . -name "*~" -exec rm {} \;
