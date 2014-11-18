
CC=i686-elf-gcc
CFLAGS=-isystem ../../img/usr/include -std=gnu99 -ffreestanding -O2 -Wall -Wextra --verbose

../obj/%.o:	%.c
	mkdir -p $(dir $@)
	$(CC) -c $< -o $@ $(CFLAGS)

OBJS=$(addprefix ../obj/, string/strlen.o)

all: $(OBJS) #../img/usr/lib/libk.a

#../img/usr/lib/libk.a:	$(OBJS)
