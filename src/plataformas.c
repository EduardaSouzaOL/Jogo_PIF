#include "plataformas.h"
#include <stdlib.h>



static Plataforma *CriarPlataforma(Rectangle r)
{
    Plataforma *p = malloc(sizeof(Plataforma));
    if (!p) return NULL;

    p->rect = r;
    p->next = NULL;
    return p;
}


Plataforma *GerarPlataformas(int qtd, int dificuldade, float limiteGeracao)
{
    Plataforma *head = NULL;
    Plataforma *tail = NULL;

    float x = 300;

    float distMin = 380;
    float distMax = 520;

    float limiteReal = limiteGeracao - 300.0f;

    for (int i = 0; i < qtd; i++)
    {
        x += distMin + (rand() % (int)(distMax - distMin));

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

        Rectangle rect = (Rectangle){ x, yFinal, w, 20 };

        // cria nó
        Plataforma *nova = CriarPlataforma(rect);

        // adiciona na lista
        if (!head) {
            head = tail = nova;
        } else {
            tail->next = nova;
            tail = nova;
        }
    }

    return head;
}


void DesenharPlataformas(Plataforma *lista)
{
    Plataforma *p = lista;

    while (p != NULL) {
        DrawRectangleRec(p->rect, DARKGRAY);
        p = p->next;
    }
}


void LiberarPlataformas(Plataforma *lista)
{
    Plataforma *p = lista;

    while (p != NULL) {
        Plataforma *tmp = p;
        p = p->next;
        free(tmp);
    }
}
