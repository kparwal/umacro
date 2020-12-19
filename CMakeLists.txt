cmake_minimum_required(VERSION 2.8.12)
project(umacro)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTEST REQUIRED IMPORTED_TARGET gtest)

add_executable(test_umacro test/test.cpp)
target_include_directories(test_umacro PUBLIC umacro ${GTEST_INCLUDE_DIRS}/gtest)
target_link_libraries(test_umacro PUBLIC ${GTEST_LDFLAGS})
