#ifndef JOGADOR_H
#define JOGADOR_H

#include "raylib.h"
#include <stdbool.h>

typedef struct Jogador {
    Rectangle hitbox;
    Vector2 velocidade;
    bool pulando;
    bool vivo;
} Jogador;

void InitJogador(Jogador *jogador);
void AtualizarJogador(Jogador *jogador, float dt);

#endif
