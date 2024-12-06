#ifndef LISTA_H
#define LISTA_H

#include "carro.h"

typedef struct ListaNo {
    Carro carro;
    struct ListaNo *proximo;
} ListaNo;

// Declarações das funções
ListaNo* criarLista();
ListaNo* inserirNaLista(ListaNo* lista, Carro carro);
ListaNo* removerDaLista(ListaNo* lista, char* placa);  // Função de remoção
void listarCarros(ListaNo* lista);  // Função para listar os carros

#endif
