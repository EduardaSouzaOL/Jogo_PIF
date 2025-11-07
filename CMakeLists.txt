cmake_minimum_required(VERSION 3.16)
project(Jogo_PIF C)

set(CMAKE_C_STANDARD 11)

# Adiciona código-fonte
add_executable(Jogo_PIF src/main.c)

# Detecta Raylib automaticamente ou permite caminho manual
if (WIN32)
    # Caminho para sua Raylib local (ajuste conforme necessário)
    set(RAYLIB_DIR "C:/raylib/raylib-5.5_win64_mingw-w64")
    target_include_directories(Jogo_PIF PRIVATE ${RAYLIB_DIR}/include)
    target_link_directories(Jogo_PIF PRIVATE ${RAYLIB_DIR}/lib)
    target_link_libraries(Jogo_PIF raylib opengl32 gdi32 winmm)
elseif(UNIX)
    find_package(raylib REQUIRED)
    target_link_libraries(Jogo_PIF raylib m pthread)
endif()
