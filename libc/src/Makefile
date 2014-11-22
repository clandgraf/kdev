
AR=i686-elf-ar
CC=i686-elf-gcc
CFLAGS=-isystem ../../img/usr/include -std=gnu99 -ffreestanding -O2 -Wall -Wextra

../obj/usr/%.o:	%.c
	mkdir -p $(dir $@)
	$(CC) -c $< -o $@ $(CFLAGS)

../obj/kern/%.o:	%.c
	mkdir -p $(dir $@)
	$(CC) -c $< -o $@ $(CFLAGS) -D__ISKERNEL

LIBK=../../img/usr/lib/libk.a
LIBC=../../img/usr/lib/libc.a
LIBS=$(LIBK) $(LIBA)

OBJS=string/strlen.o

LIBC_OBJS=$(addprefix ../obj/usr/, $(OBJS))
LIBK_OBJS=$(addprefix ../obj/kern/, $(OBJS))

.PHONY:	all clean

all:	$(LIBK) $(LIBC)

$(LIBK):	$(LIBK_OBJS)
	mkdir -p $(dir $@)
	$(AR) rcs $@ $(OBJS)

$(LIBC):	$(LIBC_OBJS)
	mkdir -p $(dir $@)
	$(AR) rcs $@ $(OBJS)

clean:
	rm -rf ../obj $(LIBK) $(LIBC) ./*~
