#include "jogo.h"
#include "raylib.h"
#include "jogador.h"
#include "inimigo.h"
#include "plataformas.h"
#include "colisoes.h"
#include <stdlib.h>
#include <time.h>
#include "placar.h" 

#define MAX_PLAT 200
#define MAX_INI  1000

void RodarJogo(int dificuldade)
{
    int danoMax;

    if (dificuldade == 0) danoMax = 5;
    else if (dificuldade == 1) danoMax = 3;
    else danoMax = 1;

    int qtdPlataformas = 89;
    int qtdInimigos    = 74;

    if (qtdPlataformas > MAX_PLAT) qtdPlataformas = MAX_PLAT;
    if (qtdInimigos > MAX_INI)     qtdInimigos = MAX_INI;

    srand((unsigned)time(NULL));

    Jogador jogador;
    InitJogador(&jogador);

    // --- SISTEMA DE PLACAR ---
    int recordeAtual = CarregarRecorde(); 
    int score = 0; // Agora representará o número de abates
    // -------------------------

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
    float limiteGeracao = posParede - margemParede - 300.0f;

    Plataforma *plataformas = GerarPlataformas(qtdPlataformas, dificuldade, limiteGeracao);
    for (Plataforma *p = plataformas; p != NULL; p = p->next) {
        if (p->rect.x >= limiteGeracao)
            p->rect.x = limiteGeracao - (rand() % 600);
    }

    Inimigo inimigos[MAX_INI];
    IniciarInimigos(inimigos, qtdInimigos, 1, limiteGeracao);

    Camera2D cam = {0};
    cam.offset = (Vector2){ 640, 360 };
    cam.zoom = 1.3f;

    int dano = 0;
    float cooldown = 0;

    int inimigoChave = (qtdInimigos > 0) ? (rand() % qtdInimigos) : -1;
    bool chaveColetada = false;

    bool deathMessageShown = false;
    float deathTimer = 0.0f;
    const float deathDuration = 10.0f;
    float fadeAlpha = 0.0f;

    bool finalBomIniciado = false;
    float finalBomTimer = 0.0f;
    const float finalBomDuracao = 6.0f;
    float finalBomAlpha = 0.0f;

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        if (!finalBomIniciado)
            UpdateJogador(&jogador, dt, gravidade, forcaPulo);

        // (REMOVIDO) Lógica antiga de score por distância foi apagada daqui

        cam.target = (Vector2){ jogador.caixa.x, jogador.caixa.y };

        if (jogador.caixa.x < limiteEsquerdo)
            jogador.caixa.x = limiteEsquerdo;

        bool descer = IsKeyDown(KEY_DOWN);

        ResolverColisaoChao(&jogador.caixa, &jogador.velocidade, chao, &jogador.pulando);

        ResolverColisaoPlataformasLista(
            &jogador.caixa,
            &jogador.velocidade,
            plataformas,
            &jogador.pulando,
            descer
        );

        if (cooldown > 0) cooldown -= dt;

        AtualizarInimigos(inimigos, qtdInimigos, dt);

        if (!finalBomIniciado)
        {
            for (int i = 0; i < qtdInimigos; i++) {

                if (!inimigos[i].vivo) continue;

                if (ColisaoTotal(jogador.caixa, inimigos[i].caixa)) {

                    float fundo = jogador.caixa.y + jogador.caixa.height;
                    float topo  = inimigos[i].caixa.y;

                    // Colisão por cima (pulo no inimigo)
                    if (fundo <= topo + 10 && jogador.velocidade.y > 0) {

                        inimigos[i].vida--;
                        jogador.velocidade.y = forcaPulo * 1.25f;

                        if (i == inimigoChave && inimigos[i].vida <= 0)
                            chaveColetada = true;

                        // --- AQUI CONTA O ABATE ---
                        if (inimigos[i].vida <= 0) {
                            inimigos[i].vivo = false;
                            score++; // Incrementa 1 ponto por inimigo morto
                        }
                        // --------------------------
                    }
                    else if (cooldown <= 0) {
                        // Dano no jogador
                        cooldown = 0.6f;
                        dano++;

                        int dir = (jogador.caixa.x > inimigos[i].caixa.x) ? 1 : -1;

                        if (inimigos[i].velocidade.x > 0 && dir > 0)
                            inimigos[i].velocidade.x = -inimigos[i].velocidade.x;
                        if (inimigos[i].velocidade.x < 0 && dir < 0)
                            inimigos[i].velocidade.x = -inimigos[i].velocidade.x;

                        AplicarKnockbackJogador(&jogador, dir);
                        inimigos[i].tempoKnockback = 0.25f;
                    }
                }
            }
        }

        // ... (Código de colisão com parede igual ao anterior)
        bool tocandoParede = ColisaoTotal(jogador.caixa, paredeFinal);

        if (!finalBomIniciado)
        {
            if (!paredeAberta)
            {
                if (tocandoParede)
                {
                    if (!chaveColetada)
                    {
                        if (IsKeyPressed(KEY_E) && !deathMessageShown) {
                            deathMessageShown = true;
                            deathTimer = deathDuration;
                            fadeAlpha = 0.0f;
                        }
                        jogador.caixa.x = paredeFinal.x - jogador.caixa.width - 1;
                    }
                    else
                    {
                        if (IsKeyPressed(KEY_E))
                        {
                            paredeAberta = true;
                            paredeFinal.x = -999999;
                            paredeFinal.width = 0;
                            paredeFinal.height = 0;

                            finalBomIniciado = true;
                            finalBomTimer = finalBomDuracao;
                            finalBomAlpha = 0.0f;

                            jogador.velocidade.x = 0;
                            jogador.velocidade.y = 0;
                        }
                    }
                }
            }
        }
        else
        {
            finalBomTimer -= dt;
            float p = (finalBomDuracao - finalBomTimer) / finalBomDuracao;
            if (p < 0) p = 0;
            if (p > 1) p = 1;
            finalBomAlpha = p;

            if (finalBomTimer <= 0.0f)
                goto FIM;
        }

        if (deathMessageShown) {
            deathTimer -= dt;
            float p = (deathDuration - deathTimer) / deathDuration;
            if (p < 0) p = 0;
            if (p > 1) p = 1;
            fadeAlpha = p;

            if (deathTimer <= 0.0f)
                goto FIM;
        }

        if (dano >= danoMax)
            goto FIM;

        BeginDrawing();
        ClearBackground(SKYBLUE);

        BeginMode2D(cam);
        DrawRectangleRec(chao, DARKGREEN);
        DesenharPlataformas(plataformas);
        DesenharJogador(&jogador);
        DesenharInimigos(inimigos, qtdInimigos);

        if (!paredeAberta)
            DrawRectangleRec(paredeFinal, BLACK);
        EndMode2D();

        // --- HUD ATUALIZADO ---
        DrawText(TextFormat("Dano: %d/%d", dano, danoMax), 20, 20, 30, RED);
        
        // Mostra 'Abates' e 'Recorde'
        DrawText(TextFormat("Abates: %d", score), 20, 60, 20, WHITE);
        DrawText(TextFormat("Recorde: %d", (score > recordeAtual ? score : recordeAtual)), 20, 85, 20, GOLD);
        // ----------------------

        if (chaveColetada)
            DrawText("ITEM CHAVE COLETADO!", 20, 120, 30, YELLOW);

        if (!paredeAberta && tocandoParede && !chaveColetada)
            DrawText("Pressione E para interagir com a muralha", 20, 160, 22, WHITE);

        if (deathMessageShown) {
            DrawText("E apos tocar a muralha amaldiçoada, a heroina caiu e nunca mais levantou...",
                     20, 140, 20, WHITE);
            Color fadeColor = (Color){0, 0, 0, (unsigned char)(fadeAlpha * 255)};
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), fadeColor);
        }

        if (finalBomIniciado)
        {
            DrawText("E ao atravessar a muralha selada, a heroina enfim estava livre...",
                     20, 140, 20, BLACK);
            Color fadeBranco = (Color){255, 255, 255, (unsigned char)(finalBomAlpha * 255)};
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), fadeBranco);
        }

        EndDrawing();
    }

FIM:
    SalvarRecorde(score);
    LiberarPlataformas(plataformas);
}