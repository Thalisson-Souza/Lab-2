#ifndef ARVORE_H
#define ARVORE_H

#include "carro.h"

typedef struct ArvoreNo {
    Carro carro;
    struct ArvoreNo *esquerda, *direita;
} ArvoreNo;

// Declarações das funções
ArvoreNo* inserirNaArvore(ArvoreNo *raiz, Carro carro, int (*cmp)(Carro, Carro));
ArvoreNo* removerDaArvore(ArvoreNo *raiz, Carro carro, int (*cmp)(Carro, Carro));
void percorrerArvore(ArvoreNo *raiz);

#endif
