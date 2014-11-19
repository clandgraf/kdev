
../img/usr/include/%.h:	include/%.h
	mkdir -p $(dir $@)
	cp $< $@

HEADERS=$(addprefix ../img/usr/, $(shell find include/ -name *.h))

.PHONY:	all install-libs install-headers clean

all: install-headers install-libs

install-libs:
	cd src && $(MAKE)
install-headers:	$(HEADERS)

clean:
	cd src && $(MAKE) clean
	rm -f $(HEADERS)
