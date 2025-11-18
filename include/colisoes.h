#ifndef COLISOES_H
#define COLISOES_H

#include "raylib.h"
#include <stdbool.h>

void ResolverColisaoChao(Rectangle *jogador, Vector2 *velocidade, Rectangle  chao, bool *pulando);

void ResolverColisaoPlataformas(Rectangle *jogador, Vector2   *velocidade, Rectangle *plataformas, int qtd, bool *pulando, bool descer);

bool ColisaoTotal(Rectangle a, Rectangle b);

#endif
