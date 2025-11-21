#ifndef MENU_H
#define MENU_H

#include "raylib.h"

typedef enum GameState {
    ESTADO_MENU,
    ESTADO_PLAY,
    ESTADO_DIFICULDADE,
    ESTADO_SETTINGS,
    ESTADO_EXIT
} GameState;

typedef struct Menu {
    const char **options;
    int optionCount;
    int selecionado;
    int dificuldade;      // ← ADICIONADO
    Vector2 pos;
    float lineSpacing;
    bool initialized;
} Menu;

void MenuInit(Menu *m);
GameState MenuUpdate(Menu *m);
void MenuDraw(const Menu *m);
void MenuUnload(Menu *m);

/// Tela de dificuldade
GameState MenuDificuldadeUpdate(Menu *m);
void MenuDificuldadeDraw(const Menu *m);

int MenuGetDificuldade(const Menu *m);

#endif
