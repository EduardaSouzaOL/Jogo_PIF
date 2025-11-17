#include "colisoes.h"
#include "raylib.h"

void ResolverColisaoChao(Rectangle *jogador, Vector2   *velocidade, Rectangle  chao, bool *pulando)
{
    if (CheckCollisionRecs(*jogador, chao))
    {
        jogador->y = chao.y - jogador->height;
        velocidade->y = 0;
        *pulando = false;
    }
}

void ResolverColisaoPlataformas(Rectangle *jogador, Vector2   *velocidade, Rectangle *plataformas, int qtd, bool *pulando, bool descer)
{
    if (descer) return; // segurando pra baixo, cai pelas plataformas

    for (int i = 0; i < qtd; i++)
    {
        Rectangle r = plataformas[i];

        // só considerar se está caindo
        if (velocidade->y > 0 &&
            CheckCollisionRecs(*jogador, r))
        {
            float topoPlataforma = r.y;
            float fundoJogador   = jogador->y + jogador->height;

            if (fundoJogador <= topoPlataforma + 10)
            {
                jogador->y = topoPlataforma - jogador->height;
                velocidade->y = 0;
                *pulando = false;
            }
        }
    }
}

bool ColisaoTotal(Rectangle a, Rectangle b)
{
    return CheckCollisionRecs(a, b);
}
