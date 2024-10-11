#ifndef TABULEIRO_H
#define TABULEIRO_H 
#include "peca.h"

Peca*** criar_tabuleiro();
void iniciarTabuleiro();
void desenhar_tabuleiro(Peca*** tabuleiro);
void destruir_tabuleiro(Peca*** tabuleiro);

#endif