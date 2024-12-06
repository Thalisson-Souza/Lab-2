#ifndef CARRO_H
#define CARRO_H

#include <string.h>

typedef struct Carro {
    char placa[10];
    char marca[20];
    int ano;
} Carro;

// Declarações das funções
int compararPorPlaca(Carro a, Carro b);
int compararPorMarca(Carro a, Carro b);
int compararPorAno(Carro a, Carro b);

#endif