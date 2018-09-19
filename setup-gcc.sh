export PREFIX="$HOME/Projects/os/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"

export CC=gcc-5.4.4
export CXX=g++-5.4.4
export CPP=cpp-5.4.4
export LD=gcc-5.4.4

if [ ! -f binutils-2.31.tar.gz ];
then
	wget http://ftp.gnu.org/gnu/binutils/binutils-2.31.tar.gz
fi
tar xvfz binutils-2.31.tar.gz

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
../gcc-7.1.0/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers --disable-multilib --enable-initfini-array
make all-gcc
make all-target-libgcc
#SHLIB_LINK="i686-elf-gcc -O2 -fPIC -shared @shlib_objs@ -o @shlib_base_name@.ell" make all-target-libgcc
make install-gcc
make install-target-libgcc

