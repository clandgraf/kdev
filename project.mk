#
# File:    project.mk
# Author:  Christoph Landgraf
# Purpose: Target install-headers installs header files in subdirectory include 
#          into directory defined by INCLUDE_DIR.
#          Target install-objects invokes the makefile in the src directory which 
#          should build and install the project.
#          For an example usage see kernel/Makefile or libc/Makefile
#

include ../config.mk

$(INCLUDE_DIR)%.h:	include/%.h
	mkdir -p $(dir $@)
	cp $< $@

HEADERS=$(addprefix $(INCLUDE_DIR), $(shell find include -name '*.h' -printf '%P\n'))

.PHONY:	all install-objects install-headers clean

all: install-objects

install-objects:
	cd src && $(MAKE)
install-headers:	$(HEADERS)

clean:
	cd src && $(MAKE) clean
	rm -f $(HEADERS)
