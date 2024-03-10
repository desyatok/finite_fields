cmake_minimum_required(VERSION 3.22)
project(finite_fields C)

set(CMAKE_C_STANDARD 11)

add_library(finite_fields STATIC library.c)
