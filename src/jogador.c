#include "jogador.h"

#define GRAVIDADE 900.0f
#define FORCA_PULO -350.0f
#define VELOCIDADE_HORIZONTAL 200.0f

void InitJogador(Jogador *jogador)
{
    jogador->hitbox = (Rectangle){ 100, 400, 40, 50 };
    jogador->velocidade = (Vector2){ 0, 0 };
    jogador->pulando = false;
    jogador->vivo = true;
}

void AtualizarJogador(Jogador *jogador, float dt)
{
    if (!jogador->vivo) return;

    // Movimento horizontal
    if (IsKeyDown(KEY_RIGHT))
        jogador->velocidade.x = VELOCIDADE_HORIZONTAL;
    else if (IsKeyDown(KEY_LEFT))
        jogador->velocidade.x = -VELOCIDADE_HORIZONTAL;
    else
        jogador->velocidade.x = 0;

    // Pulo
    if (IsKeyPressed(KEY_UP) && !jogador->pulando)
    {
        jogador->velocidade.y = FORCA_PULO;
        jogador->pulando = true;
    }

    // Gravidade
    jogador->velocidade.y += GRAVIDADE * dt;

    // Aplicar movimento
    jogador->hitbox.x += jogador->velocidade.x * dt;
    jogador->hitbox.y += jogador->velocidade.y * dt;

    // Colisão com o chão (provisória)
    if (jogador->hitbox.y + jogador->hitbox.height >= 500)
    {
        jogador->hitbox.y = 500 - jogador->hitbox.height;
        jogador->velocidade.y = 0;
        jogador->pulando = false;
    }
}
