#ifndef JOGADOR_H
#define JOGADOR_H

#include "raylib.h"
#include <stdbool.h>

typedef struct Jogador {
    Rectangle caixa;
    Vector2 velocidade;
    bool pulando;

    /* campos para knockback */
    float tempoKnockback;   // tempo restante de knockback
    float forcaKnockback;   // força atual do knockback
} Jogador;

void InitJogador(Jogador *j);
void UpdateJogador(Jogador *j, float dt, float gravidade, float forcaPulo);
void DesenharJogador(Jogador *j);

/* aplica knockback ao jogador; direcao = -1 ou 1 (use conforme seu jogo) */
void AplicarKnockbackJogador(Jogador *j, int direcao);

#endif
