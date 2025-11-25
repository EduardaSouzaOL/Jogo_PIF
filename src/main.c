#include "raylib.h"
#include "menu.h"
#include "jogo.h"
#include "inimigo.h" // Certifique-se que este include está aqui para acessar as funções de textura

int main(void) {
    InitWindow(1280, 720, "Jogo PIF - Amor & Endereco");
    SetTargetFPS(60);

    // --- ADICIONE ESTA LINHA ---
    // Carrega as imagens dos inimigos (coelho, lobo, leão) para a memória
    CarregarTexturasInimigos(); 
    // ---------------------------

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
            // Antes de sair pelo menu, precisamos limpar a memória
            goto ENCERRAMENTO; 
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

// Rótulo para garantir que a limpeza execute mesmo se sair pelo menu
ENCERRAMENTO: 
    MenuUnload(&menu);

    DescarregarTexturasInimigos();


    CloseWindow();
    return 0;
}