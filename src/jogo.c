#include "jogo.h"
#include "raylib.h"
#include "jogador.h"
#include "inimigo.h"
#include "plataformas.h"
#include "colisoes.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAX_PLAT 200
#define MAX_INI  1000

void RodarJogo(int dificuldade)
{
    int qtdPlataformas;
    int qtdInimigos;

    if (dificuldade == 1) {
        qtdPlataformas = 210;
        qtdInimigos = 300;
    }
    else if (dificuldade == 2) {
        qtdPlataformas = 80;
        qtdInimigos = 200;
    }
    else {
        qtdPlataformas = 50;
        qtdInimigos = 350;
    }

    if (qtdPlataformas > MAX_PLAT) qtdPlataformas = MAX_PLAT;
    if (qtdInimigos > MAX_INI) qtdInimigos = MAX_INI;

    srand((unsigned)time(NULL));

    Jogador jogador;
    InitJogador(&jogador);

    float tamanhoMapa = 50000;
    Rectangle chao = (Rectangle){ -5000, 650, tamanhoMapa, 2000 };

    float posParede = (-5000 + tamanhoMapa) - 2000;
    Rectangle paredeFinal = { posParede, 250, 128, 1024 };
    bool paredeAberta = false;

    jogador.caixa.x = 100;
    float limiteEsquerdo = jogador.caixa.x;

    float gravidade = 520.0f;
    float forcaPulo = -500.0f;

    float margemParede = 200.0f;
    float limiteGeracao = posParede - margemParede - 300.0f;   // <----- DO JEITO QUE VOCÊ PEDIU

    Rectangle plataformas[MAX_PLAT];
    InitPlataformas(plataformas, qtdPlataformas, dificuldade);

    for (int i = 0; i < qtdPlataformas; i++) {
        if (plataformas[i].x >= limiteGeracao)
            plataformas[i].x = limiteGeracao - (rand() % 600);
    }

    Inimigo inimigos[MAX_INI];
    IniciarInimigos(inimigos, qtdInimigos, dificuldade);

    for (int i = 0; i < qtdInimigos; i++) {

        if (inimigos[i].caixa.x >= limiteGeracao)
            inimigos[i].caixa.x = limiteGeracao - (rand() % 800);

        if (inimigos[i].limiteDir > limiteGeracao)
            inimigos[i].limiteDir = limiteGeracao;

        if (inimigos[i].limiteEsq >= inimigos[i].limiteDir)
            inimigos[i].limiteEsq = inimigos[i].caixa.x - 100.0f;
    }

    static float inimigoSpawnX[MAX_INI];
    static float inimigoSpawnY[MAX_INI];

    for (int i = 0; i < qtdInimigos; i++) {
        inimigoSpawnX[i] = inimigos[i].caixa.x;
        inimigoSpawnY[i] = inimigos[i].caixa.y;
    }

    Camera2D cam = {0};
    cam.offset = (Vector2){ 640, 360 };
    cam.zoom = 1.3f;

    int dano = 0;
    int danoMax = 3;
    float cooldown = 0;

    int inimigoChave = (qtdInimigos > 0) ? (rand() % qtdInimigos) : -1;
    bool chaveColetada = false;

    bool deathMessageShown = false;
    float deathTimer = 0.0f;
    const float deathDuration = 10.0f;
    float fadeAlpha = 0.0f;

    Rectangle npcCubo = { posParede + 200.0f, jogador.caixa.y, jogador.caixa.width, jogador.caixa.height };
    bool showCongrats = false;

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        UpdateJogador(&jogador, dt, gravidade, forcaPulo);
        cam.target = (Vector2){ jogador.caixa.x, jogador.caixa.y };

        if (jogador.caixa.x < limiteEsquerdo)
            jogador.caixa.x = limiteEsquerdo;

        bool descer = IsKeyDown(KEY_DOWN);

        ResolverColisaoChao(&jogador.caixa, &jogador.velocidade, chao, &jogador.pulando);
        ResolverColisaoPlataformas(&jogador.caixa, &jogador.velocidade, plataformas, qtdPlataformas, &jogador.pulando, descer);

        if (cooldown > 0) cooldown -= dt;

        AtualizarInimigos(inimigos, qtdInimigos, dt);

        // COLISÕES
        for (int i = 0; i < qtdInimigos; i++) {

            if (!inimigos[i].vivo) continue;

            if (ColisaoTotal(jogador.caixa, inimigos[i].caixa)) {

                float fundo = jogador.caixa.y + jogador.caixa.height;
                float topo  = inimigos[i].caixa.y;

                if (fundo <= topo + 10 && jogador.velocidade.y > 0) {

                    inimigos[i].vida--;
                    jogador.velocidade.y = forcaPulo * 1.25f;

                    if (i == inimigoChave && inimigos[i].vida <= 0)
                        chaveColetada = true;

                    if (inimigos[i].vida <= 0)
                        inimigos[i].vivo = false;
                }
                else if (cooldown <= 0) {

                    cooldown = 0.6f;
                    dano++;

                    int dir = (jogador.caixa.x > inimigos[i].caixa.x) ? 1 : -1;

                    AplicarKnockbackJogador(&jogador, dir);

                    inimigos[i].velocidade.x = -dir * fabsf(inimigos[i].velocidade.x);
                    inimigos[i].tempoKnockback = 0.25f;
                }
            }
        }

        // ENTRE INIMIGOS
        for (int a = 0; a < qtdInimigos; a++) {

            if (!inimigos[a].vivo) continue;

            if (inimigos[a].caixa.x > limiteGeracao)
                inimigos[a].caixa.x = limiteGeracao - 10.0f;

            for (int b = a + 1; b < qtdInimigos; b++) {

                if (!inimigos[b].vivo) continue;

                if (ColisaoTotal(inimigos[a].caixa, inimigos[b].caixa)) {

                    inimigos[a].caixa.x = inimigoSpawnX[a];
                    inimigos[a].caixa.y = inimigoSpawnY[a];

                    inimigos[b].caixa.x = inimigoSpawnX[b];
                    inimigos[b].caixa.y = inimigoSpawnY[b];

                    inimigos[a].velocidade.x *= -1;
                    inimigos[b].velocidade.x *= -1;

                    inimigos[a].tempoKnockback = 0.0f;
                    inimigos[b].tempoKnockback = 0.0f;
                }
            }
        }

        // INTERAÇÃO COM A PAREDE
        bool tocandoParede = ColisaoTotal(jogador.caixa, paredeFinal);

        if (tocandoParede) {

            if (!chaveColetada) {

                if (IsKeyPressed(KEY_E) && !deathMessageShown) {
                    deathMessageShown = true;
                    deathTimer = deathDuration;
                    fadeAlpha = 0.0f;
                }

                jogador.caixa.x = paredeFinal.x - jogador.caixa.width - 1;
            }
            else {
                if (!paredeAberta && IsKeyPressed(KEY_E))
                    paredeAberta = true;
            }
        }

        if (deathMessageShown) {

            deathTimer -= dt;

            float progress = (deathDuration - deathTimer) / deathDuration;
            if (progress < 0) progress = 0;
            if (progress > 1) progress = 1;
            fadeAlpha = progress;

            if (deathTimer <= 0.0f)
                return;
        }

        if (paredeAberta) {
            paredeFinal.width = 0;
            paredeFinal.height = 0;
            npcCubo.y = jogador.caixa.y;
        }

        if (dano >= danoMax && chaveColetada)
            return;

        if (paredeAberta) {

            if (jogador.caixa.x > posParede + 10 && ColisaoTotal(jogador.caixa, npcCubo)) {
                if (IsKeyPressed(KEY_E))
                    showCongrats = true;
            }
        }

        // DESENHO
        BeginDrawing();
        ClearBackground(SKYBLUE);

        BeginMode2D(cam);

        DrawRectangleRec(chao, DARKGREEN);
        DesenharPlataformas(plataformas, qtdPlataformas);
        DesenharJogador(&jogador);
        DesenharInimigos(inimigos, qtdInimigos);

        if (!paredeAberta)
            DrawRectangleRec(paredeFinal, BLACK);

        if (paredeAberta) {
            DrawRectangleRec(npcCubo, GREEN);
            if (showCongrats)
                DrawText("PARABENS! VOCE DESCOBRIU A PASSAGEM!", npcCubo.x - 120, npcCubo.y - 60, 20, YELLOW);
        }

        EndMode2D();

        DrawText(TextFormat("Dano: %d/%d", dano, danoMax), 20, 20, 30, RED);

        if (chaveColetada)
            DrawText("ITEM CHAVE COLETADO!", 20, 70, 30, YELLOW);

        if (!paredeAberta && tocandoParede && !chaveColetada)
            DrawText("Pressione E para interagir com a muralha", 20, 110, 22, WHITE);

        if (deathMessageShown) {

            const char *msg = "E apos tocar a muralha amaldiçoada, a heroina caiu e nunca mais levantou...";
            DrawText(msg, 20, 140, 20, WHITE);

            Color fadeColor = (Color){ 0, 0, 0, (unsigned char)(fadeAlpha * 255) };
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), fadeColor);
        }

        EndDrawing();
    }
}
