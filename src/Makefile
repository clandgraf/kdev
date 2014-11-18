.SUFFIXES:
.SUFFIXES: .c .o .s .h .bin

AS=i686-elf-as
CC=i686-elf-gcc
CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra
LDFLAGS=-ffreestanding -O2 -nostdlib

../obj/%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)
../obj/%.o: %.s
	$(AS) $< -o $@

OBJECTS=$(addprefix ../obj/, fb.o kmain.o util.o boot.o)

all:	../img/boot/kdev.bin

../img/boot/kdev.bin:	$(OBJECTS)
	$(CC) -T linker.ld -o $@ $(LDFLAGS) $(OBJECTS) -lgcc

clean:
	rm -f ../obj/*.o ../img/boot/kdev.bin ../kdev.iso
