#
# File:    libc/src/Makefile
# Author:  Christoph Landgraf
# Purpose: Compiles the libc and libk and installs these to the img
#

include ../../config.mk

CFLAGS=-isystem $(SYS_ROOT)/usr/include -std=gnu99 -ffreestanding -O2 -Wall -Wextra

## Output Variables

LIB_PREFIX=$(SYS_ROOT)/usr/lib
LIBK=$(LIB_PREFIX)/libk.a
LIBC=$(LIB_PREFIX)/libc.a
LIBS=$(LIBK) $(LIBC)

SRCS=$(call file_list, ., , '*.c')
OBJS=$(SRCS:.c=.o)
LIBC_OBJS=$(addprefix ../obj/libc/, $(OBJS))
LIBK_OBJS=$(addprefix ../obj/libk/, $(OBJS))

## Template Rules

../obj/libc/%.o:	%.c
	mkdir -p $(dir $@)
	$(CC) -c $< -o $@ $(CFLAGS)
../obj/libk/%.o:	%.c
	mkdir -p $(dir $@)
	$(CC) -c $< -o $@ $(CFLAGS) -D__IS_KERNEL
$(LIB_PREFIX)/%.a:
	mkdir -p $(dir $@)
	$(AR) rcs $@ $^

## Targets

.PHONY:	all clean

all:	$(LIBS)

$(LIBK):	$(LIBK_OBJS)
$(LIBC):	$(LIBC_OBJS)

clean:
	rm -rf ../obj $(LIBS)
