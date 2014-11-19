
AR=i686-elf-ar
CC=i686-elf-gcc
CFLAGS=-isystem ../../img/usr/include -std=gnu99 -ffreestanding -O2 -Wall -Wextra

../obj/%.o:	%.c
	mkdir -p $(dir $@)
	$(CC) -c $< -o $@ $(CFLAGS)

LIBK=../../img/usr/lib/libk.a
LIBS=LIBK

OBJS=$(addprefix ../obj/, string/strlen.o)

.PHONY:	all clean

all:	$(LIBK)

$(LIBK):	$(OBJS)
	mkdir -p $(dir $@)
	$(AR) rcs $@ $(OBJS)

clean:
	rm -rf ../obj $(LIBK)
