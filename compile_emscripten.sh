#!/bin/sh -e

mkdir -p web
emcc -o web/ld30.js src/*.c libestk3.bc -I"../libestk/src" --preload-file media
cp html/* web

