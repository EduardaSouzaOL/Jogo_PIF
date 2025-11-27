#!/bin/bash

# Ir para o diretório onde o script está
cd "$(dirname "$0")"

echo "========================================"
echo "     JOGO PIF - COMPILAÇÃO & EXECUÇÃO   "
echo "========================================"
echo ""

# Verifica se a pasta build existe, senão cria
if [ ! -d "build" ]; then
    echo "[INFO] Pasta 'build/' não encontrada. Criando..."
    mkdir build
fi

# Verifica se o executável existe
if [ ! -f "build/Jogo_PIF" ]; then
    echo "[INFO] Executável não encontrado. Compilando o jogo..."
    cmake -B build
    cmake --build build

    # Verifica se compilou corretamente
    if [ ! -f "build/Jogo_PIF" ]; then
        echo ""
        echo "[ERRO] Falha ao compilar o jogo!"
        echo "Verifique se o CMake e o compilador estão instalados."
        exit 1
    fi
else
    echo "[INFO] Executável encontrado. Compilação não necessária."
fi

echo ""
echo "========================================"
echo "              INICIANDO JOGO            "
echo "========================================"
echo ""

# Executa o jogo
./build/Jogo_PIF
