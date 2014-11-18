.SUFFIXES:
.SUFFIXES: .c .o .s .h .bin

ARCH=i386
AS=i686-elf-as
CC=i686-elf-gcc
CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra
LDFLAGS=-ffreestanding -O2 -nostdlib

../obj/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) -c $< -o $@ $(CFLAGS)
../obj/%.o: %.s
	mkdir -p $(dir $@)
	$(AS) $< -o $@

OBJECTS=$(addprefix ../obj/, fb.o kmain.o util.o arch/$(ARCH)/boot.o)
BINARY=../../img/boot/kdev.bin

all:	$(BINARY)

$(BINARY):	$(OBJECTS)
	$(CC) -T arch/i386/linker.ld -o $@ $(LDFLAGS) $(OBJECTS) -lgcc

clean:
	rm -rf ../obj 
	rm -f $(BINARY)
