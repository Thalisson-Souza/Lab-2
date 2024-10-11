#ifndef PECA_H
#define PECA_H

#include <stdbool.h>

typedef struct{
    char tipo;
    char cor;
} Peca;

bool posicaoValida(int x, int y);

bool pecaAliada(Peca* peca1, Peca* peca2);

bool caminhoLinhaColunaLivre(Peca*** tabuleiro, int inicioX, int inicioY, int fimX, int fimY);

bool caminhoDiagonalLivre(Peca*** tabuleiro, int inicioX, int inicioY, int fimX, int fimY);

void movimentoUsuario(Peca*** tabuleiro, int jogadorAtual);

void desenhar_tabuleiro(Peca*** tabuleiro);

#endif