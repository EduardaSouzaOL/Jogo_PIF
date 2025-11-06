#include "raylib.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Controle de Cubo - Raylib Cross-platform");

    // Posição inicial do cubo
    float cubeX = screenWidth / 2.0f;
    const float cubeY = screenHeight / 2.0f;
    const float cubeSize = 40.0f;
    const float speed = 5.0f;  // Velocidade de movimento do cubo

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Movimento para esquerda
        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) cubeX -= speed;
        // Movimento para direita
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) cubeX += speed;

        // Impede que o cubo saia dos limites da tela
        if (cubeX < cubeSize / 2) cubeX = cubeSize / 2;
        if (cubeX > screenWidth - cubeSize / 2) cubeX = screenWidth - cubeSize / 2;

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Use as teclas A/D ou <- -> para mover o cubo!", 180, 20, 20, DARKGRAY);

        // Desenha o cubo como um retângulo
        DrawRectangle(cubeX - cubeSize / 2, cubeY - cubeSize / 2, cubeSize, cubeSize, RED);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
