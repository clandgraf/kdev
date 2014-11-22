include ../config.mk

../img/usr/include/kernel/%.h:	include/%.h
	mkdir -p $(dir $@)
	cp $< $@

HEADERS=$(addprefix ../img/usr/include/kernel/, $(shell find include -name '*.h' -printf '%P\n'))

.PHONY: all install-kernel install-headers clean

all: install-kernel

install-kernel:
	cd src && $(MAKE)
install-headers:	$(HEADERS)

clean:
	cd src && $(MAKE) clean
	rm -f $(HEADERS)
