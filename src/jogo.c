#include "jogo.h"
#include "raylib.h"
#include "jogador.h"
#include "inimigo.h"
#include "plataformas.h"
#include "colisoes.h"
#include <stdlib.h>
#include <time.h>
#include "placar.h" 

#define MAX_PLAT 200 // Limite máximo de plataformas
#define MAX_INI  1000 // Limite máximo de inimigos

/**
 * @brief Função principal que executa o loop do jogo.
 * @param dificuldade Nível de dificuldade (0, 1, 2)
 */
void RodarJogo(int dificuldade)
{
    // Carregamento de recursos iniciais e variáveis
    CarregarTexturasInimigos();
    Texture2D texturaMuro = LoadTexture("assets/muro.png");
    int danoMax;

    // Configura o dano máximo do jogador com base na dificuldade
    if (dificuldade == 0) danoMax = 5;
    else if (dificuldade == 1) danoMax = 3;
    else danoMax = 1;

    // Configuração de quantidades de elementos
    int qtdPlataformas = 89;
    int qtdInimigos= 74;

    if (qtdPlataformas > MAX_PLAT) qtdPlataformas = MAX_PLAT;
    if (qtdInimigos > MAX_INI) qtdInimigos = MAX_INI;

    srand((unsigned)time(NULL));

    // Inicialização do jogador
    Jogador jogador;
    InitJogador(&jogador);

    // Sistema de placar
    int recordeAtual = CarregarRecorde(); 
    int score = 0; // Número de abates
    
    // Configurações do mapa (chão e parede final)
    float tamanhoMapa = 50000;
    Rectangle chao = (Rectangle){ -5000, 650, tamanhoMapa, 2000 };
    float posParede = (-5000 + tamanhoMapa) - 2000;
    Rectangle paredeFinal = { posParede, -1000, 128, 2000 }; 
    bool paredeAberta = false;

    jogador.caixa.x = 100;
    float limiteEsquerdo = jogador.caixa.x;

    // Constantes de física
    float gravidade = 520.0f;
    float forcaPulo = -500.0f;

    // Geração de plataformas e inimigos
    float margemParede = 200.0f;
    float limiteGeracao = posParede - margemParede - 300.0f;
    Plataforma *plataformas = GerarPlataformas(qtdPlataformas, dificuldade, limiteGeracao);

    Inimigo inimigos[MAX_INI];
    IniciarInimigos(inimigos, qtdInimigos, 1, limiteGeracao);

    // Define um inimigo aleatório para possuir a chave (e o torna um leão para destaque)
    if (qtdInimigos > 0) {
        int indiceSorteado = rand() % qtdInimigos;
        inimigos[indiceSorteado].temChave = true;

        inimigos[indiceSorteado].tipo = TIPO_LEAO; 
    }

    // Configuração da câmera
    Camera2D cam = {0};
    cam.offset = (Vector2){ 640, 360 };
    cam.zoom = 1.3f;

    int dano = 0; // Dano sofrido pelo jogador
    float cooldown = 0; // Tempo de invencibilidade após sofrer dano

    // Variáveis para controle do estado de "Game Over" (sem chave)
    bool deathMessageShown = false;
    float deathTimer = 0.0f;
    const float deathDuration = 10.0f;
    float fadeAlpha = 0.0f;

    // Variáveis para controle do estado de "Final Bom" (com chave)
    bool finalBomIniciado = false;
    float finalBomTimer = 0.0f;
    const float finalBomDuracao = 6.0f;
    float finalBomAlpha = 0.0f;

    // --- LOOP PRINCIPAL DO JOGO ---
    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        if (!finalBomIniciado)
            UpdateJogador(&jogador, dt, gravidade, forcaPulo); // Atualiza posição e estado do jogador

        cam.target = (Vector2){ jogador.caixa.x, jogador.caixa.y };

        if (jogador.caixa.x < limiteEsquerdo)
            jogador.caixa.x = limiteEsquerdo;

        bool descer = IsKeyDown(KEY_DOWN);

        // Resolução de colisões
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

        // Lógica de colisão com inimigos (dano e pulo)
        if (!finalBomIniciado)
        {
            for (int i = 0; i < qtdInimigos; i++) {
                if (!inimigos[i].vivo) continue;

                if (ColisaoTotal(jogador.caixa, inimigos[i].caixa)) {

                    float fundo = jogador.caixa.y + jogador.caixa.height;
                    float topo= inimigos[i].caixa.y;

                    // Colisão por cima (pulo no inimigo para ataque)
                    if (fundo <= topo + 10 && jogador.velocidade.y > 0) {
                        inimigos[i].vida--;
                        jogador.velocidade.y = forcaPulo * 1.25f;

                        if (inimigos[i].vida <= 0) {
                            inimigos[i].vivo = false;
                            score++; // Incrementa ponto por abate

                            // Coleta da chave
                            if (inimigos[i].temChave) {
                                jogador.chave = 1; 
                            }
                        }
                    }
                    // Colisão lateral ou por baixo (jogador sofre dano)
                    else if (cooldown <= 0) {
                        cooldown = 0.6f;
                        dano++;
                        int dir = (jogador.caixa.x > inimigos[i].caixa.x) ? 1 : -1;
                        AplicarKnockbackJogador(&jogador, dir);
                        inimigos[i].tempoKnockback = 0.25f;
                    }
                }
            }
        }

        // Lógica da Parede Final e Condições de Fim de Jogo
        bool tocandoParede = ColisaoTotal(jogador.caixa, paredeFinal);

        if (!finalBomIniciado)
        {
            if (!paredeAberta && tocandoParede)
            {
                // Se NÃO tem a chave
                if (jogador.chave == 0)
                {
                    // Inicia "Game Over" se pressionar [E] sem a chave
                    if (IsKeyPressed(KEY_E) && !deathMessageShown) {
                        deathMessageShown = true;
                        deathTimer = deathDuration;
                        fadeAlpha = 0.0f;
                    }
                    // Impede o jogador de atravessar a parede
                    jogador.caixa.x = paredeFinal.x - jogador.caixa.width - 1;
                }
                // Se TEM a chave
                else
                {
                    // Abre a parede se pressionar [E]
                    if (IsKeyPressed(KEY_E))
                    {
                        paredeAberta = true;
                        paredeFinal.x = -999999; // Remove a parede
                        finalBomIniciado = true; // Inicia o "Final Bom"
                        finalBomTimer = finalBomDuracao;
                        finalBomAlpha = 0.0f;
                        jogador.velocidade.x = 0;
                        jogador.velocidade.y = 0;
                    }
                }
            }
        }
        else // Transição para o "Final Bom"
        {
            finalBomTimer -= dt;
            float p = (finalBomDuracao - finalBomTimer) / finalBomDuracao;
            if (p < 0) p = 0;
            if (p > 1) p = 1;
            finalBomAlpha = p; // Aumenta o alpha para o fade branco

            if (finalBomTimer <= 0.0f)
                goto FIM; // Sai do loop para finalizar o jogo
        }

        // Transição para "Game Over" (Sem chave / Morte)
        if (deathMessageShown) {
            deathTimer -= dt;
            float p = (deathDuration - deathTimer) / deathDuration;
            if (p < 0) p = 0;
            if (p > 1) p = 1;
            fadeAlpha = p; // Aumenta o alpha para o fade preto

            if (deathTimer <= 0.0f)
                goto FIM; // Sai do loop para finalizar o jogo
        }

        // Condição de "Game Over" por dano
        if (dano >= danoMax)
            goto FIM;

        // --- RENDERIZAÇÃO (DRAWING) ---
        BeginDrawing();
        ClearBackground(SKYBLUE);

        // Desenha os elementos do jogo que seguem a câmera (Mundo 2D)
        BeginMode2D(cam);
        DrawRectangleRec(chao, DARKGREEN);
        DesenharPlataformas(plataformas);
        DesenharJogador(&jogador);
        DesenharInimigos(inimigos, qtdInimigos);

        if (!paredeAberta){
            DrawTexturePro(texturaMuro, 
                           (Rectangle){ 0, 0, (float)texturaMuro.width, (float)texturaMuro.height }, 
                           paredeFinal, 
                           (Vector2){ 0, 0 }, 
                           0.0f, 
                           WHITE);
        }
        EndMode2D();

        // Desenha a Interface do Usuário (HUD)
        DrawText(TextFormat("Dano: %d/%d", dano, danoMax), 20, 20, 30, RED);
        DrawText(TextFormat("Abates: %d", score), 20, 60, 20, WHITE);
        DrawText(TextFormat("Recorde: %d", (score > recordeAtual ? score : recordeAtual)), 20, 85, 20, GOLD);

        // Desenha mensagens de objetivo
        if (jogador.chave > 0) {
            DrawText("CHAVE COLETADA!", 20, 120, 20, GREEN);
            DrawText("Vá para a muralha final!", 20, 145, 20, GREEN);
        } else {
            DrawText("OBJETIVO: Encontre o inimigo com a CHAVE (Dourado)!", 20, 120, 20, GOLD);
        }

        // Aviso de interação com a muralha
        if (!paredeAberta && tocandoParede && !deathMessageShown)
        {
            if (jogador.chave > 0) {
                DrawText("Pressione [E] para DESTRUIR a muralha!", 20, 180, 22, GREEN);
            } else {
                DrawText("A muralha está selada... Precisa da CHAVE.", 20, 180, 22, RED);
                DrawText("Cuidado! Tocar nela sem a chave é fatal (Pressione E por sua conta e risco)", 20, 205, 18, GRAY);
            }
        }

        // Efeito de "Game Over" (fade preto)
        if (deathMessageShown) {
            DrawText("E apos tocar a muralha amaldiçoada, a heroina caiu e nunca mais levantou...",
                     20, 140, 20, WHITE);
            Color fadeColor = (Color){0, 0, 0, (unsigned char)(fadeAlpha * 255)};
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), fadeColor);
        }

        // Efeito de "Final Bom" (fade branco)
        if (finalBomIniciado)
        {
            DrawText("E ao atravessar a muralha selada, a heroina enfim estava livre...",
                     20, 140, 20, BLACK);
            Color fadeBranco = (Color){255, 255, 255, (unsigned char)(finalBomAlpha * 255)};
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), fadeBranco);
        }

        EndDrawing();
    }

FIM: // Ponto de saída do jogo (após "Game Over" ou "Final Bom")

    // Liberação de recursos
    UnloadTexture(texturaMuro);
    SalvarRecorde(score);
    LiberarPlataformas(plataformas);
    DescarregarTexturasInimigos(); 
}