
SUFFIXES=
SUFFIXES=.iso

all:	kdev.iso

run:	kdev.iso
	qemu-system-i386 -cdrom $<

kdev.iso:	img/boot/kdev.bin
	grub-mkrescue -o $@ img

img/boot/kdev.bin:
	cd kernel/src && $(MAKE)

clean:
	cd kernel/src && $(MAKE) clean
