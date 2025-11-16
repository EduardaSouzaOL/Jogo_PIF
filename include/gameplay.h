#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "raylib.h"
#include <stdbool.h>

typedef struct JogadorGameplay {
    Vector2 posicao;
    Vector2 velocidade;
    float velocidade_escalar;
    bool no_chao;
    Rectangle caixa_colisao;
    int vidas;
} JogadorGameplay;

typedef struct Nivel {
    Rectangle *plataformas;
    int quantidade_plataformas;
    Texture2D fundo;
} Nivel;

void GameplayInit(void);
void GameplayUpdate(float dt);
void GameplayDraw(void);
void GameplayUnload(void);

#endif

// controle de estado
// void LoadLevel(const char *filename);
// void ResetPlayer(void);