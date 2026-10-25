cmake_minimum_required(VERSION 3.20)
project(c_software_renderer C)

set(CMAKE_C_STANDARD 11)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

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

if(APPLE)
    set(RAYLIB_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/external/raylib-6.2_macos/include")
    set(RAYLIB_LIBRARY "${CMAKE_SOURCE_DIR}/external/raylib-6.2_macos/lib/libraylib.a")

elseif(UNIX)
    set(RAYLIB_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/external/raylib-5.5/include")
    set(RAYLIB_LIBRARY "${CMAKE_SOURCE_DIR}/external/raylib-5.5/lib/libraylib.a")
endif()



target_link_libraries(raylib_window PRIVATE ${RAYLIB_LIBRARY})
target_include_directories(raylib_window PRIVATE ${RAYLIB_INCLUDE_DIR})



if(APPLE)
    target_link_libraries(raylib_window PRIVATE
        "-framework Cocoa"
        "-framework OpenGL"
        "-framework QuartzCore"
        "-framework Metal"
        "-framework IOKit"
        "-framework CoreVideo")

elseif(UNIX)
    target_link_libraries(raylib_window PRIVATE
        m
        pthread
        dl
        rt)
endif()
