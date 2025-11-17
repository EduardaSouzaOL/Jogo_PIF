#include "jogo.h"
#include "raylib.h"
#include "jogador.h"
#include "inimigo.h"
#include "plataformas.h"
#include "colisoes.h"

#define MAX_PLAT 200
#define MAX_INI  1000

void RodarJogo(int dificuldade)
{
    int qtdPlataformas;
    int qtdInimigos;

    // Quantidades por dificuldade
    if (dificuldade == 1)       // FÁCIL
    {
        qtdPlataformas = 110;
        qtdInimigos = 100;
    }
    else if (dificuldade == 2)  // MÉDIO
    {
        qtdPlataformas = 80;
        qtdInimigos = 200;
    }
    else                         // DIFÍCIL (3)
    {
        qtdPlataformas = 50;
        qtdInimigos = 350;
    }

    if (qtdPlataformas > MAX_PLAT) qtdPlataformas = MAX_PLAT;
    if (qtdInimigos > MAX_INI) qtdInimigos = MAX_INI;

    Jogador jogador;
    InitJogador(&jogador);

    Rectangle chao = (Rectangle){ -5000, 650, 200000, 2000 };
    float gravidade = 520.0f;
    float forcaPulo = -500.0f;

    Rectangle plataformas[MAX_PLAT];
    InitPlataformas(plataformas, qtdPlataformas, dificuldade);

    Inimigo inimigos[MAX_INI];
    IniciarInimigos(inimigos, qtdInimigos, dificuldade);

    Camera2D cam = {0};
    cam.offset = (Vector2){ 640, 360 };
    cam.zoom = 1.3f;

    float limiteEsquerdo = jogador.caixa.x;

    int dano = 0;
    int danoMax = 3;
    float cooldown = 0;

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        UpdateJogador(&jogador, dt, gravidade, forcaPulo);
        cam.target = (Vector2){ jogador.caixa.x, jogador.caixa.y };

        // Parede invisível atrás do player
        if (jogador.caixa.x < limiteEsquerdo)
            jogador.caixa.x = limiteEsquerdo;

        bool descer = IsKeyDown(KEY_DOWN);

        ResolverColisaoChao(&jogador.caixa, &jogador.velocidade,
                            chao, &jogador.pulando);

        ResolverColisaoPlataformas(&jogador.caixa, &jogador.velocidade,
                                   plataformas, qtdPlataformas,
                                   &jogador.pulando, descer);

        if (cooldown > 0) cooldown -= dt;

        AtualizarInimigos(inimigos, qtdInimigos, dt);

        for (int i = 0; i < qtdInimigos; i++)
        {
            if (!inimigos[i].vivo) continue;

            if (ColisaoTotal(jogador.caixa, inimigos[i].caixa))
            {
                float fundo = jogador.caixa.y + jogador.caixa.height;
                float topo  = inimigos[i].caixa.y;

                // JOGADOR PISA NO INIMIGO
                if (fundo <= topo + 10 && jogador.velocidade.y > 0)
                {
                    inimigos[i].vida--;
                    jogador.velocidade.y = forcaPulo * 1.25f;

                    if (inimigos[i].vida <= 0)
                        inimigos[i].vivo = false;
                }
                else if (cooldown <= 0)
                {
                    cooldown = 0.6f;
                    dano++;

                    float direcao = (jogador.caixa.x < inimigos[i].caixa.x) ? -1 : 1;

                    AplicarKnockbackJogador(&jogador, direcao);
                    inimigos[i].velocidade.x = direcao * 250;
                }
            }
        }

        if (dano >= danoMax)
        {
            CloseWindow();
            return;
        }

        BeginDrawing();
        ClearBackground(SKYBLUE);

        BeginMode2D(cam);

        DrawRectangleRec(chao, DARKGREEN);
        DrawRectangle(-5000, 650, 200000, 2000, DARKGREEN);

        DesenharPlataformas(plataformas, qtdPlataformas);
        DesenharJogador(&jogador);
        DesenharInimigos(inimigos, qtdInimigos);

        EndMode2D();

        DrawText(TextFormat("Dano: %d/%d", dano, danoMax), 
                 20, 20, 30, RED);

        EndDrawing();
    }
}
