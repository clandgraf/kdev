<h1>My osdev experiments</h1>

<p>This repository contains my experiments in Operating Systems Development. The motivation is mainly to learn more about systems programming. The directory kernel contains the kernel sources, while the directory libc contains libc sources.</p>

<p>The current implementation includes a multiboot compatible startup routine, as well as the basic setup of the x86 architecture.</p>


<h2>Toolchain Configuration</h2>

<p>The code has been tested on qemu-i386 using the following toolchain configuration:</p>

<ul>
<li>gmp-6.0.0a</li>
<li>mpfr-3.1.2</li>
<li>mpc-1.0.2</li>
<li>binutils-2.24: configure --target=i686-elf --with-sysroot --disable-nls --disable-werror</li>
<li>gcc-4.8.2: configure --target=i686-elf --disable-nls --enable-languages=c,c++ --without-headers</li>
</ul>

<p>The gmp, mpfr and mpc libraries have been configured and compiled by moving them into the gcc source directory. The build system requires the GNU utilities make and find to run. To build bootable images GRUB2 is used.</p>


<h2>Build Configuration</h2>

<p>The configuration of the build system can be done by editing the file config.mk in the repositories root directory. The variables that might require editing are the following:</p>

<table>
  <tr>
    <td>ARCH</td>
    <td>The architecture for which the kernel will be compiled. This should be set to i38. The variable controls, which of the architecture dependent source trees under the kernel/src/arch directory is compiled into the kernel.</td>
  </tr>
  <tr>
    <td>AS</td>
    <td>Should point to the Assembler of the Toolchain.</td>
  </tr>
  <tr>
    <td>CC</td>
    <td>Should point to the C Compiler of the Toolchain</td>
  </tr>
  <tr>
    <td>AR</td>
    <td>Should point to the Archiver of the Toolchain</td>
  </tr>
  <tr>
    <td>SYS_ROOT_NAME</td>
    <td>The directory in which to assemble the system root, given relative to the root directory of the repository</td>
  </tr>
</table>

<p>The build process will compile the system libraries and kernel and assemble a bootable system root in the directory specified by SYS_ROOT_NAME.</p>


<h3>Make targets:</h3>

<table>
  <tr>
    <td>all</td>
    <td>Builds a bootable CD image using grub-mkrescue.</td>
  </tr>
  <tr>
    <td>run</td>
    <td>Uses qemu to boot the kernel</td>
  </tr>
  <tr>
    <td>libs</td>
    <td>Builds the system libraries libc (libc for applications) and libk (libc for the kernel)</td>
  </tr>
</table>
