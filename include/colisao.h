#ifndef COLISAO_H
#define COLISAO_H

#include "raylib.h"
#include "jogador.h"
#include "inimigo.h"

// --- Jogador x Plataforma ---
void ColisaoJogadorPlataformas(Jogador *j, Rectangle *plataformas, int qtd);

// --- Jogador x Inimigo ---
void ColisaoJogadorInimigo(Jogador *j, Inimigo *i);

#endif