#!/bin/sh

cp resources/lena.png ./out.png
./a.out out.png 3
./a.out out.png 1
feh ./out.png

