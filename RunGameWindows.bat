@echo off
setlocal

echo ============================================
echo   COMPILANDO Jogo_PIF (Windows)
echo ============================================
echo.

if not exist build (
    mkdir build
)

cd build

cmake .. -G "MinGW Makefiles"
if %errorlevel% neq 0 (
    echo [ERRO] CMake falhou.
    pause
    exit /b
)

mingw32-make
if %errorlevel% neq 0 (
    echo [ERRO] Make falhou.
    pause
    exit /b
)

echo ============================================
echo   EXECUTANDO Jogo_PIF.exe
echo ============================================
echo.

Jogo_PIF.exe

cd ..
pause
