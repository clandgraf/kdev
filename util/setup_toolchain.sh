#!/bin/sh

# TODO disable documentation building (texinfo requirement)

. ../kdevrc

BINUTIL_VERSION="2.25"
GCC_VERSION="4.9.3"

TARGET="i686-elf"

echo "Target: ${TARGET}"

mkdir ./tar
mkdir ./src

# Fetch binutils

if [ ! -e "./tar/binutils-${BINUTIL_VERSION}.tar.gz" ]; then
    echo "Fetching binutils-${BINUTIL_VERSION}"
    wget -P ./tar "http://ftp.gnu.org/gnu/binutils/binutils-${BINUTIL_VERSION}.tar.gz"
fi
    
if [ ! -d "./src/binutils-${BINUTIL_VERSION}" ]; then
    tar -xf "./tar/binutils-${BINUTIL_VERSION}.tar.gz" -C ./src
fi

# Fetch gcc

if [ ! -e "./tar/gcc-${GCC_VERSION}.tar.bz2" ]; then
    echo "Fetching gcc-${GCC_VERSION}"
    wget -P ./tar "ftp://ftp.gnu.org/gnu/gcc/gcc-${GCC_VERSION}/gcc-${GCC_VERSION}.tar.bz2"
fi

if [ ! -d "./src/gcc-${GCC_VERSION}" ]; then
    tar -xf "./tar/gcc-${GCC_VERSION}.tar.bz2" -C ./src
fi

cd src/gcc-${GCC_VERSION}
contrib/download_prerequisites
cd ../..

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
