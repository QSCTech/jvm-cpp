#!/usr/bin/env bash
echo "############# need 'git' in your PATH #############"
echo "git path: $(whereis git)"
echo "dependence: libzip, docopt"
LIBDIR="./libs"
if [ ! -d $LIBDIR ]; then
  mkdir $LIBDIR
fi

echo "git clone git@github.com:nih-at/libzip.git ./libs/libzip"
git clone git@github.com:nih-at/libzip.git ./libs/libzip

echo "git clone git@github.com:docopt/docopt.cpp.git ./libs/docopt"
git clone git@github.com:docopt/docopt.cpp.git ./libs/docopt

cd ./libs/libzip/
cmake ./

cd ../../
cmake ./

cd ./libs/docopt/
make

cd ../../
make