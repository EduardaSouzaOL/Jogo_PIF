#include "jogador.h"

void InitJogador(Jogador *j)
{
    j->caixa = (Rectangle){ 100, 400, 40, 50 };
    j->velocidade = (Vector2){ 0, 0 };
    j->pulando = false;
    j->vivo = true;
}

void UpdateJogador(Jogador *j, float dt, float gravidade, float forcaPulo)
{
    if (IsKeyDown(KEY_RIGHT)) j->velocidade.x = 200;
    else if (IsKeyDown(KEY_LEFT)) j->velocidade.x = -200;
    else j->velocidade.x = 0;

    if (IsKeyPressed(KEY_UP) && !j->pulando)
    {
        j->velocidade.y = forcaPulo;
        j->pulando = true;
    }

    j->velocidade.y += gravidade * dt;

    j->caixa.x += j->velocidade.x * dt;
    j->caixa.y += j->velocidade.y * dt;
}

void DesenharJogador(Jogador *j)
{
    DrawRectangleRec(j->caixa, BLUE);
}
