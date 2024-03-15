cmake_minimum_required(VERSION 3.22)
project(finite_fields C)

set(CMAKE_C_STANDARD 11)

add_library(finite_fields STATIC library.c)
add_library(minunit INTERFACE minunit.h)

add_executable(tests tests.c)

target_link_libraries(tests finite_fields minunit)

enable_testing()
add_test(test_pack tests)
