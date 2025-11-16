#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "raylib.h"

typedef struct Player {
    Vector2 posicao;
    Vector2 velocidade;
    float velocidade;
    bool esta_no_chao;
    Rectangle hitbox;
    int vidas;

} Player;

typedef struct Nivel {
    Rectangle *plataformas;
    int contagem_plataformas;
    Texture2D fundo;

} Nivel;


void GameplayInit(void);
void GameplayUpdate(float dt);
void GameplayDraw(void);
void GameplayUnload(void);

// controle de estado
// void LoadLevel(const char *filename);
// void ResetPlayer(void);