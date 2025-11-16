#ifndef MENU_H
#define MENU_H

#include "raylib.h"

typedef enum GameState {
    ESTADO_MENU,
    ESTADO_PLAY,
    ESTADO_SETTINGS,
    ESTADO_EXIT
} GameState;

typedef struct Menu {
    const char **options;
    int optionCount;
    int selecionado;
    Vector2 pos;
    float lineSpacing;
    bool initialized;
} Menu;

void MenuInit(Menu *m);
GameState MenuUpdate(Menu *m);
void MenuDraw(const Menu *m);
void MenuUnload(Menu *m);

#endif
