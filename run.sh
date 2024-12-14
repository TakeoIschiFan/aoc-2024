clear

set -xe

CC="clang"
CFLAGS="-g -Wall -Wextra -pedantic -lm"

directory="$1"

SRC="$1/main.c common/*.c"

$CC $CFLAGS -o out $SRC 

./out
