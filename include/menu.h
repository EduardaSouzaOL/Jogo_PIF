#ifndef MENU_H
#define MENU_H

#include "raylib.h"

// Estados possíveis do jogo
typedef enum GameState {
    ESTADO_MENU,
    ESTADO_PLAY,
    ESTADO_SETTINGS,
    ESTADO_EXIT
} GameState;

// Estrutura do menu principal
typedef struct Menu {
    const char **options;   // Lista de opções
    int optionCount;        // Quantidade de opções
    int selecionado;        // Índice selecionado
    Vector2 pos;            // Posição do texto
    float lineSpacing;      // Espaçamento entre linhas
    bool initialized;       // Controle de inicialização
} Menu;

// Inicializa o menu
void MenuInit(Menu *m);

// Atualiza a lógica do menu
GameState MenuUpdate(Menu *m);

// Desenha o menu na tela
void MenuDraw(const Menu *m);

// Descarrega recursos do menu
void MenuUnload(Menu *m);

#endif
