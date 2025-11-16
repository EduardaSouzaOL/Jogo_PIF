#include "gameplay.h"
#include "raylib.h"
#include <stdlib.h>

// estaticos, não visiveis fora deste arquivo
static Player jogador; // jogador principal, saiu de uma estrutura definida em gameplay.h
static Nivel nivelAtual; // nivel atual do jogo, guarda as plataformas e o fundo
static Camera2D camera; // camera do jogo, visão do jogador
static float gravidade = 0.45f;     // força da gravidade plmds

// funções privadas, apenas nesse arquivo
static void InitJogador(void);
static void UpdateFisica(float dt);
static void CheckColisoes(void);

// funções públicas, visiveis em gameplay.h
void GameplayInit(void){
    
}