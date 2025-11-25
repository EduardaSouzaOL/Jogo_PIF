#include "inimigo.h"
#include <stdlib.h>


// Texturas globais
Texture2D texCoelho;
Texture2D texLobo;
Texture2D texLeao;

void CarregarTexturasInimigos(void)
{
    texCoelho = LoadTexture("../assets/images/coelho.png");
    texLobo = LoadTexture("../assets/images/lobo.png");
    texLeao = LoadTexture("../assets/images/leao.png");
}

void DescarregarTexturasInimigos(void)
{
    UnloadTexture(texCoelho);
    UnloadTexture(texLobo);
    UnloadTexture(texLeao);
}

void IniciarInimigos(Inimigo *v, int qtd, int dificuldade, float limiteGeracao)
{
    float inicioMapa = 600.0f;
    float fimMapa = limiteGeracao - 200.0f;
    float espacoTotal = fimMapa - inicioMapa;
    if (espacoTotal <= 0) espacoTotal = 1000;

    float dist = espacoTotal / qtd;

    for (int i = 0; i < qtd; i++)
    {
        float x = inicioMapa + i * dist;

        //TIPO BASEADO NA POSIÇÃO (ZONAS)
        TipoInimigo tipo;
        int r = rand() % 100;

        if (x < 5000) {
            // ZONA 1: Maioria COELHOS
            if (r < 70)         tipo = TIPO_COELHO;
            else if (r < 95)    tipo = TIPO_LOBO;
            else                tipo = TIPO_LEAO;
        }
        else if (x < 15000) {
            // ZONA 2: Maioria LOBOS
            if (r < 20)         tipo = TIPO_COELHO;
            else if (r < 85)    tipo = TIPO_LOBO;
            else                tipo = TIPO_LEAO;
        }
        else {
            // ZONA 3: Maioria LEÕES
            if (r < 10)         tipo = TIPO_COELHO;
            else if (r < 40)    tipo = TIPO_LOBO;
            else                tipo = TIPO_LEAO;
         }

        v[i].tipo = tipo;

        // ========== TAMANHO BASEADO NO TIPO ==========
        float tam;
        if (tipo == TIPO_COELHO)        tam = 30.0f;
        else if (tipo == TIPO_LOBO)     tam = 45.0f;
        else                            tam = 70.0f;

        float chaoY = 650.0f;
        float y = chaoY - tam;

        v[i].caixa.x = x;
        v[i].caixa.y = y;
        v[i].caixa.width = tam;
        v[i].caixa.height = tam;

        // ========== VELOCIDADE BASEADA NO TIPO ==========
        float velBase = 80.0f;
        if (tipo == TIPO_COELHO)        velBase = 100.0f;
        else if (tipo == TIPO_LOBO)     velBase = 80.0f;
        else                            velBase = 50.0f;

        v[i].velocidade.x = (i % 2 == 0) ? velBase : -velBase;
        v[i].velocidade.y = 0;

        float patrulha = 300.0f;
        v[i].limiteEsq = x - patrulha;
        v[i].limiteDir = x + patrulha;

        if (v[i].limiteEsq < inicioMapa)
            v[i].limiteEsq = inicioMapa;
        if (v[i].limiteDir > fimMapa)
            v[i].limiteDir = fimMapa;

        v[i].vivo = true;

        // ========== VIDA BASEADA NO TIPO ==========
        if (tipo == TIPO_COELHO)        v[i].vida = 1;
        else if (tipo == TIPO_LOBO)     v[i].vida = 3;
        else                            v[i].vida = 8;

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
        {
            float x = v[i].caixa.x;
            float y = v[i].caixa.y;
            float w = v[i].caixa.width;
            float h = v[i].caixa.height;

            Texture2D tex;
            if (v[i].tipo == TIPO_COELHO)
                tex = texCoelho;
            else if (v[i].tipo == TIPO_LOBO)
                tex = texLobo;
            else
                tex = texLeao;

            // Desenha a textura escalada para o tamanho da caixa
            Rectangle source = { 0, 0, tex.width, tex.height };
            Rectangle dest = { x, y, w, h };
            Vector2 origin = { 0, 0 };
     
            DrawTexturePro(tex, source, dest, origin, 0.0f, WHITE);
        }
    }
}