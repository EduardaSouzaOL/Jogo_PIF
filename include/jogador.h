#ifndef JOGADOR_H
#define JOGADOR_H

#include "raylib.h"
#include <stdbool.h>

typedef struct Jogador {
    Rectangle caixa_colisao;
    Vector2 velocidade;
    bool pulando;
    bool vivo;
} Jogador;

void InicializarJogador(Jogador *jogador);
void AtualizarJogador(Jogador *jogador, float delta);

#endif
