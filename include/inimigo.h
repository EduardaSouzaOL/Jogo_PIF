#ifndef INIMIGO_H
#define INIMIGO_H

#include "raylib.h"
#include <stdbool.h>

typedef struct Inimigo {
    Rectangle caixa;
    Vector2 velocidade;

    float limiteEsq;
    float limiteDir;

    bool vivo;
    int vida;

    bool especial;
    struct Inimigo *next;

    float tempoKnockback;   // <— ADICIONADO
} Inimigo;

void IniciarInimigos(Inimigo *v, int qtd, int dificuldade);
void AtualizarInimigos(Inimigo *v, int qtd, float dt);
void DesenharInimigos(Inimigo *v, int qtd);

#endif
