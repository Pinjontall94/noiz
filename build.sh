#!/bin/sh

set -xe

CFLAGS="-Wall -Wextra -Werror -pedantic -std=c99 -fsanitize=address -ggdb -O0 $(pkg-config --cflags sdl2)"
LIBS="$(pkg-config --libs sdl2)"

zig cc "$CFLAGS" noiz.c -o noiz "$LIBS"
