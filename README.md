My osdev experiments

This repository contains my experiments in Operating Systems Development. The motivation is mainly to learn more about systems programming. The directory kernel contains the kernel sources, while the directory libc contains libc sources.

The current implementation includes a multiboot compatible startup routine, as well as the basic setup of the x86 architecture.


Toolchain Configuration

The code has been tested on qemu-i386 using the following toolchain configuration:

gmp-6.0.0a
mpfr-3.1.2
mpc-1.0.2
binutils-2.24: configure --target=i686-elf --with-sysroot --disable-nls --disable-werror
gcc-4.8.2: configure --target=i686-elf --disable-nls --enable-languages=c,c++ --without-headers

The gmp, mpfr and mpc libraries have been configured and compiled by moving them into the gcc source directory.
The build system requires the GNU utilities make and find to run. To build bootable images GRUB2 is used.


Build Configuration

The configuration of the build system can be done by editing the file config.mk in the repositories root directory. The variables that might require editing are the following:

ARCH		  The architecture for which the kernel will be compiled.
		  This should be set to i38. The variable controls, which of the architecture dependent source trees under the kernel/src/arch directory is compiled into the kernel.

AS		  Should point to the Assembler of the Toolchain
CC		  Should point to the C Compiler of the Toolchain
AR		  Should point to the Archiver of the Toolchain

SYS_ROOT_NAME	  The directory in which to assemble the system root, given relative to the root directory of the repository

The build process will compile the system libraries and kernel and assemble a bootable system root in the directory specified by SYS_ROOT_NAME. 


Make targets:

all	Builds a bootable CD image using grub-mkrescue.
run	Uses qemu to boot the kernel
libs	Builds the system libraries libc (libc for applications) and libk (libc for the kernel)
