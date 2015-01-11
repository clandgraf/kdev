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
export ARCH=x86

export AS=i686-elf-as
export CC=i686-elf-gcc
export AR=i686-elf-ar
export CPP=i686-elf-cpp

export SYS_ROOT_NAME=img


# Setup Directory Structure
export DEV_ROOT=$(dir $(lastword $(MAKEFILE_LIST)))
export SYS_ROOT=$(DEV_ROOT)$(SYS_ROOT_NAME)


###
###  Helper Functions
###

# detect sed
ifeq ($(shell echo a | sed s/a\?/b/g), a)
export SED=sed -E
else
export SED=sed
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
