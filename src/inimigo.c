#include "inimigo.h"
#include <stdlib.h>

// Definição das variáveis globais das texturas
Texture2D texCoelho;
Texture2D texLobo;
Texture2D texLeao;

void CarregarTexturasInimigos(void)
{
    texCoelho = LoadTexture("assets/images/coelho.png");
    texLobo   = LoadTexture("assets/images/lobo.png");
    texLeao   = LoadTexture("assets/images/leao.png");
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
    float fimMapa    = limiteGeracao - 200.0f;
    float espacoTotal = fimMapa - inicioMapa;
    
    if (espacoTotal <= 0) espacoTotal = 1000;
    float dist = espacoTotal / qtd;

    for (int i = 0; i < qtd; i++)
    {
        float x = inicioMapa + i * dist;
        float chaoY = 650.0f;
        
        // Define o tamanho da caixa de colisão (pode ajustar conforme a imagem)
        float tam = 50.0f; 
        float y = chaoY - tam;

        v[i].caixa = (Rectangle){ x, y, tam, tam };

        // Define a velocidade base
        v[i].velocidade.x = (i % 2 == 0) ? 80.0f : -80.0f;
        v[i].velocidade.y = 0;

        // --- Lógica de Tipo de Inimigo ---
        // Distribui os tipos: Coelho, Lobo, Leão sequencialmente
        int resto = i % 3;
        if (resto == 0)      v[i].tipo = TIPO_COELHO;
        else if (resto == 1) v[i].tipo = TIPO_LOBO;
        else                 v[i].tipo = TIPO_LEAO;

        // Opcional: Ajustar velocidade ou vida baseado no tipo
        if (v[i].tipo == TIPO_LEAO) v[i].velocidade.x *= 1.5f; // Leão corre mais

        // Configuração da patrulha
        float patrulha = 300.0f;
        v[i].limiteEsq = x - patrulha;
        v[i].limiteDir = x + patrulha;

        if (v[i].limiteEsq < inicioMapa) v[i].limiteEsq = inicioMapa;
        if (v[i].limiteDir > fimMapa)    v[i].limiteDir = fimMapa;

        v[i].vivo = true;
        v[i].vida = 1;
        v[i].tempoKnockback = 0.0f;
        v[i].temChave = false;
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

        // Inverte direção nos limites
        if (v[i].caixa.x < v[i].limiteEsq)
        {
            v[i].caixa.x = v[i].limiteEsq;
            if (v[i].velocidade.x < 0) v[i].velocidade.x = -v[i].velocidade.x;
        }
        else if (v[i].caixa.x + v[i].caixa.width > v[i].limiteDir)
        {
            v[i].caixa.x = v[i].limiteDir - v[i].caixa.width;
            if (v[i].velocidade.x > 0) v[i].velocidade.x = -v[i].velocidade.x;
        }
    }
}

void DesenharInimigos(Inimigo *v, int qtd)
{
    for (int i = 0; i < qtd; i++)
    {
        if (v[i].vivo)
        {
            // Seleciona a textura correta baseada no tipo
            Texture2D texAtual;
            switch (v[i].tipo) {
                case TIPO_COELHO: texAtual = texCoelho; break;
                case TIPO_LOBO:   texAtual = texLobo; break;
                case TIPO_LEAO:   texAtual = texLeao; break;
                default:          texAtual = texCoelho; break;
            }

            // Verifica se a textura foi carregada corretamente
            if (texAtual.id > 0) 
            {
                // Inverte a imagem se o inimigo estiver indo para a esquerda
                Rectangle sourceRec = { 0.0f, 0.0f, (float)texAtual.width, (float)texAtual.height };
                
                // Se velocidade for negativa (esquerda), espelha a textura
                if (v[i].velocidade.x < 0) sourceRec.width = -sourceRec.width;

                DrawTexturePro(
                    texAtual,
                    sourceRec,
                    v[i].caixa, // Desenha esticado no tamanho da hitbox
                    (Vector2){0, 0},
                    0.0f,
                    WHITE
                );
            }
            else 
            {
                // Fallback: desenha retângulo vermelho se a textura falhar
                DrawRectangleRec(v[i].caixa, RED);
            }
        }
    }
}