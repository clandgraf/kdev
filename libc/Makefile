
../img/usr/include/%.h:	include/%.h
	mkdir -p $(dir $@)
	cp $< $@

HEADERS=$(addprefix ../img/usr/, $(shell find include/ -name *.h))
#LIBS=../img/usr/lib/libk.a

all: install-libs

#install-libs:	install-headers $(LIBS)
#	cd src && $(MAKE)

install-headers:	$(HEADERS)
