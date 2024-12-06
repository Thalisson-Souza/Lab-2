#include <stdio.h>
#include <string.h>
#include "carro.h"
#include "arvore.h"
#include "busca.h"

// Funções de comparação para as árvores
int compararPorPlaca(Carro a, Carro b) {
    return strcmp(a.placa, b.placa);    // Compara as strings das placas
}

int compararPorMarca(Carro a, Carro b) {
    return strcmp(a.marca, b.marca);    // Compara as strings das marcas
}

int compararPorAno(Carro a, Carro b) {  
    return a.ano - b.ano;       // Retorna a diferença entre os anos
}

// Função para buscar carro pela placa
void buscarCarroPorPlaca(ArvoreNo *arvore, char *placa) {
    if (!arvore) {  // Verifica se o nó atual da árvore é nulo
        printf("Carro não encontrado.\n");
        return;
    }

    // Compara a placa fornecida com a placa do nó atual
    int cmp = strcmp(placa, arvore->carro.placa);
    if (cmp == 0) { // Caso as placas sejam iguais
        printf("\nCarro encontrado: Placa: %s, Marca: %s, Ano: %d\n",
               arvore->carro.placa, arvore->carro.marca, arvore->carro.ano);
    } else if (cmp < 0) {   // Caso a placa fornecida seja menor (em ordem alfabética)
        buscarCarroPorPlaca(arvore->esquerda, placa);   // Busca na subárvore esquerda
    } else {
        buscarCarroPorPlaca(arvore->direita, placa); // Busca na subárvore direita
    }
}