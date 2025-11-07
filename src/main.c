#include "raylib.h"

typedef struct Player {
    Rectangle rect;    // Hitbox do jogador
    Vector2 velocity;  // Velocidade
    bool isJumping;    // Controle de pulo
} Player;

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Plataforma com Scroll - Raylib");

    // Inicializa jogador
    Player player = { 0 };
    player.rect = (Rectangle){ 100, 300, 40, 50 };
    player.velocity = (Vector2){ 0, 0 };
    player.isJumping = false;

    Rectangle ground = { 0, 400, 2000, 50 }; // Chão mais largo que tela para testar o scroll

    Rectangle platforms[3] = {
        { 300, 350, 120, 20 },
        { 700, 300, 100, 20 },
        { 1200, 320, 150, 20 }
    };

    const float gravity = 500.0f;
    const float jumpForce = -350.0f;

    Camera2D camera = { 0 };
    camera.target = (Vector2){ player.rect.x + player.rect.width / 2, player.rect.y + player.rect.height / 2 };
    camera.offset = (Vector2){ screenWidth / 2, screenHeight / 2 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        // Movimento horizontal
        if (IsKeyDown(KEY_RIGHT)) player.velocity.x = 200;
        else if (IsKeyDown(KEY_LEFT)) player.velocity.x = -200;
        else player.velocity.x = 0;

        // Pulo
        if (IsKeyPressed(KEY_UP) && !player.isJumping) {
            player.velocity.y = jumpForce;
            player.isJumping = true;
        }

        // Gravidade
        player.velocity.y += gravity * dt;

        // Atualiza posição do jogador
        player.rect.x += player.velocity.x * dt;
        player.rect.y += player.velocity.y * dt;

        // Colisão com o chão
        if (CheckCollisionRecs(player.rect, ground)) {
            player.rect.y = ground.y - player.rect.height;
            player.velocity.y = 0;
            player.isJumping = false;
        }

        // Colisão com plataformas
        for (int i = 0; i < 3; i++) {
            if (CheckCollisionRecs(player.rect, platforms[i]) && player.velocity.y > 0) {
                player.rect.y = platforms[i].y - player.rect.height;
                player.velocity.y = 0;
                player.isJumping = false;
            }
        }

        // Atualiza o alvo da câmera (segue o player)
        camera.target = (Vector2){ player.rect.x + player.rect.width / 2, player.rect.y + player.rect.height / 2 };

        // Renderização
        BeginDrawing();
            ClearBackground(RAYWHITE);

            BeginMode2D(camera);
                DrawRectangleRec(ground, DARKGREEN);
                for (int i = 0; i < 3; i++) DrawRectangleRec(platforms[i], BROWN);
                DrawRectangleRec(player.rect, BLUE);
            EndMode2D();

            DrawText("Use as setas para mover e UP para pular", 10, 10, 20, GRAY);
            DrawText("Camera segue o jogador!", 10, 40, 20, DARKGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}