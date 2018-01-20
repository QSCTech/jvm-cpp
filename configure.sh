#!/usr/bin/env bash
echo "############# need git, make, cmake and g++ in your PATH #############"
echo "dependence: libzip, docopt"

echo "git clone https://github.com/nih-at/libzip.git libzip"
git clone https://github.com/nih-at/libzip.git libzip

echo "git clone https://github.com/docopt/docopt.cpp.git docopt"
git clone https://github.com/docopt/docopt.cpp.git docopt

cd libzip
cmake .

cd ..
cmake .

cd docopt
make

cd ..
make