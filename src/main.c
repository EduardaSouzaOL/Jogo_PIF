#include "raylib.h"
#include "menu.h"

int main(void) {
    InitWindow(800, 450, "Menu");
    SetTargetFPS(60);

    Menu menu;
    MenuInit(&menu);

    GameState state = ESTADO_MENU;

    while (!WindowShouldClose()) {

        // UPDATE
        switch (state) {
            case ESTADO_MENU:
                state = MenuUpdate(&menu);
                break;

            case ESTADO_PLAY:
                if (IsKeyPressed(KEY_ESCAPE)) state = ESTADO_MENU;
                break;

            case ESTADO_SETTINGS:
                if (IsKeyPressed(KEY_ESCAPE)) state = ESTADO_MENU;
                break;

            case ESTADO_EXIT:
                CloseWindow();
                return 0;
        }

        // DRAW
        BeginDrawing();
        ClearBackground(BLACK);

        switch (state) {
            case ESTADO_MENU:
                MenuDraw(&menu);
                break;

            case ESTADO_PLAY:
                DrawText("JOGO RODANDO\nPressione ESC para voltar", 50, 100, 24, GREEN);
                break;

            case ESTADO_SETTINGS:
                DrawText("CONFIGURACOES\nPressione ESC para voltar", 50, 100, 24, BLUE);
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
