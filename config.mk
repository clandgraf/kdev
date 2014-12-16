#
# File:    config.mk
# Author:  Christoph Landgraf
# Purpose: Setup environment variables for build process
#          and declare general purpose functions
#

SUFFIXES=.c .h .s. .iso .bin .o


###
###  Configuration
###

# Setup Toolchain and directories
ARCH=i386

AS=i686-elf-as
CC=i686-elf-gcc
AR=i686-elf-ar

SYS_ROOT_NAME=img


# Setup Directory Structure
DEV_ROOT=$(dir $(lastword $(MAKEFILE_LIST)))
SYS_ROOT=$(DEV_ROOT)$(SYS_ROOT_NAME)


###
###  Helper Functions
###

# detect sed
ifeq ($(shell echo a | sed s/a\?/b/g), a)
SED=sed -E
$(info BSD sed detected: using $(SED))
else
SED=sed
$(info GNU sed detected: using $(SED))
endif


# escape_re: escape text for use in sed
#   $1: the string to be escaped

escape_re=$(shell echo $(1) | $(SED) 's/[]\/$$*.^|[]/\\\\&/g')


# file_list:
#   $1, directory_removed: First part of directory, is truncated from output
#   $2, directory_kept:    Second part of directory, is kept in output
#   $3, name:              A pattern describing the file to be matched
#   $4, prune_list:        A list of pattern describing directories to be pruned

file_list=$(shell find $(strip $(1))/$(strip $(2)) \
                       $(patsubst %, -name % -prune -o , $(4)) \
                       -name $(3) -print | \
                       $(SED) s\!$(strip $(call escape_re, $(1)))\/\/\?\!\!g)
