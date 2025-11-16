cmake_minimum_required(VERSION 3.15)
project(Jogo_PIF C)

set(CMAKE_C_STANDARD 99)

# Caminho da Raylib (ajuste se necessário)
set(RAYLIB_DIR "${CMAKE_SOURCE_DIR}/external/raylib")

# Compila a Raylib dentro do projeto
add_subdirectory(${RAYLIB_DIR})

# Incluir diretório de headers do seu jogo
include_directories(include)

# ---------------------------
# Arquivos .c do seu jogo
# ---------------------------
add_executable(Jogo_PIF
    src/main.c
    src/menu.c
    src/inimigo.c
)

# Linkar raylib
target_link_libraries(Jogo_PIF raylib)

# ---------------------------
# Dependências extras por SO
# ---------------------------
if (WIN32)
    target_link_libraries(Jogo_PIF opengl32 gdi32 winmm)
endif()

if (UNIX AND NOT APPLE)
    target_link_libraries(Jogo_PIF m pthread dl rt X11)
endif()
