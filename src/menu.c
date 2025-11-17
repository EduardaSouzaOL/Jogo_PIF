#include "menu.h"
#include <string.h>

// Textura estática para o fundo do menu
static Texture2D fundoMenu;

// Inicialização do menu
void MenuInit(Menu *m) {
    static const char *opts[] = {
        "Jogar",
        "Configurações",
        "Sair"
    };

    m->options = opts;
    m->optionCount = sizeof(opts) / sizeof(opts[0]);
    m->selecionado = 0;
    m->pos = (Vector2){40, 140};
    m->lineSpacing = 50;
    m->initialized = true;

    fundoMenu = LoadTexture("assets/images/fundo_menu.png");
}

// Atualização da lógica do menu
GameState MenuUpdate(Menu *m) {
    if (!m || !m->initialized)
        return ESTADO_MENU;

    // Navegação com teclado — seta para baixo
    if (IsKeyPressed(KEY_DOWN)) {
        m->selecionado++;
        if (m->selecionado >= m->optionCount)
            m->selecionado = 0;
    }

    // Navegação com teclado — seta para cima
    if (IsKeyPressed(KEY_UP)) {
        m->selecionado--;
        if (m->selecionado < 0)
            m->selecionado = m->optionCount - 1;
    }

    // Seleção com ENTER
    if (IsKeyPressed(KEY_ENTER)) {
        const char *opt = m->options[m->selecionado];

        if (strcmp(opt, "Jogar") == 0)         return ESTADO_PLAY;
        if (strcmp(opt, "Configurações") == 0) return ESTADO_SETTINGS;
        if (strcmp(opt, "Sair") == 0)          return ESTADO_EXIT;
    }

    return ESTADO_MENU;
}

// Desenho do menu
void MenuDraw(const Menu *m) {
    int fontSize = 24;

    // Fundo com imagem proporcional à tela
    DrawTexturePro(
        fundoMenu,
        (Rectangle){0, 0, fundoMenu.width, fundoMenu.height},
        (Rectangle){0, 0, GetScreenWidth(), GetScreenHeight()},
        (Vector2){0, 0},
        0.0f,
        WHITE
    );

    // Título
    DrawText("AMOR & ENDERECO", 40, 60, 32, WHITE);

    // Lista de opções
    for (int i = 0; i < m->optionCount; i++) {
        float x = m->pos.x;
        float y = m->pos.y + i * m->lineSpacing;

        if (i == m->selecionado) {
            DrawText("<3", x - 30, y, fontSize, YELLOW);
            DrawText(m->options[i], x, y, fontSize, YELLOW);
        } else {
            DrawText(m->options[i], x, y, fontSize, LIGHTGRAY);
        }
    }
}

// Descarregamento do menu
void MenuUnload(Menu *m) {
    UnloadTexture(fundoMenu);
    m->initialized = false;
}
