#! /bin/bash
export PREFIX="$HOME/Projects/os/cross"
export TARGET=i686-eduos
export PATH="$PREFIX/bin:$PATH"
export CROSS_SYSROOT="$HOME/Projects/os/sysroot"

if [ ! -f binutils-2.31.tar.gz ];
then
	wget http://ftp.gnu.org/gnu/binutils/binutils-2.31.tar.gz
fi
tar xvfz binutils-2.31.tar.gz
# ../binutils-2.31/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot=$CROSS_SYSROOT --disable-werror

# rm -rf gcc-7.1.0
if [ ! -f gcc-7.1.0.tar.bz2 ];
then
	wget ftp://ftp.gnu.org/gnu/gcc/gcc-7.1.0/gcc-7.1.0.tar.bz2
fi
# tar xvfj gcc-7.1.0.tar.bz2

cd $HOME/Projects/os/src
rm -rf build-gcc
mkdir build-gcc
cd build-gcc
# cp -Rv ../toolchain/gcc-7.1.0 ..
../gcc-7.1.0/configure --target=$TARGET --prefix="$PREFIX" --enable-languages=c,c++ --with-newlib --with-sysroot=$CROSS_SYSROOT
make all-gcc
make all-target-libgcc
#SHLIB_LINK="i686-elf-gcc -O2 -fPIC -shared @shlib_objs@ -o @shlib_base_name@.ell" make all-target-libgcc
make install-gcc
make install-target-libgcc

