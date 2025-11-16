#include "gameplay.h"
#include "raylib.h"
#include <stdlib.h>

// estaticos, não visiveis fora deste arquivo
static Player jogador; // jogador principal, saiu de uma estrutura definida em gameplay.h
static Nivel nivelAtual; // nivel atual do jogo, guarda as plataformas e o fundo
static Camera2D camera; // camera do jogo, visão do jogador
static float gravidade = 0.45f;     // força da gravidade plmds
