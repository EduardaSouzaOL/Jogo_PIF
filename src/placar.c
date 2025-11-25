#include "placar.h"
#include <stdio.h>

#define NOME_ARQUIVO "recorde.txt"

int CarregarRecorde(void) {
    int recorde = 0;
    
    // Tenta abrir o arquivo para leitura ("r" = read)
    FILE *arquivo = fopen(NOME_ARQUIVO, "r");
    
    if (arquivo != NULL) {
        // Lê um inteiro do arquivo
        fscanf(arquivo, "%d", &recorde);
        fclose(arquivo);
    }
    
    return recorde;
}

void SalvarRecorde(int pontuacaoAtual) {
    int recordeAntigo = CarregarRecorde();

    // Só salva se a pontuação atual for maior que o recorde
    if (pontuacaoAtual > recordeAntigo) {
        // Abre o arquivo para escrita ("w" = write), o que limpa o arquivo anterior
        FILE *arquivo = fopen(NOME_ARQUIVO, "w");
        
        if (arquivo != NULL) {
            fprintf(arquivo, "%d", pontuacaoAtual);
            fclose(arquivo);
        }
    }
}