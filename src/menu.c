#include "menu.h"
#include <string.h>

static Texture2D fundoMenu;

void MenuInit(Menu *m) {
    static const char *opts[] = {
        "Jogar",
        "Dificuldade",
        "Sair"
    };

    m->options = opts;
    m->optionCount = 3;
    m->selecionado = 0;
    m->dificuldade = 1;     // ← padrão: médio
    m->pos = (Vector2){40, 140};
    m->lineSpacing = 50;
    m->initialized = true;

    fundoMenu = LoadTexture("assets/images/fundo_menu.png");
}

GameState MenuUpdate(Menu *m) {
    if (!m->initialized) return ESTADO_MENU;

    if (IsKeyPressed(KEY_DOWN)) {
        m->selecionado = (m->selecionado + 1) % m->optionCount;
    }

    if (IsKeyPressed(KEY_UP)) {
        m->selecionado--;
        if (m->selecionado < 0) m->selecionado = m->optionCount - 1;
    }

    if (IsKeyPressed(KEY_ENTER)) {
        switch (m->selecionado) {
        case 0: return ESTADO_PLAY;
        case 1: return ESTADO_DIFICULDADE;   // ← nova tela
        case 2: return ESTADO_EXIT;
        }
    }

    return ESTADO_MENU;
}

void MenuDraw(const Menu *m) {
    DrawTexturePro(
        fundoMenu,
        (Rectangle){0,0,fundoMenu.width,fundoMenu.height},
        (Rectangle){0,0,GetScreenWidth(),GetScreenHeight()},
        (Vector2){0,0},
        0.0f,
        WHITE
    );

    DrawText("AMOR & ENDERECO", 40, 60, 32, WHITE);

    for (int i = 0; i < m->optionCount; i++) {
        Color c = (i == m->selecionado) ? YELLOW : LIGHTGRAY;
        DrawText(m->options[i], m->pos.x, m->pos.y + i * m->lineSpacing, 28, c);
    }

    DrawText(TextFormat("Dificuldade atual: %s",
        m->dificuldade == 0 ? "Fácil" :
        m->dificuldade == 1 ? "Médio" : "Difícil"),
        40, 320, 24, WHITE
    );
}


// -----------------------
//  TELA DE DIFICULDADE
// -----------------------
GameState MenuDificuldadeUpdate(Menu *m)
{
    if (IsKeyPressed(KEY_UP)) {
        m->dificuldade--;
        if (m->dificuldade < 0) m->dificuldade = 2;
    }
    if (IsKeyPressed(KEY_DOWN)) {
        m->dificuldade = (m->dificuldade + 1) % 3;
    }

    if (IsKeyPressed(KEY_ENTER)) {
        return ESTADO_MENU;
    }

    if (IsKeyPressed(KEY_ESCAPE)) {
        return ESTADO_MENU;
    }

    return ESTADO_DIFICULDADE;
}

void MenuDificuldadeDraw(const Menu *m)
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);
    DrawText("ESCOLHA A DIFICULDADE", 40, 60, 32, WHITE);

    const char *nomes[] = {"Fácil", "Médio", "Difícil"};

    for (int i = 0; i < 3; i++) {
        Color c = (i == m->dificuldade) ? YELLOW : LIGHTGRAY;
        DrawText(nomes[i], 40, 160 + i * 50, 28, c);
    }

    DrawText("ENTER para confirmar", 40, 400, 24, WHITE);
}

int MenuGetDificuldade(const Menu *m)
{
    return m->dificuldade;
}

void MenuUnload(Menu *m)
{
    UnloadTexture(fundoMenu);
    m->initialized = false;
}
