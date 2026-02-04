cmake_minimum_required(VERSION 3.20)
project(c_software_renderer C)

set(CMAKE_C_STANDARD 11)

file(COPY ${CMAKE_CURRENT_SOURCE_ID}assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(GLOB SOURCES
        "./src/assets/*.c"
        "./src/io/*.c"
        "./src/math/*.c"
        "./src/render/*.c"
        "./src/utility/*.c"
        "./src/core/*.c"
)

include_directories(
        src
        src/assets
        src/io
        src/math
        src/render
        src/utility
        src/core
)

add_executable(c_software_renderer ./src/main.c ${SOURCES})

add_executable(raylib_window ./src/raylib_window.c ${SOURCES})

set(RAYLIB_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/external/raylib-5.5/include")
set(RAYLIB_LIBRARY "${CMAKE_SOURCE_DIR}/external/raylib-5.5/lib/libraylib.a")

target_link_libraries(raylib_window PRIVATE ${RAYLIB_LIBRARY})
target_include_directories(raylib_window PRIVATE ${RAYLIB_INCLUDE_DIR})

if(UNIX)
    target_link_libraries(raylib_window PRIVATE m pthread dl rt)
endif()

