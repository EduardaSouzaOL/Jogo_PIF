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

        // --------------------
        // VELOCIDADE ESCALADA POR DIFICULDADE
        // --------------------
        float velBase = 80.0f;
        float velFinal = velBase;

        for (int d = 1; d < dificuldade; d++)
            velFinal *= 1.15f; // +15% acumulativo

        v[i].velocidade = (Vector2){
            (rand() % 2 == 0) ? velFinal : -velFinal,
            0
        };

        // área de patrulha aumenta com dificuldade
        float faixa = 200 + dificuldade * 80;

        v[i].limiteEsq = x - faixa;
        v[i].limiteDir = x + faixa;

        v[i].vivo = true;
        v[i].vida = dificuldade; // 1, 2 ou 3 hits
    }
}

void AtualizarInimigos(Inimigo *v, int qtd, float dt)
{
    for (int i = 0; i < qtd; i++)
    {
        if (!v[i].vivo) continue;

        v[i].caixa.x += v[i].velocidade.x * dt;

        if (v[i].caixa.x < v[i].limiteEsq ||
            v[i].caixa.x + v[i].caixa.width > v[i].limiteDir)
        {
            v[i].velocidade.x *= -1;
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
