#include "raylib.h"
#include "menu.h"
#include "jogo.h"

int main(void) {
    InitWindow(1280, 720, "Jogo PIF - Amor & Endereco");
    SetTargetFPS(60);

    GameState estado = ESTADO_MENU;

    Menu menu;
    MenuInit(&menu);

    int dificuldade = 1;

    while (!WindowShouldClose()) {

        switch (estado) {

        case ESTADO_MENU:
            estado = MenuUpdate(&menu);
            break;

        case ESTADO_PLAY:
            dificuldade = MenuGetDificuldade(&menu);
            RodarJogo(dificuldade);

            // ao terminar o jogo, voltar ao menu
            estado = ESTADO_MENU;
            break;

        case ESTADO_EXIT:
            MenuUnload(&menu);
            CloseWindow();
            return 0;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        switch (estado) {
        case ESTADO_MENU:
            MenuDraw(&menu);
            break;

        case ESTADO_PLAY:
            // nada a desenhar aqui, RodarJogo já desenha
            break;
        }

        EndDrawing();
    }

    MenuUnload(&menu);
    CloseWindow();
    return 0;
}
