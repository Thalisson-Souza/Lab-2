#include <stdlib.h>
#include <stdio.h>
#include "tabuleiro.h"

#define VERMELHO "\033[31m"
#define RESET "\033[0m"
#define MAGENTA "\033[35m"
#define AMARELO "\033[33m"


Peca posicoesIniciais[8][8] = {
    {{'T', 'B'}, {'C', 'B'}, {'B', 'B'}, {'D', 'B'}, {'R', 'B'}, {'B', 'B'}, {'C', 'B'}, {'T', 'B'}}, // Peças brancas
    {{'*', 'B'}, {'*', 'B'}, {'*', 'B'}, {'*', 'B'}, {'*', 'B'}, {'*', 'B'}, {'*', 'B'}, {'*', 'B'}}, // Peões brancos ( lado esquerdo-> icone da peça; lado direio -> cor da peça )
    {{' ', ' '}, {' ', ' '}, {' ', ' '}, {' ', ' '}, {' ', ' '}, {' ', ' '}, {' ', ' '}, {' ', ' '}}, 
    {{' ', ' '}, {' ', ' '}, {' ', ' '}, {' ', ' '}, {' ', ' '}, {' ', ' '}, {' ', ' '}, {' ', ' '}}, 
    {{' ', ' '}, {' ', ' '}, {' ', ' '}, {' ', ' '}, {' ', ' '}, {' ', ' '}, {' ', ' '}, {' ', ' '}}, 
    {{' ', ' '}, {' ', ' '}, {' ', ' '}, {' ', ' '}, {' ', ' '}, {' ', ' '}, {' ', ' '}, {' ', ' '}}, 
    {{'@', 'P'}, {'@', 'P'}, {'@', 'P'}, {'@', 'P'}, {'@', 'P'}, {'@', 'P'}, {'@', 'P'}, {'@', 'P'}}, // Peões pretos ( lado esquerdo-> icone da peça; lado direio -> cor da peça )
    {{'t', 'P'}, {'c', 'P'}, {'b', 'P'}, {'d', 'P'}, {'r', 'P'}, {'b', 'P'}, {'c', 'P'}, {'t', 'P'}}  // Peças pretas
};

// Criar tabuleiro 8x8 com a alocação dinâmica e inicializar com as posições iniciais
Peca*** criar_tabuleiro() {
    Peca*** tabuleiro = (Peca***)malloc(8 * sizeof(Peca**));
    for (int i = 0; i < 8; i++) {
        tabuleiro[i] = (Peca**)malloc(8 * sizeof(Peca*));
        for (int j = 0; j < 8; j++) {
            tabuleiro[i][j] = (Peca*)malloc(sizeof(Peca)); // Aloca espaço para a peça ou casa vazia
            if (posicoesIniciais[i][j].tipo != ' ') {
                tabuleiro[i][j]->tipo = posicoesIniciais[i][j].tipo; // Atribui o tipo da peça
                tabuleiro[i][j]->cor = posicoesIniciais[i][j].cor;   // Atribui a cor da peça
            } else {
                tabuleiro[i][j]->tipo = ' '; // Define como casa vazia
                tabuleiro[i][j]->cor = ' ';  // Cor vazia para casas sem peça
            }
        }
    }
    return tabuleiro;
}

// Função para desenhar o tabuleiro
void desenhar_tabuleiro(Peca*** tabuleiro) {
    char peca;

    for(int i = 0; i < 8; i++){
        printf("   ---------------------------------\n");
        printf(AMARELO " %d " RESET, 8 - i); // Inserir coordenada Y na coluna (1 à 8)
        for(int j = 0; j < 8; j++){
            if (tabuleiro[i][j] != NULL){
                peca = tabuleiro[i][j]->tipo;
            }else {
                peca = ' ';
            }
            printf("| %c ", peca);
        }
        printf("|\n");
    }
    printf("   ---------------------------------\n");
    printf(AMARELO "     a   b   c   d   e   f   g   h \n" RESET); // Inserir coordenada X na coluna (A à H)
}

// Função para destruir o tabuleiro liberando a memória
void destruir_tabuleiro(Peca*** tabuleiro){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(tabuleiro[i][j] != NULL){
                free(tabuleiro[i][j]); // Libera as peças
            }
        }
        free(tabuleiro[i]); // Libera as linhas
    }
    free(tabuleiro); //Libera a matriz inteira
}