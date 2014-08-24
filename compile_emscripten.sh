#!/bin/sh

emcc -o bin/ld30.html src/*.c libestk3.bc -I"../libestk/src" --preload-file media

