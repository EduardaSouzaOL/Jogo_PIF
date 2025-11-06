# Requer PowerShell 5+ e Mingw64 no PATH
Write-Host "Building project for Windows..."

# Limpa build
Remove-Item -Recurse -Force build -ErrorAction SilentlyContinue

# Gera build com MinGW
cmake -B build -G "MinGW Makefiles" `
    -DCMAKE_C_COMPILER=C:\mingw64\bin\gcc.exe `
    -DCMAKE_CXX_COMPILER=C:\mingw64\bin\g++.exe

# Compila
cmake --build build -j

# Executa
.\build\Jogo_PIF.exe
