#!/bin/sh

set -eu

LIBFFI_URL='https://sourceware.org/pub/libffi/libffi-3.2.1.tar.gz'

ocamlc=ocamlc
if which ocamlfind >/dev/null 2>&1 ; then
    ocamlc='ocamlfind ocamlc'
fi
ocamlc_system=$($ocamlc -config | awk -F '[\r \t]+' '/^system:/ {print $2}')
case "$ocamlc_system" in
    win32) win32=1 ;;
    win64) win32=0 ;;
    *) exit 0 ;;
esac

if [ ! -f libffi.tar.gz ]; then
    if which curl >/dev/null 2>&1; then
        curl -s -L -o libffi.tar.gz "$LIBFFI_URL"
    else
        wget --quiet "$LIBFFI_URL" -O libffi.tar.gz
    fi
fi

tar -xzf libffi.tar.gz
cd libffi-*
# see https://sourceware.org/ml/libffi-discuss/2014/msg00247.html
# doesn't build on 64-bit without it
patch -p1 <../msvc-libffi/win64.S.patch
# see https://github.com/libffi/libffi/issues/198
# 'returning struct (foreign)' segfaults without it
patch -p1 <../msvc-libffi/win32.S.patch
# see above and https://github.com/Alexpux/MINGW-packages/blob/d7ccba6c06463f65a88da8cb0ca88ecea7fbfc28/mingw-w64-libffi/fix_return_size.patch
# also affects 'returning struct (foreign)', this time for 64-bit
patch -p2 <../msvc-libffi/fix_return_size.patch

curdir=$(readlink -f .)
libffidir=$(basename "$curdir")
MSVCC="${curdir}/msvcc.sh"
if [ $win32 -eq 1 ]; then
    subdir=i686-unknown-cygwin
    if [ -x /bin/dash ]; then
        /bin/dash ./configure CC="${MSVCC} -m32" CXX="${MSVCC} -m32" LD=link CPP="cl -nologo -EP" CXXCPP='cl -nologo -EP' CFLAGS='-O2 -Gy- -MD' --enable-static --disable-shared --build=i686-unknown-cygwin SHELL=/bin/dash
    else
        ./configure CC="${MSVCC} -m32" CXX="${MSVCC} -m32" LD=link CPP="cl -nologo -EP" CXXCPP='cl -nologo -EP' CFLAGS='-O2 -Gy- -MD' --enable-static --disable-shared --build=i686-unknown-cygwin
    fi
    rm i686-unknown-cygwin/include/ffitarget.h
    cp src/x86/ffitarget.h i686-unknown-cygwin/include/ffitarget.h
    sed -i 's|#define FFI_TARGET_HAS_COMPLEX_TYPE||g' i686-unknown-cygwin/include/ffitarget.h
    make
else
    subdir=x86_64-unknown-cygwin
    if [ -x /bin/dash ]; then
        /bin/dash ./configure CC="${MSVCC} -m64" CXX="${MSVCC} -m64" LD=link CPP="cl -nologo -EP" CXXCPP='cl -nologo -EP' CFLAGS='-O2 -Gy- -MD' --enable-static --disable-shared --build=x86_64-unknown-cygwin SHELL=/bin/dash
    else
        ./configure CC="${MSVCC} -m64" CXX="${MSVCC} -m64" LD=link CPP="cl -nologo -EP" CXXCPP='cl -nologo -EP' CFLAGS='-O2 -Gy- -MD' --enable-static --disable-shared --build=x86_64-unknown-cygwin
    fi
    rm ./x86_64-unknown-cygwin/include/ffitarget.h
    cp src/x86/ffitarget.h x86_64-unknown-cygwin/include/ffitarget.h
    sed -i 's|#define FFI_TARGET_HAS_COMPLEX_TYPE||g' x86_64-unknown-cygwin/include/ffitarget.h
    make
fi
cd ..
cat - > ctypes-foreign.install <<EOF
lib: [
 "${libffidir}/${subdir}/.libs/libffi.lib"
 "${libffidir}/${subdir}/include/ffitarget.h"
 "${libffidir}/${subdir}/include/ffi.h"
]
EOF
exit 0
