cmake_minimum_required(VERSION 3.15)
project(Jogo_PIF C)

set(CMAKE_C_STANDARD 99)

# Caminho da Raylib (ajuste se necessário)
set(RAYLIB_DIR "${CMAKE_SOURCE_DIR}/external/raylib")

add_subdirectory(${RAYLIB_DIR})

add_executable(Jogo_PIF src/main.c)

target_link_libraries(Jogo_PIF raylib)

# No Windows
if (WIN32)
    target_link_libraries(Jogo_PIF opengl32 gdi32 winmm)
endif()
