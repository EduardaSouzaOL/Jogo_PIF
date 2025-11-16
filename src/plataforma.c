#include "plataforma.h"

void InitPlataformas(Rectangle *p, int qtd, int dificuldade) {
    for (int i = 0; i < qtd; i++) {
        float x = 400 + i * (900 - dificuldade * 30);
        float y = 500 - (i % 5) * 45;
        float w = 150 + (i % 3) * 40;

        p[i] = (Rectangle){ x, y, w, 20 };
    }
}

void DesenharPlataformas(Rectangle *p, int qtd) {
    for (int i = 0; i < qtd; i++)
        DrawRectangleRec(p[i], BROWN);
}
