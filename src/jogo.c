#include "jogo.h"
#include "raylib.h"
#include "jogador.h"
#include "inimigo.h"
#include "plataforma.h"

#define MAX_PLATFORMS 60
#define MAX_INIMIGOS  80

void RodarJogo(void)
{
    int dificuldade = 10;

    int qtdPlataformas = 5 + (10 - dificuldade) * 2;
    int qtdInimigos    = 5 + dificuldade * 3;

    if (qtdPlataformas > MAX_PLATFORMS) qtdPlataformas = MAX_PLATFORMS;
    if (qtdInimigos > MAX_INIMIGOS) qtdInimigos = MAX_INIMIGOS;

    // Jogador
    Jogador jogador;
    InitJogador(&jogador);

    // Chão
    Rectangle chao = { 0, 650, 60000, 70 };

    // Físicas
    float gravidade = 500;
    float forcaPulo = -350;

    // Plataformas
    Rectangle plataformas[MAX_PLATFORMS];
    InitPlataformas(plataformas, qtdPlataformas, dificuldade);

    // Inimigos
    Inimigo inimigos[MAX_INIMIGOS];
    InitInimigos(inimigos, qtdInimigos, dificuldade);

    // Sistema de Dano
    int dano = 0;
    int danoMax = 3;
    float cooldown = 0;

    // Câmera
    Camera2D cam = { 0 };
    cam.offset = (Vector2){ 1280/2, 720/2 };
    cam.zoom = 1.3f;

    // Loop do jogo
    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        UpdateJogador(&jogador, dt, gravidade, forcaPulo);

        // Atualiza câmera
        cam.target = (Vector2){ jogador.hitbox.x, jogador.hitbox.y };

        // ===== COLISÃO COM O CHÃO =====
        if (CheckCollisionRecs(jogador.hitbox, chao))
        {
            jogador.hitbox.y = chao.y - jogador.hitbox.height;
            jogador.velocidade.y = 0;
            jogador.pulando = false;
        }

        // ===== COLISÃO COM PLATAFORMAS =====
        bool descendo = IsKeyDown(KEY_DOWN);

        for (int i = 0; i < qtdPlataformas; i++)
        {
            if (descendo) break;

            Rectangle p = plataformas[i];

            if (CheckCollisionRecs(jogador.hitbox, p) && jogador.velocidade.y > 0)
            {
                jogador.hitbox.y = p.y - jogador.hitbox.height;
                jogador.velocidade.y = 0;
                jogador.pulando = false;
            }
        }

        // ===== INIMIGOS =====
        if (cooldown > 0) cooldown -= dt;

        UpdateInimigos(inimigos, qtdInimigos, dt);

        for (int i = 0; i < qtdInimigos; i++)
        {
            if (!inimigos[i].hitbox) continue;

            if (CheckCollisionRecs(jogador.hitbox, inimigos[i].hitbox))
            {
                float bot = jogador.hitbox.y + jogador.hitbox.height;
                float top = inimigos[i].hitbox.y;

                // Pisa no inimigo
                if (bot <= top + 10 && jogador.velocidade.y > 0)
                {
                    inimigos[i].ta_vivo = false;
                    jogador.velocidade.y = forcaPulo / 1.5f;
                }
                else if (cooldown <= 0)
                {
                    dano++;
                    cooldown = 0.7;
                }
            }
        }

        if (dano >= danoMax)
            return;

        // ============================================
        //                    DESENHO
        // ============================================
        BeginDrawing();
        ClearBackground(SKYBLUE);

        BeginMode2D(cam);

        DrawRectangleRec(chao, DARKGREEN);
        DesenharPlataformas(plataformas, qtdPlataformas);
        DesenharJogador(&jogador);
        DesenharInimigos(inimigos, qtdInimigos);

        EndMode2D();

        DrawText(TextFormat("Dano: %d/%d", dano, danoMax), 20, 20, 30, MAROON);

        EndDrawing();
    }
}
