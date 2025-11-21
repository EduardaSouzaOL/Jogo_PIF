#include "inimigo.h"
#include <stdlib.h>

void IniciarInimigos(Inimigo *v, int qtd, int dificuldade, float limiteGeracao)
{
    float inicioMapa = 600.0f;     // 500 px depois do player
    float fimMapa    = limiteGeracao - 200.0f;

    float espacoTotal = fimMapa - inicioMapa;
    if (espacoTotal <= 0) espacoTotal = 1000;

    // Distribuição uniforme total
    float dist = espacoTotal / qtd;

    for (int i = 0; i < qtd; i++)
    {
        float x = inicioMapa + i * dist;

        // INIMIGO NO CHÃO REAL !!
        float chaoY = 650.0f;                   // y do chão no seu jogo
        float tam   = 40.0f;                   // tamanho inimigo
        float y     = chaoY - tam;             // encostado no chão

        // Caixa de colisão
        v[i].caixa.x = x;
        v[i].caixa.y = y;
        v[i].caixa.width  = tam;
        v[i].caixa.height = tam;

        // Velocidade inicial alternada
        v[i].velocidade.x = (i % 2 == 0) ? 80.0f : -80.0f;
        v[i].velocidade.y = 0;

        // -------------------------------------------
        // NOVA RONDA DE PATRULHA: AGORA 300 px p/ cada lado
        // -------------------------------------------
        float patrulha = 300.0f;

        v[i].limiteEsq = x - patrulha;
        v[i].limiteDir = x + patrulha;

        if (v[i].limiteEsq < inicioMapa)
            v[i].limiteEsq = inicioMapa;

        if (v[i].limiteDir > fimMapa)
            v[i].limiteDir = fimMapa;

        // Atributos gerais
        v[i].vivo = true;
        v[i].vida = 1;
        v[i].tempoKnockback = 0.0f;
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

        // inverter lado manualmente (sem math.h)
        if (v[i].caixa.x < v[i].limiteEsq)
        {
            if (v[i].velocidade.x < 0)
                v[i].velocidade.x = -v[i].velocidade.x;
        }

        if (v[i].caixa.x + v[i].caixa.width > v[i].limiteDir)
        {
            if (v[i].velocidade.x > 0)
                v[i].velocidade.x = -v[i].velocidade.x;
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
