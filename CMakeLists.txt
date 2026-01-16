cmake_minimum_required(VERSION 3.20)
project(engine C)

set(CMAKE_C_STANDARD 11)

file(GLOB_RECURSE SOURCES "*.c" "*.h")

add_executable(engine ${SOURCES})

include_directories(.)