#include "plataformas.h"
#include <stdlib.h>

void InitPlataformas(Rectangle *p, int qtd, int dificuldade, float limiteGeracao)
{
    float x = 300;

    float distMin = 380;
    float distMax = 520;

    // limite real (300px antes da parede)
    float limiteReal = limiteGeracao - 300.0f;

    for (int i = 0; i < qtd; i++)
    {
        x += distMin + (rand() % (int)(distMax - distMin));

        // ⚠ BLOQUEAR geração perto da parede
        if (x >= limiteReal)
            x = limiteReal - (rand() % 600 + 400);

        float yBaixa = 480 + (rand() % 50);
        float yMedia = 410 + (rand() % 50);
        float yAlta  = 300 + (rand() % 90);

        float yFinal = yBaixa;
        int r = rand() % 100;

        if (dificuldade == 1) {
            if (r < 60) yFinal = yBaixa;
            else        yFinal = yMedia;
        }
        else if (dificuldade == 2) {
            if (r < 35) yFinal = yBaixa;
            else if (r < 70) yFinal = yMedia;
            else             yFinal = yAlta;
        }
        else {
            if (r < 20) yFinal = yMedia;
            else        yFinal = yAlta;
        }

        float w = 160 + (rand() % 100);

        p[i] = (Rectangle){ x, yFinal, w, 20 };
    }
}
