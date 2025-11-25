#ifndef INIMIGO_H
#define INIMIGO_H

#include "raylib.h"
#include <stdbool.h>

// Texturas dos inimigos (declarar como extern)
extern Texture2D texCoelho;
extern Texture2D texLobo;
extern Texture2D texLeao;

// Funções para carregar/descarregar texturas
void CarregarTexturasInimigos(void);
void DescarregarTexturasInimigos(void);

// Tipos de inimigos (animais)
typedef enum {
    TIPO_COELHO = 1,
    TIPO_LOBO = 2,
    TIPO_LEAO = 3
} TipoInimigo;

typedef struct Inimigo {
    Rectangle caixa;
    Vector2 velocidade;
    float limiteEsq;
    float limiteDir;
    float tempoKnockback;
    int vida;
    bool vivo;
    TipoInimigo tipo; // NOVO: tipo do animal
} Inimigo;

void IniciarInimigos(Inimigo *v, int qtd, int dificuldade, float limiteGeracao);
void AtualizarInimigos(Inimigo *v, int qtd, float dt);
void DesenharInimigos(Inimigo *v, int qtd);


#endif
