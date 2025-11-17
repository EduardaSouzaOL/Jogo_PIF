cmake_minimum_required(VERSION 3.15)
project(Jogo_PIF C)

set(CMAKE_C_STANDARD 99)

# Diretório onde a Raylib está
set(RAYLIB_DIR "${CMAKE_SOURCE_DIR}/external/raylib")

# Adiciona raylib
add_subdirectory(${RAYLIB_DIR})

# Inclui seus headers
include_directories(include)

# Arquivos fonte do seu jogo
add_executable(Jogo_PIF
    src/main.c
    src/menu.c
    src/jogo.c
    src/jogador.c
    src/inimigo.c
    src/plataformas.c
    src/colisoes.c
    src/gameplay.c
)

# Linka raylib
target_link_libraries(Jogo_PIF raylib)

# Linkagem para Windows (MinGW)
if (WIN32)
    target_link_libraries(Jogo_PIF opengl32 gdi32 winmm)
endif()

# Linux (caso um dia use)
if (UNIX AND NOT APPLE)
    target_link_libraries(Jogo_PIF m pthread dl rt X11)
endif()
