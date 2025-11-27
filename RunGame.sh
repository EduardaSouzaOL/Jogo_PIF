#!/bin/bash

echo "============================================"
echo "      Jogo_PIF - Compilar e Executar"
echo "============================================"
echo ""

# --------------------------------------------------
# TESTE 1: CMAKE EXISTE?
# --------------------------------------------------
if ! command -v cmake &> /dev/null
then
    echo "[ERRO] CMake não encontrado!"
    echo "Instale com:"
    echo "  sudo apt install cmake"
    exit 1
fi
echo "[OK] CMake encontrado."

# --------------------------------------------------
# TESTE 2: GCC EXISTE?
# --------------------------------------------------
if ! command -v gcc &> /dev/null
then
    echo "[ERRO] GCC (build-essential) não encontrado!"
    echo "Instale com:"
    echo "  sudo apt install build-essential"
    exit 1
fi
echo "[OK] GCC encontrado."

# --------------------------------------------------
# TESTE 3: RAYLIB EXISTE?
# --------------------------------------------------
if ! ldconfig -p | grep -q raylib
then
    echo "[ERRO] Raylib não encontrada no sistema!"
    echo "Instale com:"
    echo "  sudo apt install libraylib-dev"
    echo ""
    exit 1
fi
echo "[OK] Raylib encontrada."

# --------------------------------------------------
# CRIAR PASTA BUILD
# --------------------------------------------------
if [ ! -d "build" ]; then
    mkdir build
fi

cd build

echo "============================================"
echo "          Rodando CMake..."
echo "============================================"

cmake .. 
if [ $? -ne 0 ]; then
    echo "[ERRO] Falha ao gerar projeto com CMake!"
    exit 1
fi

echo "============================================"
echo "          Compilando o Jogo..."
echo "============================================"

make
if [ $? -ne 0 ]; then
    echo "[ERRO] Falha ao compilar!"
    exit 1
fi

echo "============================================"
echo "         Executando Jogo_PIF..."
echo "============================================"

./Jogo_PIF
cd ..

exit 0
