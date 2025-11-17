#include "plataformas.h"
#include <stdlib.h>

void InitPlataformas(Rectangle *p, int qtd, int dificuldade)
{
    float x = 300;

    // distância maior → menos plataformas
    float distMin = 380;   // antes 250
    float distMax = 520;   // antes 450

    for (int i = 0; i < qtd; i++)
    {
        x += distMin + (rand() % (int)(distMax - distMin));

        // alturas ajustadas (todas mais altas)
        float yBaixa = 480 + (rand() % 50);   // antes 520–560
        float yMedia = 410 + (rand() % 50);   // antes 450–500
        float yAlta  = 300 + (rand() % 90);   // antes 330–420

        float yFinal = yBaixa;
        int r = rand() % 100;

        if (dificuldade == 1)      // fácil
        {
            if (r < 60) yFinal = yBaixa;
            else        yFinal = yMedia;
        }
        else if (dificuldade == 2) // médio
        {
            if (r < 35) yFinal = yBaixa;
            else if (r < 70) yFinal = yMedia;
            else             yFinal = yAlta;
        }
        else                       // difícil
        {
            if (r < 20) yFinal = yMedia;
            else        yFinal = yAlta;
        }

        float w = 160 + (rand() % 100); // igual ao anterior

        p[i] = (Rectangle){ x, yFinal, w, 20 };
    }
}

void DesenharPlataformas(Rectangle *p, int qtd)
{
    for (int i = 0; i < qtd; i++)
    {
        DrawRectangleRec(p[i], BROWN);
    }
}
