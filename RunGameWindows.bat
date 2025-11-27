@echo off
setlocal enabledelayedexpansion

echo ============================================
echo   Jogo_PIF - Compilar e Executar
echo ============================================
echo.

REM --------------------------------------------------
REM TESTE 1: CMAKE EXISTE?
REM --------------------------------------------------
where cmake >nul 2>&1
if %errorlevel% neq 0 (
    echo [ERRO] CMake nao encontrado!
    echo Instale o CMake aqui: https://cmake.org/download/
    pause
    exit /b
)
echo [OK] CMake encontrado.

REM --------------------------------------------------
REM TESTE 2: GCC (MINGW) EXISTE?
REM --------------------------------------------------
where gcc >nul 2>&1
if %errorlevel% neq 0 (
    echo [ERRO] MinGW (gcc) nao encontrado!
    echo Instale o MinGW ou adicione ao PATH.
    echo Baixar Raylib + MinGW oficial:
    echo https://github.com/raysan5/raylib/releases/download/5.0/mingw64.zip
    pause
    exit /b
)
echo [OK] GCC encontrado.

REM --------------------------------------------------
REM CRIAR PASTA DE BUILD
REM --------------------------------------------------
if not exist build (
    mkdir build
)

cd build

echo ============================================
echo   Rodando CMake...
echo ============================================

cmake .. -G "MinGW Makefiles"
if %errorlevel% neq 0 (
    echo [ERRO] Falha ao gerar com CMake!
    pause
    exit /b
)

echo ============================================
echo   Compilando o Jogo...
echo ============================================

mingw32-make
if %errorlevel% neq 0 (
    echo [ERRO] Falha ao compilar o jogo!
    pause
    exit /b
)

echo ============================================
echo   Executando Jogo_PIF.exe...
echo ============================================

Jogo_PIF.exe
cd ..

pause
exit /b
