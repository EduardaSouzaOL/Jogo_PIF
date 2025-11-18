#include "inimigo.h"
#include <stdlib.h>

void IniciarInimigos(Inimigo *v, int qtd, int dificuldade)
{
    float x = 500;
    float distMin = 350;
    float distMax = 550;

    for (int i = 0; i < qtd; i++)
    {
        x += distMin + (rand() % (int)(distMax - distMin));

        float y = 610;

        v[i].caixa = (Rectangle){ x, y, 40, 40 };

        float velBase = 80.0f;
        float velFinal = velBase;

        for (int d = 1; d < dificuldade; d++)
            velFinal *= 1.15f;

        v[i].velocidade = (Vector2){
            (rand() % 2 == 0) ? velFinal : -velFinal,
            0
        };

        float faixa = 200 + dificuldade * 80;

        v[i].limiteEsq = x - faixa;
        v[i].limiteDir = x + faixa;

        v[i].vivo = true;
        v[i].vida = dificuldade;

        v[i].tempoKnockback = 0;   // <— ADICIONADO
    }
}

void AtualizarInimigos(Inimigo *v, int qtd, float dt)
{
    for (int i = 0; i < qtd; i++)
    {
        if (!v[i].vivo) continue;

        if (v[i].tempoKnockback > 0)
            v[i].tempoKnockback -= dt;

        v[i].caixa.x += v[i].velocidade.x * dt;

        if (v[i].tempoKnockback <= 0)
        {
            if (v[i].caixa.x < v[i].limiteEsq ||
                v[i].caixa.x + v[i].caixa.width > v[i].limiteDir)
            {
                v[i].velocidade.x *= -1;
            }
        }
    }
}

void DesenharInimigos(Inimigo *v, int qtd)
{
    for (int i = 0; i < qtd; i++)
    {
        if (v[i].vivo)
            DrawRectangleRec(v[i].caixa, RED);
    }
}
