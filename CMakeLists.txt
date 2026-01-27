cmake_minimum_required(VERSION 3.20)
project(c_software_renderer C)

set(CMAKE_C_STANDARD 11)

file(COPY ${CMAKE_CURRENT_SOURCE_ID}assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(GLOB SOURCES
        "./src/main.c"
        "./src/assets/*.c"
        "./src/io/*.c"
        "./src/math/*.c"
        "./src/render/*.c"
        "./src/utility/*.c"
)

include_directories(
        src
        src/assets
        src/io
        src/math
        src/render
        src/utility
)

add_executable(c_software_renderer ${SOURCES})