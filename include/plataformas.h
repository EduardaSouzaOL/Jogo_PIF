#ifndef PLATAFORMAS_H
#define PLATAFORMAS_H
#include <stdlib.h>

#include "raylib.h"

// Estrutura da lista encadeada
typedef struct Plataforma {
    Rectangle rect;
    struct Plataforma *next;
} Plataforma;

// Gera lista de plataformas
Plataforma *GerarPlataformas(int qtd, int dificuldade, float limiteGeracao);

// Desenha lista inteira
void DesenharPlataformas(Plataforma *lista);

// Libera memória
void LiberarPlataformas(Plataforma *lista);

#endif
