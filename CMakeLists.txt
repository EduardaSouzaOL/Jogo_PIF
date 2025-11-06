cmake_minimum_required(VERSION 3.16)
project(Jogo_PIF LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)
set(BUILD_TESTING  OFF CACHE BOOL "" FORCE)
set(RAYLIB_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(external/raylib)

add_executable(Jogo_PIF
  src/main.c
)

# No Windows, adiciona o shim e força subsystem=console no MinGW
if (WIN32)
  target_sources(Jogo_PIF PRIVATE src/winmain_shim.c)
  if (MINGW)
    target_link_options(Jogo_PIF PRIVATE -mconsole -Wl,-subsystem,console)
    target_link_libraries(Jogo_PIF PRIVATE gdi32 winmm opengl32)
  elseif (MSVC)
    target_link_options(Jogo_PIF PRIVATE /SUBSYSTEM:CONSOLE)
  endif()
elseif(APPLE)
  find_library(COCOA_FRAMEWORK Cocoa)
  find_library(IOKIT_FRAMEWORK IOKit)
  find_library(COREVIDEO_FRAMEWORK CoreVideo)
  target_link_libraries(Jogo_PIF PRIVATE ${COCOA_FRAMEWORK} ${IOKIT_FRAMEWORK} ${COREVIDEO_FRAMEWORK})
elseif(UNIX)
  find_package(Threads REQUIRED)
  target_link_libraries(Jogo_PIF PRIVATE m dl Threads::Threads)
endif()

target_link_libraries(Jogo_PIF PRIVATE raylib)

set_target_properties(Jogo_PIF PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)

message(STATUS "=> Build: ${CMAKE_BUILD_TYPE}")
