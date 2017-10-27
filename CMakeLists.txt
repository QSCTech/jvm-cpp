cmake_minimum_required(VERSION 3.8)
project(jvm)

add_subdirectory(libs/docopt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O0 -lboost_system -lboost_filesystem")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -lboost_system -lboost_filesystem")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -lboost_system -lboost_filesystem")
aux_source_directory(src JVM_SRC)
add_library(vm ${JVM_SRC})
include_directories(libs/libzip)
include_directories(libs/docopt)
include_directories(src)

link_directories("libs/docopt")
link_directories("./")

link_libraries(libdocopt.a)
link_libraries(libvm.a)
link_libraries(libzip.a)

add_executable(jvm main.cpp)