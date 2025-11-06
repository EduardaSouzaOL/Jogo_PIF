#!/bin/bash
set -e

# Instala dependências se não existirem (de forma básica)
if ! dpkg -s build-essential cmake libasound2-dev libx11-dev &>/dev/null; then
    echo "Instalando dependências raylib..."
    sudo apt update
    sudo apt install -y build-essential cmake \
        libasound2-dev libx11-dev libxrandr-dev libxi-dev \
        libxinerama-dev libxcursor-dev
fi

# Build
rm -rf build
cmake -B build
cmake --build build -j

# Run
./build/Jogo_PIF
