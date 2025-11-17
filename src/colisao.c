#include "colisao.h"

#define COLISAO_LATERAL_MAX 3 // P NAO MORRER
#define TOLERANCIA_MAX 8

// colisao com plataformas
void ColisaoJogadorPlataformas(Jogador *j, Rectangle *plataformas, int qtd)
{
    for (int i = 0; i < qtd; i++)
    {
        Rectangle p = plataformas[i];

        if (CheckCollisionRecs(j->hitbox, p))
        {
            float jogadorBottom = j->hitbox.y + j->hitbox.height;
            float jogadorTop    = j->hitbox.y;
            float jogadorLeft   = j->hitbox.x;
            float jogadorRight  = j->hitbox.x + j->hitbox.width;

            float platBottom = p.y + p.height;
            float platTop    = p.y;
            float platLeft   = p.x;
            float platRight  = p.x + p.width;

            //  de cima,faz pousar na plataforma
            if (jogadorBottom > platTop && jogadorTop < platTop &&
                jogadorRight > platLeft && jogadorLeft < platRight)
            {
                j->hitbox.y = platTop - j->hitbox.height;
                j->velocidade.y = 0;
                j->pulando = false;
            }

            // p fora do eixo
            else if (jogadorRight > platLeft && jogadorLeft < platLeft) {
                j->hitbox.x = platLeft - j->hitbox.width;
            }
            else if (jogadorLeft < platRight && jogadorRight > platRight) {
                j->hitbox.x = platRight;
            }

            // bate a cabeça
            else if (jogadorTop < platBottom && jogadorBottom > platBottom) {
                j->hitbox.y = platBottom;
                j->velocidade.y = 50; // empurra pra baixo um pouco
            }
        }
    }
}


// colisao com inimigo

void ColisaoJogadorInimigo(Jogador *j, Inimigo *i)
{
    if (!i->ta_vivo) return;
    if (!j->vivo) return;

    if (!CheckCollisionRecs(j->hitbox, i->rect))
        return;

    float jogadorBottom = j->hitbox.y + j->hitbox.height;
    float inimigoTop    = i->rect.y;

    float jogadorLeft   = j->hitbox.x;
    float jogadorRight  = j->hitbox.x + j->hitbox.width;
    
    float inimigoLeft   = i->rect.x;
    float inimigoRight  = i->rect.x + i->rect.width;


    // 1. Jogador pisa em cima, inimigo morre 
    if (jogadorBottom <= inimigoTop + TOLERANCIA_MAX)  // 8px tolerancia
    {
        i->ta_vivo = false;
        j->velocidade.y = -250; // efeito de pular depois de matar
        return;
    }

    // usa as coordenadas de limite do jogador e inimigo
    bool lateral =
        (jogadorRight > inimigoLeft && jogadorLeft < inimigoLeft) ||
        (jogadorLeft < inimigoRight && jogadorRight > inimigoRight);
        // verifica se teve colisão do lado direito jogador com o esquerdo do inimigo
        //verifica a colisao do lado esquerdo do inimigo  como 
    if (lateral)
    {
        i->colisao_lateral_comJogador++;

        if (i->colisao_lateral_comJogador >= COLISAO_LATERAL_MAX)
        {
            j->vivo = false; // jogador morreu
        }
    }
}
