#
# File:    libc/Makefile
# Author:  Christoph Landgraf
# Purpose: Installs libc headers and invokes the Makefile in the source 
#          directory to compile libc and libk.
#

include ../config.mk

../img/usr/include/%.h:	include/%.h
	mkdir -p $(dir $@)
	cp $< $@

HEADERS=$(addprefix ../img/usr/include/, $(shell find include -name '*.h' -printf '%P\n'))

.PHONY:	all install-libs install-headers clean

all: install-libs

install-libs:
	cd src && $(MAKE)
install-headers:	$(HEADERS)

clean:
	cd src && $(MAKE) clean
	rm -f $(HEADERS)
