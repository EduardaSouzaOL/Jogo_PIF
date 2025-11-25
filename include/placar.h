#ifndef PLACAR_H
#define PLACAR_H

// Função para ler o recorde atual do arquivo
int CarregarRecorde(void);

// Função para verificar e salvar um novo recorde se ele for maior que o anterior
void SalvarRecorde(int pontuacaoAtual);

#endif