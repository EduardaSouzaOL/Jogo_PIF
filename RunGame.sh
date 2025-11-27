#!/bin/bash

echo "============================================"
echo "      COMPILANDO Jogo_PIF (Linux)"
echo "============================================"
echo ""

# Criar pasta build se não existir
if [ ! -d "build" ]; then
    mkdir build
fi

cd build

# Rodar cmake
cmake ..
if [ $? -ne 0 ]; then
    echo "[ERRO] CMake falhou."
    exit 1
fi

# Compilar
make
if [ $? -ne 0 ]; then
    echo "[ERRO] Make falhou."
    exit 1
fi

echo "============================================"
echo "     EXECUTANDO ./Jogo_PIF"
echo "============================================"
echo ""

./Jogo_PIF
cd ..
