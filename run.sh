clear

set -xe

CC="gcc"
CFLAGS="-g -DTESTS -Wall -Wextra -pedantic"

directory="$1"

SRC="$1/main.c"

$CC $CFLAGS -o out $SRC

./out
