cmake_minimum_required(VERSION 3.15)
project(Jogo_PIF C)

set(CMAKE_C_STANDARD 99)

# Diretório da Raylib (clonada em external/raylib)
set(RAYLIB_DIR "${CMAKE_SOURCE_DIR}/external/raylib")

# Adicionar Raylib ao projeto
add_subdirectory(${RAYLIB_DIR})

# Diretório dos seus headers
include_directories(include)

# Arquivos-fonte do jogo
add_executable(Jogo_PIF
    src/main.c
    src/menu.c
    src/jogo.c
    src/jogador.c
    src/inimigo.c
    src/plataformas.c
    src/colisoes.c
    src/gameplay.c
    src/placar.c
    src/intro.c
)

# Linkar Raylib primeiro
target_link_libraries(Jogo_PIF raylib)

# Dependência: Raylib precisa ser compilada antes do jogo
add_dependencies(Jogo_PIF raylib)

# Linkagem Windows (MinGW)
if (WIN32)
    target_link_libraries(Jogo_PIF opengl32 gdi32 winmm)
endif()

# Linkagem Linux
if (UNIX AND NOT APPLE)
    target_link_libraries(Jogo_PIF m pthread dl rt X11)
endif()
