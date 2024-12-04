clear

set -xe

CC="clang"
CFLAGS="-g -DTESTS -Wall -Wextra -pedantic -lm"

directory="$1"

SRC="$1/main.c"

$CC $CFLAGS -o out $SRC

./out
