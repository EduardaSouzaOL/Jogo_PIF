cmake_minimum_required(VERSION 3.16)
project(Jogo_PIF C)

# Use C99
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Evita que o raylib baixe/compile exemplos
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Adiciona o raylib (como subdiretório do seu repo)
add_subdirectory(external/raylib)

# Seu executável
add_executable(Jogo_PIF
    src/main.c
)

# Linka com raylib
target_link_libraries(Jogo_PIF PRIVATE raylib)

# (Opcional) Definições de Windows mínimas — mantêm compatível com headers do Win32
if(WIN32)
    target_compile_definitions(Jogo_PIF PRIVATE WINVER=0x0601 _WIN32_WINNT=0x0601)
endif()

# Em Linux/Unix pode precisar de libs extras (raylib já cuida bem disso, mas por garantia):
if(UNIX AND NOT APPLE)
    find_package(Threads REQUIRED)
    target_link_libraries(Jogo_PIF PRIVATE m pthread dl rt)
endif()

# Sugestão de pasta de trabalho para rodar pelo CMake Tools/VSCode
set_property(TARGET Jogo_PIF PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")

# Mensagem amigável
message(STATUS "Compilando ${PROJECT_NAME} com raylib de external/raylib")
