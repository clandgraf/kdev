#
# File:    config.mk
# Author:  Christoph Landgraf
# Purpose: Setup environment variables for build process.
#

SUFFIXES=.c .h .s. .iso .bin .o

# Setup Toolchain and directories
ARCH=i386

AS=i686-elf-as
CC=i686-elf-gcc
AR=i686-elf-ar

SYS_ROOT_NAME=img


# Setup Directory Structure
DEV_ROOT=$(dir $(lastword $(MAKEFILE_LIST)))
SYS_ROOT=$(DEV_ROOT)$(SYS_ROOT_NAME)
