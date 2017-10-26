cmake_minimum_required(VERSION 3.8)
project(vm)

set(CMAKE_CXX_STANDARD 17)

include_directories(../libs/docopt)
include_directories(../libs/libzip/lib)

link_directories("../libs/docopt")
link_directories("../libs/libzip/lib")
link_libraries(libdocopt.a)
link_libraries(libzip.a)

aux_source_directory(. JVM_SRC)

add_library(vm ${JVM_SRC})