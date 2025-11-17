#include "raylib.h"
#include "menu.h"
#include "jogo.h"

int main(void) {
    InitWindow(1280, 720, "Jogo PIF - Amor & Endereco");
    SetTargetFPS(60);

    GameState estado = ESTADO_MENU;

    Menu menu;
    MenuInit(&menu);

    int dificuldade = 1;  // padrão

    while (!WindowShouldClose()) {

        switch (estado) {

        case ESTADO_MENU:
            estado = MenuUpdate(&menu);

            if (estado == ESTADO_PLAY) {
                dificuldade = 1;  // por enquanto sempre 1
            }
            break;

        case ESTADO_PLAY:
            RodarJogo(dificuldade);
            estado = ESTADO_MENU;
            break;

        case ESTADO_SETTINGS:
            if (IsKeyPressed(KEY_ESCAPE))
                estado = ESTADO_MENU;
            break;

        case ESTADO_EXIT:
            CloseWindow();
            return 0;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        switch (estado) {
        case ESTADO_MENU:
            MenuDraw(&menu);
            break;

        case ESTADO_SETTINGS:
            DrawText("CONFIGURACOES (aperte ESC para voltar)", 40, 40, 26, WHITE);
            break;

        default:
            break;
        }

        EndDrawing();
    }

    MenuUnload(&menu);
    CloseWindow();
    return 0;
}
