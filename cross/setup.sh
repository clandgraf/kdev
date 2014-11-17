#!/bin/sh

. ../kdevrc

BINUTIL_VERSION="2.24"
GCC_VERSION="4.8.2"
GMP_VERSION="6.0.0"
MPFR_VERSION="3.1.2"
MPC_VERSION="1.0.2"

TARGET="i686-elf"

echo "Target: ${TARGET}"

mkdir ./tar
mkdir ./src

# Fetch binutils

if [ ! -d "./src/binutils-${BINUTIL_VERSION}" ]; then
    echo "Fetching binutils-${BINUTIL_VERSION}"
    wget -P ./tar "http://ftp.gnu.org/gnu/binutils/binutils-${BINUTIL_VERSION}.tar.gz"
    tar -xf "./tar/binutils-${BINUTIL_VERSION}.tar.gz" -C ./src
fi

# Fetch gcc

if [ ! -d "./src/gcc-${GCC_VERSION}" ]; then
    echo "Fetching gcc-${GCC_VERSION}"
    wget -P ./tar "ftp://ftp.gnu.org/gnu/gcc/gcc-${GCC_VERSION}/gcc-${GCC_VERSION}.tar.bz2"
    tar -xf "./tar/gcc-${GCC_VERSION}.tar.bz2" -C ./src
fi

# Fetch gmp

if [ ! -d "src/gcc-${GCC_VERSION}/gmp" ]; then
    
    if [ ! -d "./src/gmp-${GMP_VERSION}" ]; then
	echo "Fetching gmp-${GMP_VERSION}"
	wget -P ./tar "https://gmplib.org/download/gmp/gmp-${GMP_VERSION}a.tar.bz2"
	tar -xf "./tar/gmp-${GMP_VERSION}a.tar.bz2" -C ./src
    fi
    
    echo "Moving gmp-${GMP_VERSION} to gcc-${GCC_VERSION}/gmp"
    mv "src/gmp-${GMP_VERSION}" "src/gcc-${GCC_VERSION}/gmp"
fi

# Fetch mpfr


if [ ! -d "src/gcc-${GCC_VERSION}/mpfr" ]; then

    if [ ! -d "./src/mpfr-${MPFR_VERSION}" ]; then
	echo "Fetching mpfr-${MPFR_VERSION}"
	wget -P ./tar "http://www.mpfr.org/mpfr-current/mpfr-${MPFR_VERSION}.tar.bz2"
	tar -xf "./tar/mpfr-${MPFR_VERSION}.tar.bz2" -C ./src
    fi

    echo "Moving mpfr-${MPFR_VERSION} to gcc-${GCC_VERSION}/mpfr"
    mv "src/mpfr-${MPFR_VERSION}" "src/gcc-${GCC_VERSION}/mpfr"

fi

# Fetch mpc

if [ ! -d "src/gcc-${GCC_VERSION}/mpc" ]; then

    if [ ! -d "./src/mpc-${MPC_VERSION}" ]; then
	echo "Fetching mpc-${MPC_VERSION}"
	wget -P ./tar "ftp://ftp.gnu.org/gnu/mpc/mpc-${MPC_VERSION}.tar.gz"
	tar -xf "./tar/mpc-${MPC_VERSION}.tar.gz" -C ./src
    fi

    echo "Moving mpc-${MPC_VERSION} to gcc-${GCC_VERSION}"
    mv "src/mpc-${MPC_VERSION}" "src/gcc-${GCC_VERSION}/mpc"

fi

# Compiling Binutils

mkdir src/build-binutils; cd src/build-binutils

"../binutils-${BINUTIL_VERSION}/configure" --target=$TARGET --prefix=$CROSS_PREFIX --with-sysroot --disable-nls --disable-werror
make
make install

cd ../..

# Compiling GCC

mkdir src/build-gcc; cd src/build-gcc

"../gcc-${GCC_VERSION}/configure" --target=$TARGET --prefix="$CROSS_PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
make all-gcc
make all-target-libgcc
make install-gcc
make install-target-libgcc

cd ../..
