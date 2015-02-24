#
# File:   doc.mk
# Author: Christoph Landgraf
#

include ../../config.mk

html/%.html:	src/%.rst
	@mkdir -p $(dir $@)
	$(RST2HTML) $< $@

RST_FILES=$(addprefix html/, $(call file_list, src, , '*.rst'))

.PHONY: clean

all: $(RST_FILES:.rst=.html)

clean: 
	rm -rf html
