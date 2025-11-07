# 🎮 Projeto Raylib - Jogo Colaborativo

Este é um projeto desenvolvido em **C** usando a biblioteca **[Raylib](https://www.raylib.com/)**, com suporte multiplataforma (**Windows + Linux**) e gerenciamento colaborativo via **Git**.

---

## 🧩 Estrutura do Projeto

```
📦 projeto-raylib/
├── src/              # Código-fonte (.c, .h)
├── assets/           # Imagens, sons, fontes etc.
├── CMakeLists.txt    # Configuração do build
├── build/            # Pasta gerada pelo CMake (IGNORADA no git)
├── .gitignore
└── README.md
```

---

## 🧱 Requisitos

### 🔹 Windows (MSYS2 + MinGW + Raylib)

1. Baixe e instale o [MSYS2](https://www.msys2.org/)
2. Abra o terminal **MSYS2 UCRT64** e rode:

   ```bash
   pacman -Syu
   pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-make
   ```

3. Baixe a **Raylib 5.5 para Windows (MinGW)** e extraia em:
   ```
   C:\raylib\raylib-5.5_win64_mingw-w64
   ```

4. Adicione o caminho aos includes e libs no `CMakeLists.txt`:
   ```cmake
   include_directories("C:/raylib/raylib-5.5_win64_mingw-w64/include")
   link_directories("C:/raylib/raylib-5.5_win64_mingw-w64/lib")
   ```

---

### 🔹 Linux (Debian/Ubuntu ou derivados)

1. Instale Raylib e dependências:
   ```bash
   sudo apt update
   sudo apt install build-essential cmake git libgl1-mesa-dev libopenal-dev libpthread-stubs0-dev libx11-dev libxrandr-dev libxi-dev libxcursor-dev libxinerama-dev libraylib-dev
   ```

2. Verifique se o Raylib está disponível:
   ```bash
   pkg-config --libs raylib
   ```

---

## 🧠 Configurando no VSCode

1. Instale as extensões:
   - **C/C++** (Microsoft)
   - **CMake Tools**
   - **CodeLLDB** (opcional para debug)
2. Abra o projeto no VSCode
3. Pressione `Ctrl + Shift + P` e selecione:
   ```
   CMake: Configure
   CMake: Build
   ```
4. O executável será gerado dentro de `build/`

---

## 🚀 Como Rodar o Jogo

No terminal do VSCode (ou MSYS2/Linux):

```bash
cd build
./nome_do_jogo.exe     # Windows
./nome_do_jogo         # Linux
```

---

## 👥 Fluxo Colaborativo (Git)

### 🌳 Branches principais
| Branch | Função |
|---------|--------|
| `main` | Versão estável (entregas testadas) |
| `dev` | Integração de recursos em desenvolvimento |
| `feature/*` | Branches individuais de cada pessoa |

---

### 🧭 Passo a passo para contribuir

1. Atualize o projeto:
   ```bash
   git checkout dev
   git pull origin dev
   ```

2. Crie sua branch:
   ```bash
   git checkout -b feature/nome-da-tarefa
   ```

3. Faça as alterações e commits:
   ```bash
   git add .
   git commit -m "feat: adiciona tela inicial"
   git push origin feature/nome-da-tarefa
   ```

4. Abra um **Pull Request** para `dev`
5. Após revisão, o líder faz o merge

---

## 🧹 Convenções

- Nunca commitar arquivos de build (`/build`, `.exe`, `.dll`, `.o`, etc)
- Commits padronizados:
  ```
  feat: adiciona menu inicial
  fix: corrige erro na colisão
  refactor: melhora loop principal
  chore: atualiza dependências
  ```
- Código deve **compilar antes de enviar**

---

## 🧰 .gitignore

```gitignore
# --- Build ---
build/
*.o
*.obj
*.exe
*.dll
*.lib
*.a
*.so
*.out

# --- CMake ---
CMakeFiles/
CMakeCache.txt
cmake_install.cmake
Makefile

# --- VSCode ---
.vscode/
.vscode/settings.json

# --- Sistema ---
.DS_Store
Thumbs.db
desktop.ini

# --- Temporários ---
*.log
*.tmp
*.bak
```

---

## 📜 Licença

Este projeto é distribuído sob a licença [MIT](https://opensource.org/licenses/MIT).

---

### 👩‍💻 Equipe

| Membro | Função | GitHub |
|--------|---------|--------|
| Nome 1 | Programador(a) | [@nome1](https://github.com/nome1) |
| Nome 2 | Programador(a) | [@nome2](https://github.com/nome2) |
| Nome 3 | Programador(a) | [@nome3](https://github.com/nome3) |

---

> 🧡 Desenvolvido com Raylib e trabalho em equipe!
