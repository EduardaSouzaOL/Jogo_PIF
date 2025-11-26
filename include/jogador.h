#ifndef JOGADOR_H
#define JOGADOR_H

#include "raylib.h"
#include <stdbool.h>

typedef enum {
    ESTADO_IDLE,
    ESTADO_ANDAR,
    ESTADO_PULO,
    ESTADO_AGACHAR
} EstadoJogador;

typedef enum {
    DIR_DIREITA,
    DIR_ESQUERDA
} DirecaoJogador;

typedef struct Jogador {
    Rectangle caixa;
    Vector2 velocidade;
    bool pulando;

    float tempoKnockback;
    float forcaKnockback;

    int chave;

    // ---- SPRITE ----
    Texture2D sprite;
    int frameWidth;
    int frameHeight;
    EstadoJogador estado;
    DirecaoJogador direcao;

    // ---- ANIMAÇÃO ----
    int animFrame;
    float animTimer;

} Jogador;

void InitJogador(Jogador *j);
void UpdateJogador(Jogador *j, float dt, float gravidade, float forcaPulo);
void DesenharJogador(Jogador *j);
void AplicarKnockbackJogador(Jogador *j, int direcao);

#endif
