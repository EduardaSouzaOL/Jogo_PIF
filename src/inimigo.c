#include "inimigo.h"

void Inimigo_Init(Inimigo *i, float x, float y, float width, float height,
                float LimiteEsquerda, float LimiteDireita)
{
    i->rect = (Rectangle){ x, y, width, height };
    i->velocidade = 60.0f;
    i->direcao = 1; // começa indo para a direita
    i->LimiteEsquerda = LimiteEsquerda;
    i->LimiteDireita = LimiteDireita;
}

void Inimigo_Update(Inimigo *i, float dt)
{
    // Move inimigo
    // *i ponteiro para a struct Inimigo, NAO É INDICE PELO AMOR DE DEUS
    i->rect.x += i->velocidade * i->direcao * dt;

    // Checa limites da plataforma
    if (i->rect.x <= i->LimiteEsquerda) {
        i->rect.x = i->LimiteEsquerda;
        i->direcao = 1; // vira para a direita
    }

    if (i->rect.x + i->rect.width >= i->LimiteDireita) {
        i->rect.x = i->LimiteDireita - i->rect.width;
        i->direcao = -1; // vira para a esquerda
    }
}

void Inimigo_Draw(const Inimigo *i)
{
    DrawRectangleRec(i->rect, RED);
}
