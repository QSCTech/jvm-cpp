echo "############# need git, mingw32-make, cmake and g++ in your PATH #############"
echo "dependence: libzip, docopt"

echo "git clone git@github.com:nih-at/libzip.git libzip"
git clone git@github.com:nih-at/libzip.git libzip

echo "git clone git@github.com:docopt/docopt.cpp.git docopt"
git clone git@github.com:docopt/docopt.cpp.git docopt

cd libzip
cmake . -G "MinGW Makefiles"

cd ..
cmake . -G "MinGW Makefiles"

cd docopt
mingw32-make

cd ..
mingw32-make