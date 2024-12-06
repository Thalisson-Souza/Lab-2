#ifndef BUSCA_H
#define BUSCA_H

#include "carro.h"
#include "arvore.h"

// Definição das funções de comparação para as árvores
int compararPorPlaca(Carro a, Carro b);
int compararPorMarca(Carro a, Carro b);
int compararPorAno(Carro a, Carro b);

// Definição da função para buscar carro pela placa
void buscarCarroPorPlaca(ArvoreNo *arvore, char *placa);

#endif
