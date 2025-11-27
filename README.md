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


---

## 🧱 Requisitos

### 🔹 Windows (MSYS2 + MinGW + Raylib)

1. Baixe e instale o **[MSYS2](https://www.msys2.org/)**.
2. Abra o terminal **MSYS2 UCRT64** e instale os pacotes necessários:

   ```bash
   pacman -Syu
   pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-cmake git
   pacman -S mingw-w64-ucrt-x86_64-raylib

Observação:
Você pode usar a Raylib fornecida pelo MSYS2, mas também pode usar uma versão manual da Raylib para MinGW.


## Caso prefira baixar manualmente a Raylib:


# Baixe a versão MinGW no repositório oficial:
https://github.com/raysan5/raylib/releases

### Extraia em:
```
   C:\raylib\raylib-5.5_win64_mingw-w64
```

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
./Jogo_PIF.exe     # Windows
./Jogo_PIF         # Linux
```




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

## 📜 Licença

Este projeto é distribuído sob a licença [MIT](https://opensource.org/licenses/MIT).

---

### 👩‍💻 Equipe

| Membro | Função | GitHub |
|--------|---------|--------|
| Maria Eduarda Souza de Oliveira | Programador(a) | [@EduardaOL](https://github.com/EduardaSouzaOL) |
| Danilo Araujo Duleba | Programador(a) | [@danduleba](https://github.com/danduleba) |
| Giovanna Karla Santos Do Nascimento | Programador(a) | [GihNascimento](https://github.com/GihNascimento) |

---

> 🧡 Desenvolvido com Raylib e trabalho em equipe!
