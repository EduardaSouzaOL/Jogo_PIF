#include "jogador.h"
#include "raylib.h"

void InitJogador(Jogador *j)
{
    j->caixa = (Rectangle){ 100, 400, 40 * 1.4, 50 * 1.4 }; 
    j->velocidade = (Vector2){ 0, 0 };
    j->pulando = false;

    j->tempoKnockback = 0.0f;
    j->forcaKnockback = 0.0f;

    j->chave = 0;

    //  SPRITE 
    j->sprite = LoadTexture("assets/images/jogador.png");

    // 5 frames na largura e 2 linhas 
    j->frameWidth  = j->sprite.width / 5;
    j->frameHeight = j->sprite.height / 2;

    j->estado = ESTADO_IDLE;
    j->direcao = DIR_DIREITA;

    j->animFrame = 0;
    j->animTimer = 0.0f;
}

void UpdateJogador(Jogador *j, float dt, float gravidade, float forcaPulo)
{
    if (j->tempoKnockback > 0.0f)
    {
        j->tempoKnockback -= dt;
    }
    else
    {
        // ---- MOVIMENTO LATERAL ----
        if (IsKeyDown(KEY_RIGHT)) {
            j->velocidade.x = 180;
            j->direcao = DIR_DIREITA;
            j->estado = ESTADO_ANDAR;
        }
        else if (IsKeyDown(KEY_LEFT)) {
            j->velocidade.x = -180;
            j->direcao = DIR_ESQUERDA;
            j->estado = ESTADO_ANDAR;
        }
        else {
            j->velocidade.x = 0;
            j->estado = ESTADO_IDLE;
        }

        // ---- AGACHAR ----
        if (IsKeyDown(KEY_DOWN)) {
            j->estado = ESTADO_AGACHAR;
        }

        // ---- PULO ----
        if (IsKeyPressed(KEY_UP) && !j->pulando)
        {
            j->velocidade.y = forcaPulo;
            j->pulando = true;
            j->estado = ESTADO_PULO;
        }
    }

    // ---- GRAVIDADE ----
    j->velocidade.y += gravidade * dt;

    // ---- MOVIMENTO ----
    j->caixa.x += j->velocidade.x * dt;
    j->caixa.y += j->velocidade.y * dt;

    // ---- ANIMAÇÃO ----
    if (j->estado == ESTADO_ANDAR)
    {
        j->animTimer += dt;
        if (j->animTimer >= 0.15f)
        {
            j->animTimer = 0;
            j->animFrame++;
            if (j->animFrame > 2)   
                j->animFrame = 0;
        }
    }
    else
    {
        j->animFrame = 0;
    }
}

void DesenharJogador(Jogador *j)
{
    int frame = 0;

    switch (j->estado)
    {
        case ESTADO_IDLE:     frame = 0; break;
        case ESTADO_ANDAR:    frame = 1 + j->animFrame; break; // usa 1,2,3
        case ESTADO_PULO:     frame = 4; break;
        case ESTADO_AGACHAR:  frame = 4; break;
    }

    Rectangle source = {
        j->frameWidth * frame,
        0,
        j->frameWidth,
        j->frameHeight
    };

    // DIREÇÃO ← esquerda usa a linha inferior (NÃO flipar)
    if (j->direcao == DIR_ESQUERDA)
    {
        source.y = j->frameHeight;  
    }

    Rectangle dest = {
        j->caixa.x,
        j->caixa.y,
        j->caixa.width,
        j->caixa.height
    };

    DrawTexturePro(j->sprite, source, dest, (Vector2){0,0}, 0, WHITE);
}

void AplicarKnockbackJogador(Jogador *j, int direcao)
{
    j->velocidade.x = 250 * direcao;
    j->tempoKnockback = 0.2f;
}
