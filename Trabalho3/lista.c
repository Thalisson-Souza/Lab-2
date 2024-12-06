#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "carro.h"
#include "lista.h"

// Função para criar uma lista vazia
ListaNo* criarLista() {
    return NULL;
}

// Função para inserir um carro na lista
ListaNo* inserirNaLista(ListaNo* lista, Carro carro) {
    ListaNo* novoNo = (ListaNo*)malloc(sizeof(ListaNo));    
    novoNo->carro = carro;                     
    novoNo->proximo = lista;                    
    return novoNo;
}

// Função para remover um carro da lista pela placa
ListaNo* removerDaLista(ListaNo* lista, char* placa) {
    ListaNo *anterior = NULL, *atual = lista;

    while (atual != NULL && strcmp(atual->carro.placa, placa) != 0) {   // Percorre a lista procurando o carro com a placa especificada
        anterior = atual;           // Armazena o nó anterior
        atual = atual->proximo;     // Move para o próximo nó
    }

    if (atual == NULL) return lista;  // Carro não encontrado

    if (anterior == NULL) {
        lista = atual->proximo;  // Atualiza a cabeça da lista para o próximo nó
    } else {
        anterior->proximo = atual->proximo;     // Remove o nó conectando o anterior ao próximo
    }

    free(atual);    // Libera a memória do nó removido
    return lista;
}

// Função para listar todos os carros da lista
void listarCarros(ListaNo* lista) {
    ListaNo* atual = lista;
    while (atual != NULL) {     // Percorre cada nó da lista e imprime os dados do carro
        printf("Placa: %s, Marca: %s, Ano: %d\n", atual->carro.placa, atual->carro.marca, atual->carro.ano);
        atual = atual->proximo;
    }
}
