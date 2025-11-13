#include "raylib.h"

#define NUM_ENEMIES 30  // Número de inimigos espalhados pelo mapa

typedef struct Player {
    Rectangle rect;    // Hitbox do jogador
    Vector2 velocity;  // Velocidade
    bool isJumping;    // Controle de pulo
    bool isAlive;      // Jogador ainda está vivo?
} Player;

typedef struct Enemy {
    Rectangle rect;    // Hitbox do inimigo
    Vector2 velocity;  // Velocidade
    float leftLimit;   // Limite esquerdo da patrulha
    float rightLimit;  // Limite direito da patrulha
    bool isAlive;      // Inimigo ativo?
} Enemy;

int main(void)
{
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Mapa de 5 Minutos - Raylib");

    // ==== JOGADOR ====
    Player player = { 0 };
    player.rect = (Rectangle){ 100, 300, 40, 50 };
    player.velocity = (Vector2){ 0, 0 };
    player.isJumping = false;
    player.isAlive = true;

    // ==== MUNDO ====
    Rectangle ground = { 0, 650, 60000, 70 }; // 60.000px = ~5min andando
    const float gravity = 500.0f;
    const float jumpForce = -350.0f;

    // ==== INIMIGOS ====
    Enemy enemies[NUM_ENEMIES] = { 0 };
    for (int i = 0; i < NUM_ENEMIES; i++) {
        float x = 800 + i * 2000;  // espaçados a cada 2000px
        enemies[i].rect = (Rectangle){ x, 610, 40, 40 };
        enemies[i].velocity = (Vector2){ (i % 2 == 0) ? 100 : -100, 0 };
        enemies[i].leftLimit = x - 100;
        enemies[i].rightLimit = x + 100;
        enemies[i].isAlive = true;
    }

    // ==== VARIÁVEIS DE JOGO ====
    int damageCount = 0;
    const int maxDamage = 3;
    bool tookDamage = false;

    // ==== CÂMERA ====
    Camera2D camera = { 0 };
    camera.target = (Vector2){ player.rect.x + player.rect.width / 2, player.rect.y + player.rect.height / 2 };
    camera.offset = (Vector2){ screenWidth / 2, screenHeight / 2 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        // ================== MOVIMENTO DO JOGADOR ==================
        if (IsKeyDown(KEY_RIGHT)) player.velocity.x = 200;
        else if (IsKeyDown(KEY_LEFT)) player.velocity.x = -200;
        else player.velocity.x = 0;

        if (IsKeyPressed(KEY_UP) && !player.isJumping) {
            player.velocity.y = jumpForce;
            player.isJumping = true;
        }

        // Gravidade
        player.velocity.y += gravity * dt;

        // Atualiza posição
        player.rect.x += player.velocity.x * dt;
        player.rect.y += player.velocity.y * dt;

        // Colisão com o chão
        if (CheckCollisionRecs(player.rect, ground)) {
            player.rect.y = ground.y - player.rect.height;
            player.velocity.y = 0;
            player.isJumping = false;
        }

        tookDamage = false;

        // ================== MOVIMENTO E COLISÃO DOS INIMIGOS ==================
        for (int i = 0; i < NUM_ENEMIES; i++)
        {
            Enemy *enemy = &enemies[i];
            if (!enemy->isAlive) continue;

            // Movimento de patrulha
            enemy->rect.x += enemy->velocity.x * dt;
            if (enemy->rect.x < enemy->leftLimit || enemy->rect.x + enemy->rect.width > enemy->rightLimit)
                enemy->velocity.x *= -1;

            // Colisão jogador x inimigo
            if (CheckCollisionRecs(player.rect, enemy->rect))
            {
                float playerBottom = player.rect.y + player.rect.height;
                float enemyTop = enemy->rect.y;

                if (playerBottom <= enemyTop + 10 && player.velocity.y > 0)
                {
                    // Pula em cima do inimigo
                    enemy->isAlive = false;
                    player.velocity.y = jumpForce / 1.5f;
                }
                else if (!tookDamage) // Colisão lateral/inferior = dano
                {
                    damageCount++;
                    tookDamage = true;
                    player.rect.x -= player.velocity.x * 0.5f; // recuo
                }
            }
        }

        // ================== FIM DE JOGO AO LEVAR 3 DANOS ==================
        if (damageCount >= maxDamage)
        {
            CloseWindow();
            return 0;
        }

        // ================== CÂMERA SEGUE O JOGADOR ==================
        camera.target.x = player.rect.x + player.rect.width / 2;
        camera.target.y = player.rect.y + player.rect.height / 2;

        // Limita câmera ao mapa
        if (camera.target.x < screenWidth / 2) camera.target.x = screenWidth / 2;
        if (camera.target.x > ground.width - screenWidth / 2)
            camera.target.x = ground.width - screenWidth / 2;

        // ================== DESENHO ==================
        BeginDrawing();
            ClearBackground(SKYBLUE);
            BeginMode2D(camera);

                // Chão
                DrawRectangleRec(ground, DARKGREEN);

                // Inimigos
                for (int i = 0; i < NUM_ENEMIES; i++) {
                    if (enemies[i].isAlive)
                        DrawRectangleRec(enemies[i].rect, RED);
                    else
                        DrawText("X", enemies[i].rect.x + 10, enemies[i].rect.y - 20, 20, DARKGRAY);
                }

                // Jogador
                DrawRectangleRec(player.rect, BLUE);

            EndMode2D();

            // HUD
            DrawText(TextFormat("Dano: %d/%d", damageCount, maxDamage), 20, 20, 20, MAROON);
            DrawText("Ande -> 5 minutos de mapa com scroll", 20, 50, 20, DARKGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}