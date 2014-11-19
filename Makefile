
SUFFIXES=
SUFFIXES=.iso

.PHONY:	all run kernel libs clean

all:	disc-image

run:	disc-image
	qemu-system-i386 -cdrom kdev.iso

disc-image: kernel kdev.iso

kdev.iso:
	grub-mkrescue -o $@ img

kernel:	libs
	cd kernel/src && $(MAKE)

libs:	
	cd libc/ && $(MAKE)

clean:
	cd kernel/src && $(MAKE) clean
	cd libc && $(MAKE) clean
	rm kdev.iso
