#ifndef INIMIGO_H
#define INIMIGO_H

#include "raylib.h"

typedef struct {
    Rectangle rect;     // Posição e tamanho do inimigo
    float velocidade;        // Velocidade de movimento
    int direcao;      // -1 = esquerda, +1 = direita
    float LimiteEsquerda;    // Limite da esquerda da plataforma
    float LimiteDireita;   // Limite da direita da plataforma
} Inimigo;

// Inicializa um inimigo na posição desejada com patrol horizontal
void Inimigo_Init(Inimigo *i, float x, float y, float width, float height, float LimiteEsquerda, float LimiteDireita);

// Atualiza o movimento do inimigo
void Inimigo_Update(Inimigo *i, float dt);

// Desenha o inimigo
void Inimigo_Draw(const Inimigo *i);

#endif
