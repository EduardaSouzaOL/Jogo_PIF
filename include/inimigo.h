#ifndef INIMIGO_H
#define INIMIGO_H

#include "raylib.h"

typedef struct Inimigo {
    Rectangle caixa;
    Vector2 velocidade;
    float limiteEsq;
    float limiteDir;
    float tempoKnockback;
    int vida;
    bool vivo;
} Inimigo;

void IniciarInimigos(Inimigo *v, int qtd, int dificuldade, float limiteGeracao);
void AtualizarInimigos(Inimigo *v, int qtd, float dt);
void DesenharInimigos(Inimigo *v, int qtd);

#endif
