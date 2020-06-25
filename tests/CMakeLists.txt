set(CMAKE_CXX_STANDARD 17)

include_directories (../include/)
include_directories (${Boost_INCLUDE_DIRS})
include_directories (${googletest_SOURCE_DIR})

add_executable (MyTests EnumHelper_test.cpp)
target_compile_options (MyTests PRIVATE -Werror=switch-enum)
target_link_libraries (MyTests gtest gtest_main)

gtest_discover_tests (MyTests)
