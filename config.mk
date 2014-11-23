#
# File:    config.mk
# Author:  Christoph Landgraf
# Purpose: Setup environment variables for build process.
#

SUFFIXES=.c .h .s. .iso .bin .o

## Setup Toolchain
ARCH=i386
AS=i686-elf-as
CC=i686-elf-gcc
AR=i686-elf-ar

## Setup Directory Structure
DEV_ROOT=$(dir $(lastword $(MAKEFILE_LIST)))
SYS_ROOT=$(DEV_ROOT)img
