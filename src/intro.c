#include "intro.h"
#include "raylib.h"
#include <math.h> // Para usar a função sin() no efeito de pulsar

#define LINHAS_CORACAO 6
#define COLUNAS_CORACAO 7

void RodarIntro(void) {
    // MATRIZ: Define o desenho do coração (pixel art via código)
    // 1 = Parte vermelha, 0 = Vazio
    int matrizCoracao[LINHAS_CORACAO][COLUNAS_CORACAO] = {
        {0, 1, 1, 0, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1},
        {0, 1, 1, 1, 1, 1, 0},
        {0, 0, 1, 1, 1, 0, 0},
        {0, 0, 0, 1, 0, 0, 0}
    };

    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    
    // Tamanho de cada "pixel" quadrado do coração
    int tamanhoBloco = 40; 
    
    // Cálculos para centralizar a matriz na tela
    int larguraTotalCoracao = COLUNAS_CORACAO * tamanhoBloco;
    int alturaTotalCoracao = LINHAS_CORACAO * tamanhoBloco;
    int offsetX = (screenWidth - larguraTotalCoracao) / 2;
    int offsetY = (screenHeight - alturaTotalCoracao) / 2 - 50; // Levemente para cima para caber o texto

    float tempo = 0.0f;
    bool introFinalizada = false;
    bool mostrarTitulo = false;

    // Loop da Introdução
    while (!WindowShouldClose() && !introFinalizada) {
        float dt = GetFrameTime();
        tempo += dt;

        // Controles de tempo
        if (tempo > 2.0f) mostrarTitulo = true; // Mostra o texto após 2 segundos
        if (tempo > 6.0f) introFinalizada = true; // Encerra a intro após 6 segundos

        // Pular intro com Enter
        if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) {
            introFinalizada = true;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE); // Fundo branco para destacar o coração

        // --- 1. Desenhar o Coração baseando-se na Matriz ---
        for (int i = 0; i < LINHAS_CORACAO; i++) {
            for (int j = 0; j < COLUNAS_CORACAO; j++) {
                
                // Se a célula da matriz for 1, desenhamos um bloco
                if (matrizCoracao[i][j] == 1) {
                    
                    // Efeito visual: Coração pulsando usando seno
                    float fatorPulsar = 0.0f;
                    if (mostrarTitulo) {
                        fatorPulsar = sinf(tempo * 5.0f) * 4.0f; // Varia o tamanho levemente
                    }

                    // Desenha o retângulo na posição correta
                    DrawRectangle(
                        offsetX + j * tamanhoBloco - (int)fatorPulsar/2, 
                        offsetY + i * tamanhoBloco - (int)fatorPulsar/2, 
                        tamanhoBloco + (int)fatorPulsar, 
                        tamanhoBloco + (int)fatorPulsar, 
                        RED
                    );
                }
            }
        }

        // --- 2. Desenhar o Título ---
        if (mostrarTitulo) {
            const char* titulo = "AMOR & ENDERECO";
            int fontSize = 50;
            int textWidth = MeasureText(titulo, fontSize);
            
            // Desenha o texto abaixo do coração
            DrawText(titulo, 
                     screenWidth / 2 - textWidth / 2, 
                     offsetY + alturaTotalCoracao + 30, 
                     fontSize, 
                     MAROON);
                     
            DrawText("Pressione ENTER...", screenWidth/2 - MeasureText("Pressione ENTER...", 20)/2, screenHeight - 40, 20, GRAY);
        }

        EndDrawing();
    }
}