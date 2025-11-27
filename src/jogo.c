#include "jogo.h"
#include "raylib.h"
#include "jogador.h"
#include "inimigo.h"
#include "plataformas.h"
#include "colisoes.h"
#include "placar.h"
#include <stdlib.h>
#include <time.h>

#define MAX_PLAT 200
#define MAX_INI  1000

void RodarJogo(int dificuldade)
{
    // ---- TEXTURAS ----
    CarregarTexturasInimigos();
    Texture2D texturaMuro = LoadTexture("assets/muro.png");
    Texture2D fundoCeu = LoadTexture("assets/images/ceu.png");

    // ---- DIFICULDADE ----
    int danoMax = (dificuldade == 0 ? 5 : dificuldade == 1 ? 3 : 1);

    int qtdPlataformas = 89;
    int qtdInimigos = 74;

    if (qtdPlataformas > MAX_PLAT) qtdPlataformas = MAX_PLAT;
    if (qtdInimigos > MAX_INI) qtdInimigos = MAX_INI;

    srand((unsigned)time(NULL));

    // ---- JOGADOR ----
    Jogador jogador;
    InitJogador(&jogador);

    // ---- PLACAR ----
    int recordeAtual = CarregarRecorde();
    int score = 0;

    // ---- MAPA ----
    float tamanhoMapa = 50000;
    Rectangle chao = (Rectangle){ -5000, 650, tamanhoMapa, 2000 };
    float posParede = (-5000 + tamanhoMapa) - 2000;
    Rectangle paredeFinal = { posParede, -1000, 128, 2000 };
    bool paredeAberta = false;

    float limiteEsquerdo = 100;

    float gravidade = 520.0f;
    float forcaPulo = -500.0f;

    float margemParede = 200.0f;
    float limiteGeracao = posParede - margemParede - 300.0f;

    // ---- PLATAFORMAS ----
    Plataforma *plataformas = GerarPlataformas(qtdPlataformas, dificuldade, limiteGeracao);

    // ---- INIMIGOS ----
    Inimigo inimigos[MAX_INI];
    IniciarInimigos(inimigos, qtdInimigos, 1, limiteGeracao);

    if (qtdInimigos > 0)
    {
        int i = rand() % qtdInimigos;
        inimigos[i].temChave = true;
        inimigos[i].tipo = TIPO_LEAO;
    }

    // ---- CAMERA ----
    Camera2D cam = {0};
    cam.offset = (Vector2){ 640, 360 };
    cam.zoom = 1.3f;

    // ---- VARIÁVEIS INTERNAS ----
    int dano = 0;
    float cooldown = 0;

    bool deathMessageShown = false;
    float deathTimer = 0.0f;
    float fadeAlpha = 0.0f;

    bool finalBomIniciado = false;
    float finalBomTimer = 0.0f;
    float finalBomAlpha = 0.0f;

    const float deathDuration = 10.0f;
    const float finalBomDuracao = 6.0f;

    // ---- LOOP PRINCIPAL ----
    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        // Atualiza jogador
        if (!finalBomIniciado)
            UpdateJogador(&jogador, dt, gravidade, forcaPulo);

        cam.target = (Vector2){ jogador.caixa.x, jogador.caixa.y };

        if (jogador.caixa.x < limiteEsquerdo)
            jogador.caixa.x = limiteEsquerdo;

        bool descer = IsKeyDown(KEY_DOWN);

        // ---- COLISÕES ----
        ResolverColisaoChao(&jogador.caixa, &jogador.velocidade, chao, &jogador.pulando);
        ResolverColisaoPlataformasLista(&jogador.caixa, &jogador.velocidade, plataformas, &jogador.pulando, descer);

        // ---- INIMIGOS ----
        AtualizarInimigos(inimigos, qtdInimigos, dt);

        if (cooldown > 0) cooldown -= dt;

        // ---- COLISÃO JOGADOR x INIMIGOS ----
        if (!finalBomIniciado)
        {
            for (int i = 0; i < qtdInimigos; i++)
            {
                if (!inimigos[i].vivo) continue;

                if (ColisaoTotal(jogador.caixa, inimigos[i].caixa))
                {
                    float fundo = jogador.caixa.y + jogador.caixa.height;
                    float topo  = inimigos[i].caixa.y;

                    // ---- ATAQUE POR CIMA ----
                    if (fundo <= topo + 10 && jogador.velocidade.y > 0)
                    {
                        inimigos[i].vida--;
                        jogador.velocidade.y = forcaPulo * 1.25f;

                        if (inimigos[i].vida <= 0)
                        {
                            inimigos[i].vivo = false;
                            score++;

                            if (inimigos[i].temChave)
                                jogador.chave = 1;
                        }
                    }
                    else if (cooldown <= 0)
                    {
                        cooldown = 0.6f;
                        dano++;

                        int dir = (jogador.caixa.x > inimigos[i].caixa.x) ? 1 : -1;
                        AplicarKnockbackJogador(&jogador, dir);
                    }
                }
            }
        }

        // ---- COLISÃO COM A PAREDE ----
        bool tocandoParede = ColisaoTotal(jogador.caixa, paredeFinal);

        if (!finalBomIniciado)
        {
            if (!paredeAberta && tocandoParede)
            {
                // ---- SEM A CHAVE → GAME OVER SE APERTAR E ----
                if (jogador.chave == 0)
                {
                    if (IsKeyPressed(KEY_E) && !deathMessageShown)
                    {
                        deathMessageShown = true;
                        deathTimer = deathDuration;
                        fadeAlpha = 0.0f;
                    }
                    jogador.caixa.x = paredeFinal.x - jogador.caixa.width - 1;
                }
                else
                {
                    // ---- TEM A CHAVE → ABRIR PAREDE ----
                    if (IsKeyPressed(KEY_E))
                    {
                        paredeAberta = true;
                        paredeFinal.x = -999999;
                        finalBomIniciado = true;
                        finalBomTimer = finalBomDuracao;
                        finalBomAlpha = 0.0f;
                        jogador.velocidade.x = 0;
                        jogador.velocidade.y = 0;
                    }
                }
            }
        }

        // ---- FINAL BOM ----
        if (finalBomIniciado)
        {
            finalBomTimer -= dt;
            finalBomAlpha = 1.0f - (finalBomTimer / finalBomDuracao);

            if (finalBomTimer <= 0)
                goto FIM;
        }

        // ---- FINAL RUIM ----
        if (deathMessageShown)
        {
            deathTimer -= dt;
            fadeAlpha = 1.0f - (deathTimer / deathDuration);

            if (deathTimer <= 0)
                goto FIM;
        }

        if (dano >= danoMax)
            goto FIM;

        // ---------------- DRAW ----------------

        BeginDrawing();

        // FUNDO SEM CAMERA
        DrawTexturePro(
            fundoCeu,
            (Rectangle){0, 0, fundoCeu.width, fundoCeu.height},
            (Rectangle){0, 0, 1280, 720},
            (Vector2){0, 0},
            0,
            WHITE
        );

        BeginMode2D(cam);

        DrawRectangleRec(chao, DARKGREEN);
        DesenharPlataformas(plataformas);
        DesenharJogador(&jogador);
        DesenharInimigos(inimigos, qtdInimigos);

        if (!paredeAberta)
        {
            DrawTexturePro(
                texturaMuro,
                (Rectangle){0, 0, texturaMuro.width, texturaMuro.height},
                paredeFinal,
                (Vector2){0, 0},
                0,
                WHITE
            );
        }

        EndMode2D();

        // HUD
        DrawText(TextFormat("Dano: %d/%d", dano, danoMax), 20, 20, 30, RED);
        DrawText(TextFormat("Abates: %d", score), 20, 60, 20, WHITE);
        DrawText(TextFormat("Recorde: %d", (score > recordeAtual ? score : recordeAtual)), 20, 85, 20, GOLD);

        if (jogador.chave > 0)
            DrawText("CHAVE COLETADA! Vá para a muralha.", 20, 120, 22, GREEN);
        else
            DrawText("PROCURE O INIMIGO DOURADO! (ele tem a chave)", 20, 120, 22, YELLOW);

        // ---- TEXTO FINAL RUIM ----
        if (deathMessageShown)
        {
            DrawText("E apos tocar a muralha amaldiçoada, a heroina caiu e nunca mais levantou...",
                     20, 140, 20, WHITE);

            Color fade = {0, 0, 0, (unsigned char)(fadeAlpha * 255)};
            DrawRectangle(0, 0, 1280, 720, fade);
        }

        // ---- TEXTO FINAL BOM ----
        if (finalBomIniciado)
        {
            DrawText("E ao atravessar a muralha selada, a heroina enfim estava livre...",
                     20, 140, 20, BLACK);

            Color fade = {255, 255, 255, (unsigned char)(finalBomAlpha * 255)};
            DrawRectangle(0, 0, 1280, 720, fade);
        }

        EndDrawing();
    }

FIM:

    UnloadTexture(fundoCeu);
    UnloadTexture(texturaMuro);
    LiberarPlataformas(plataformas);
    DescarregarTexturasInimigos();
    SalvarRecorde(score);
}
