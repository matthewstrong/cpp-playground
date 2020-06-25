cmake_minimum_required (VERSION 3.15)
project (cpp-playground)

include (cmake/Dependencies.cmake)
include (GoogleTest)
enable_testing ()

add_subdirectory (src)
add_subdirectory (tests)
