#ifndef COLISOES_H
#define COLISOES_H

#include "raylib.h"
#include <stdbool.h>

// Para usar struct Plataforma*
struct Plataforma;

void ResolverColisaoChao(Rectangle *jogador, Vector2 *velocidade, Rectangle chao, bool *pulando);

void ResolverColisaoPlataformas(Rectangle *jogador, Vector2 *velocidade,
                                Rectangle *plataformas, int qtd,
                                bool *pulando, bool descer);

// ✔ nova função com lista encadeada
void ResolverColisaoPlataformasLista(Rectangle *jogador, Vector2 *velocidade,
                                     struct Plataforma *lista,
                                     bool *pulando, bool descer);

bool ColisaoTotal(Rectangle a, Rectangle b);

#endif
