cmake_minimum_required(VERSION 3.20)
project(check_toolchain C CXX ASM)

message(STATUS "CMAKE_C_COMPILER = ${CMAKE_C_COMPILER}")
message(STATUS "CMAKE_CXX_COMPILER = ${CMAKE_CXX_COMPILER}")
message(STATUS "CMAKE_ASM_COMPILER = ${CMAKE_ASM_COMPILER}")

if(NOT CMAKE_C_COMPILER)
  message(FATAL_ERROR "C compiler not found")
endif()