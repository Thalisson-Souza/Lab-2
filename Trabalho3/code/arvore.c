#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

ArvoreNo* inserirNaArvore(ArvoreNo *raiz, Carro carro, int (*cmp)(Carro, Carro)) {
    if (!raiz) {
        ArvoreNo *novoNo = (ArvoreNo*) malloc(sizeof(ArvoreNo));
        novoNo->carro = carro;      // Atribui os dados do carro ao novo nó
        novoNo->esquerda = novoNo->direita = NULL;  // Inicializa os ponteiros como NULL
        return novoNo;
    }
    
    if (cmp(carro, raiz->carro) < 0) {   // Compara o carro a ser inserido com o carro do nó atual
        raiz->esquerda = inserirNaArvore(raiz->esquerda, carro, cmp);   // Insere na subárvore esquerda
    }else{
        raiz->direita = inserirNaArvore(raiz->direita, carro, cmp); // Insere na subárvore direita
    }
    return raiz;    // Retorna a raiz atualizada
}

ArvoreNo* removerDaArvore(ArvoreNo *raiz, Carro carro, int (*cmp)(Carro, Carro)) {
    if (!raiz) {    // Caso base: se a raiz é nula, retorna NULL
        return NULL;    
    }

    if (cmp(carro, raiz->carro) < 0)     // Compara o carro a ser removido com o carro do nó atual
        raiz->esquerda = removerDaArvore(raiz->esquerda, carro, cmp);   // Procura na subárvore esquerda
    else if (cmp(carro, raiz->carro) > 0)
        raiz->direita = removerDaArvore(raiz->direita, carro, cmp); // Procura na subárvore direita
    else {
        // Caso o nó tenha no máximo um filho (ou nenhum)
        if (!raiz->esquerda) {
            ArvoreNo *temp = raiz->direita; // Guarda a subárvore direita
            free(raiz);                     // Libera o nó atual
            return temp;                    // Retorna o filho direito (pode ser NULL)
        }       
        if (!raiz->direita) {   
            ArvoreNo *temp = raiz->esquerda;    // Guarda a subárvore esquerda
            free(raiz);                         // Libera o nó atual
            return temp;                        // Retorna o filho esquerdo
        }

         // Caso o nó tenha dois filhos: encontra o sucessor em ordem (menor da subárvore direita)
        ArvoreNo *temp = raiz->direita;
        while (temp->esquerda)
            temp = temp->esquerda;  // Percorre até o nó mais à esquerda da subárvore direita

        raiz->carro = temp->carro;  // Substitui os dados do nó atual pelo sucessor
        raiz->direita = removerDaArvore(raiz->direita, temp->carro, cmp);
    }

    return raiz;
}

void percorrerArvore(ArvoreNo *raiz) {
    if (raiz) {
        percorrerArvore(raiz->esquerda);    // Visita a subárvore esquerda
        printf("Placa: %s, Marca: %s, Ano: %d\n", raiz->carro.placa, raiz->carro.marca, raiz->carro.ano);
        percorrerArvore(raiz->direita);     // Visita a subárvore direita
    }
}
