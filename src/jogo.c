#include "jogo.h"
#include "raylib.h"
#include "jogador.h"
#include "inimigo.h"
#include "plataformas.h"
#include "colisoes.h"
#include <stdlib.h>

#define MAX_PLAT 200
#define MAX_INI  1000

void RodarJogo(int dificuldade)
{
    int qtdPlataformas;
    int qtdInimigos;

    // Quantidades por dificuldade
    if (dificuldade == 1)
    {
        qtdPlataformas = 210;
        qtdInimigos = 300;
    }
    else if (dificuldade == 2)
    {
        qtdPlataformas = 80;
        qtdInimigos = 200;
    }
    else
    {
        qtdPlataformas = 50;
        qtdInimigos = 350;
    }

    if (qtdPlataformas > MAX_PLAT) qtdPlataformas = MAX_PLAT;
    if (qtdInimigos > MAX_INI) qtdInimigos = MAX_INI;

    Jogador jogador;
    InitJogador(&jogador);

    // ---------- MUNDO EXPANDIDO ----------
    float tamanhoMapa = 200000 * 2;   // dobra o tamanho do mundo original
    Rectangle chao = (Rectangle){ -5000, 650, tamanhoMapa, 2000 };

    // Posição da parede final
    float posParede = tamanhoMapa - 2000;  
    Rectangle paredeFinal = { posParede, 450, 80, 300 };

    bool paredeAberta = false;

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

    // ---------- SORTEIO DE CHAVE ----------
    int inimigoChave = rand() % qtdInimigos;
    bool chaveColetada = false;

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        UpdateJogador(&jogador, dt, gravidade, forcaPulo);
        cam.target = (Vector2){ jogador.caixa.x, jogador.caixa.y };

        // Parede invisível atrás
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

        // ---------- COLISÃO JOGADOR x INIMIGO ----------
        for (int i = 0; i < qtdInimigos; i++)
        {
            if (!inimigos[i].vivo) continue;

            if (ColisaoTotal(jogador.caixa, inimigos[i].caixa))
            {
                float fundo = jogador.caixa.y + jogador.caixa.height;
                float topo  = inimigos[i].caixa.y;

                // PISOU NO INIMIGO
                if (fundo <= topo + 10 && jogador.velocidade.y > 0)
                {
                    inimigos[i].vida--;
                    jogador.velocidade.y = forcaPulo * 1.25f;

                    if (i == inimigoChave && inimigos[i].vida <= 0)
                        chaveColetada = true;

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

        // ---------- INTERAÇÃO COM A PAREDE FINAL ----------
        if (!paredeAberta && ColisaoTotal(jogador.caixa, paredeFinal))
        {
            if (IsKeyPressed(KEY_E))  // abre o buraco
            {
                paredeAberta = true;
            }
        }

        // Remove a parede se estiver aberta
        if (paredeAberta)
        {
            paredeFinal.height = 0;
            paredeFinal.width = 0;
        }

        // ---------- GAME OVER ----------
        if (dano >= danoMax && chaveColetada)
        {
            CloseWindow();
            return;
        }

        // ---------- DESENHO ----------
        BeginDrawing();
        ClearBackground(SKYBLUE);

        BeginMode2D(cam);

        DrawRectangleRec(chao, DARKGREEN);
        DrawRectangle(-5000, 650, tamanhoMapa, 2000, DARKGREEN);

        DesenharPlataformas(plataformas, qtdPlataformas);
        DesenharJogador(&jogador);
        DesenharInimigos(inimigos, qtdInimigos);

        // Desenhar parede final (se não estiver aberta)
        if (!paredeAberta)
            DrawRectangleRec(paredeFinal, BLACK);

        EndMode2D();

        DrawText(TextFormat("Dano: %d/%d", dano, danoMax), 20, 20, 30, RED);

        if (chaveColetada)
            DrawText("ITEM CHAVE COLETADO!", 20, 70, 30, YELLOW);

        if (!paredeAberta &&
            ColisaoTotal(jogador.caixa, paredeFinal))
        {
            DrawText("Pressione E para abrir a passagem", 20, 120, 28, WHITE);
        }

        EndDrawing();
    }
}
