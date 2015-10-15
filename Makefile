#
# File:    Makefile
# Author:  Christoph Landgraf
# Purpose: Top level makefile. Use target run to start a vm booting the os
#

include config.mk

.PHONY:	all run disc-image kernel libs clean install-headers doc

all:	$(SYS_ROOT)/boot/kdev.bin

run:	kdev.iso
	qemu-system-i386 -cdrom kdev.iso

kdev.iso:	$(SYS_ROOT)/boot/kdev.bin
	mkdir -p $(SYS_ROOT)/boot/grub
	cp grub.cfg $(SYS_ROOT)/boot/grub
	grub2-mkrescue -o $@ img

$(SYS_ROOT)/boot/kdev.bin:	install-headers libs
	cd kernel/src && $(MAKE)

install-headers:
	cd libc && $(MAKE) install-headers
	cd kernel && $(MAKE) install-headers

libs:	
	cd libc && $(MAKE)

doc:	
	cd doc/kernel && make -f ../../doc.mk

clean:
	cd kernel && $(MAKE) clean
	cd libc && $(MAKE) clean
	cd doc/kernel && make -f ../../doc.mk clean
	rm -rf $(SYS_ROOT)
	rm -f kdev.iso
	find . -name "*~" -exec rm {} \;
