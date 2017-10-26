cmake_minimum_required(VERSION 3.8)
project(jvm)

add_subdirectory(libs/libzip)
add_subdirectory(libs/docopt)
add_subdirectory(src)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O0 -lboost_system")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -lboost_system")
set(CMAKE_CXX_FLAGS_RELEASE "-O0 -lboost_system")

include_directories(libs/docopt)
include_directories(src)

link_directories("libs/docopt")
link_directories("src")
link_libraries(libdocopt.a)
link_libraries(libvm.a)

aux_source_directory(. JVM_SRC)
add_executable(jvm ${JVM_SRC})