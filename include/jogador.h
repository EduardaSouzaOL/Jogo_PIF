#ifndef JOGADOR_H
#define JOGADOR_H

#include "raylib.h"
#include <stdbool.h>

typedef struct Jogador {
    Rectangle caixa;
    Vector2 velocidade;
    bool pulando;

    float tempoKnockback;
    float forcaKnockback;

    int chave;    // <--- chave coletada de inimigo especial
} Jogador;

void InitJogador(Jogador *j);
void UpdateJogador(Jogador *j, float dt, float gravidade, float forcaPulo);
void DesenharJogador(Jogador *j);
void AplicarKnockbackJogador(Jogador *j, int direcao);

#endif
