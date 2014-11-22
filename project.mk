
include ../config.mk

$(INCLUDE_DIR)%.h:	include/%.h
	mkdir -p $(dir $@)
	cp $< $@

HEADERS=$(addprefix $(INCLUDE_DIR), $(shell find include -name '*.h' -printf '%P\n'))

.PHONY:	all install-libs install-headers clean

all: install-libs

install-objects:
	cd src && $(MAKE)
install-headers:	$(HEADERS)

clean:
	cd src && $(MAKE) clean
	rm -f $(HEADERS)
