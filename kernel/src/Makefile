.SUFFIXES:
.SUFFIXES: .c .o .s .h .bin

ARCH=i386
AS=i686-elf-as
CC=i686-elf-gcc
CFLAGS=-std=gnu99 --sysroot ../../img -isystem=../../img/usr/include/ -ffreestanding -O2 -Wall -Wextra -D__IS_KERNEL
LDFLAGS=-ffreestanding -O2 

../obj/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) -c $< -o $@ $(CFLAGS)
../obj/%.o: %.s
	mkdir -p $(dir $@)
	$(AS) $< -o $@
../img/usr/include/kernel/./%.h:	%.h
	mkdir -p $(dir $@)
	cp $< $@

HEADERS=$(addprefix ../img/usr/include/kernel/, $(shell find . -name "*.h"))
OBJECTS=$(addprefix ../obj/, fb.o kmain.o arch/$(ARCH)/boot.o)
BINARY=../../img/boot/kdev.bin

all:	$(BINARY) $(HEADERS)

install-headers:	$(HEADERS)

$(BINARY):	$(OBJECTS)
	$(CC) -T arch/i386/linker.ld -o $@ $(CFLAGS) $(OBJECTS) -nostdlib -lk -lgcc

clean:
	rm -rf ../obj 
	rm -f $(BINARY)
