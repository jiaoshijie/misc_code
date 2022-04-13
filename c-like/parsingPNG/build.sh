#!/usr/bin/env sh

set -xe

cc -Wall -Wextra -o demo png.c && ./demo ./t.png
