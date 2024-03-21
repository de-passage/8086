cmake_minimum_required(VERSION 3.28)

project(8086Disassembler)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()


add_executable(dis
  src/main.cpp)

add_custom_target(run
  DEPENDS dis
  COMMAND ${CMAKE_BINARY_DIR}/dis)

add_subdirectory(tests)
