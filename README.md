# 🎮 Projeto Raylib - Jogo PIF

Este é um projeto desenvolvido em **C**, usando a biblioteca **Raylib**, compatível com **Windows e Linux**, e organizado em estrutura colaborativa via **Git**.

## 📦 Estrutura do Projeto

```
📦 Jogo_PIF/
├── src/                 # Código-fonte (.c, .h)
├── assets/              # Imagens, sprites, músicas e efeitos
├── build/               # Pasta gerada automaticamente (IGNORADA no git)
├── RunGame.sh           # Script para Linux
├── RunGameWindows.bat   # Script para Windows
├── CMakeLists.txt
├── .gitignore
└── README.md
```

# 🧱 Requisitos do Sistema

As instruções abaixo mostram tudo o que é necessário para compilar e rodar o projeto **tanto no Linux quanto no Windows**.

# 🐧 Linux — Instalação, Build e Execução

## ✔ Instalar dependências

```bash
sudo apt update
sudo apt install build-essential cmake git libraylib-dev libgl1-mesa-dev libopenal-dev libpthread-stubs0-dev libx11-dev libxrandr-dev libxi-dev libxcursor-dev libxinerama-dev
```

## ✔ Verificar instalação da Raylib

```bash
pkg-config --libs raylib
```

## 🚀 Compilar e Rodar no Linux

```bash
chmod +x RunGame.sh
./RunGame.sh
```

# 🪟 Windows — Instalação, Build e Execução

## ✔ Instalar CMake

https://cmake.org/download/

## ✔ Instalar MinGW (gcc) + Raylib

Baixe de:
https://github.com/raysan5/raylib/releases/tag/5.0

Extraia em:
```
C:\raylib\mingw64
```

Adicione ao PATH:
```
C:\raylib\mingw64\bin
```

## 🚀 Compilar e Rodar no Windows

```
RunGameWindows.bat
```

# 🧠 Configurar no VSCode

- Instale C/C++
- Instale CMake Tools
- Configure e build pelo menu

# 🚀 Como Rodar o Jogo Manualmente

Linux:
```
cd build
./Jogo_PIF
```

Windows:
```
cd build
Jogo_PIF.exe
```

# 🧭 Fluxo de Contribuição (Git)

```bash
git checkout dev
git pull origin dev
git checkout -b feature/nome-da-tarefa
git add .
git commit -m "feat: adiciona novo sistema"
git push origin feature/nome-da-tarefa
```

# 🧹 Convenções Importantes

- Não commitar build/, executáveis, objetos
- Commits padronizados (feat, fix, refactor, chore)

# 📜 Licença

MIT

# 👩‍💻 Equipe

| Membro | Função | GitHub |
|--------|---------|--------|
| Maria Eduarda Souza de Oliveira | Programador(a) | https://github.com/EduardaSouzaOL |
| Danilo Araujo Duleba | Programador(a) | https://github.com/danduleba |
| Giovanna Karla Santos do Nascimento | Programador(a) | https://github.com/GihNascimento |
