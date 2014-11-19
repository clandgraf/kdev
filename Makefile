
SUFFIXES=
SUFFIXES=.iso

all:	kdev.iso

run:	kdev.iso
	qemu-system-i386 -cdrom $<

kdev.iso:	kernel
	grub-mkrescue -o $@ img

kernel:	libs
	cd kernel/src && $(MAKE)

libs:	
	cd libc/ && $(MAKE)

clean:
	cd kernel/src && $(MAKE) clean
	cd libc && $(MAKE) clean
