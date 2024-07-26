#!/bin/sh

SOURCE="src/convolution.cpp"
NAME="a.out"
VERSION="00"

# includes and libs
INCS="-I ./libs/"
LIBS="-L ./libs/archives -lm -lstb"

# flags
CPPFLAGS="-D_DEFAULT_SOURCE -D_BSD_SOURCE -D_POSIX_C_SOURCE=2 -DVERSION=\"${VERSION}\""
CFLAGS="-fsanitize=address -g -Wall -Wno-deprecated-declarations -Wno-write-strings -Wno-unused-function -O3 ${INCS} ${CPPFLAGS}"

# compiler
CC="g++"

# building
echo "[build.sh]# building $NAME"
echo ${CC} $CFLAGS -o "$NAME" $SOURCE $LIBS
${CC} $CFLAGS -o "$NAME" $SOURCE $LIBS
echo "[build.sh]# finished building"


