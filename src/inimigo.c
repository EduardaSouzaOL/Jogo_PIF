#include "inimigo.h"

void Inimigo_Init(Inimigo *i, float x, float y, float w, float h, float esq, float dir)
{
    i->rect = (Rectangle){x, y, w, h};
    i->velocidade = 60;
    i->direcao = 1;
    i->LimiteEsquerda = esq;
    i->LimiteDireita  = dir;
    i->ta_vivo = true;
    i->colisao_lateral_comJogador = 0;
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
