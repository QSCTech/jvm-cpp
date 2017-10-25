cmake_minimum_required(VERSION 3.8)
project(jvm)

add_subdirectory(libs/docopt)

set(CMAKE_CXX_STANDARD 14)
include_directories(libs/docopt)
include_directories(src)

link_directories("libs/docopt")
link_libraries(libdocopt.a)

aux_source_directory(./src JVM_SRC)
aux_source_directory(. JVM_SRC)

add_executable(jvm ${JVM_SRC})