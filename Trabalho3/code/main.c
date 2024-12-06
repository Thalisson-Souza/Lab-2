#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "carro.h"
#include "lista.h"
#include "arvore.h"
#include "busca.h"  

int main() {
    ListaNo *lista = criarLista();
    ArvoreNo *arvorePlaca = NULL, *arvoreMarca = NULL, *arvoreAno = NULL;

    // Carros já inseridos inicialmente
    Carro c1 = {"ABC1234", "Toyota", 2020};
    Carro c2 = {"XYZ5678", "Honda", 2018};
    Carro c3 = {"DEF2345", "Ford", 2021};

    // Inserção inicial
    lista = inserirNaLista(lista, c1);
    lista = inserirNaLista(lista, c2);
    lista = inserirNaLista(lista, c3);

    arvorePlaca = inserirNaArvore(arvorePlaca, c1, compararPorPlaca);
    arvorePlaca = inserirNaArvore(arvorePlaca, c2, compararPorPlaca);
    arvorePlaca = inserirNaArvore(arvorePlaca, c3, compararPorPlaca);

    arvoreMarca = inserirNaArvore(arvoreMarca, c1, compararPorMarca);
    arvoreMarca = inserirNaArvore(arvoreMarca, c2, compararPorMarca);
    arvoreMarca = inserirNaArvore(arvoreMarca, c3, compararPorMarca);

    arvoreAno = inserirNaArvore(arvoreAno, c1, compararPorAno);
    arvoreAno = inserirNaArvore(arvoreAno, c2, compararPorAno);
    arvoreAno = inserirNaArvore(arvoreAno, c3, compararPorAno);

    int opcao;
    do {
        printf("\nMenu:\n");
        printf("1. Inserir carro\n");
        printf("2. Excluir carro\n");
        printf("3. Buscar carro por placa\n");
        printf("4. Listar carros ordenados por placa\n");
        printf("5. Listar carros ordenados por marca\n");
        printf("6. Listar carros ordenados por ano\n");
        printf("0. Sair\n");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1) {   // Inserir um novo carro
            Carro novoCarro;
            printf("Digite a placa (no formato-> XXX1234): ");
            scanf("%s", novoCarro.placa);
            printf("Digite a marca do carro a ser inserido: ");
            scanf("%s", novoCarro.marca);
            printf("Digite o ano de fabricacao (ex: 2020): ");
            scanf("%d", &novoCarro.ano);

            // Insere o carro na lista e nas árvores
            lista = inserirNaLista(lista, novoCarro);
            arvorePlaca = inserirNaArvore(arvorePlaca, novoCarro, compararPorPlaca);
            arvoreMarca = inserirNaArvore(arvoreMarca, novoCarro, compararPorMarca);
            arvoreAno = inserirNaArvore(arvoreAno, novoCarro, compararPorAno);

            printf("\n Carro com placa '%s' inserido com sucesso!\n", novoCarro.placa);

        } else if (opcao == 2) {    // Excluir um carro pela placa
            char placa[10];
            printf("\nDigite a placa do carro a ser removido: ");
            scanf("%s", placa);

            // Remove o carro da lista e das árvores
            lista = removerDaLista(lista, placa);
            Carro carroTemp;
            strcpy(carroTemp.placa, placa);
            arvorePlaca = removerDaArvore(arvorePlaca, carroTemp, compararPorPlaca);
            arvoreMarca = removerDaArvore(arvoreMarca, carroTemp, compararPorMarca);
            arvoreAno = removerDaArvore(arvoreAno, carroTemp, compararPorAno);

            printf("\n Carro com placa '%s' foi removido (se existia armazenado)!\n", placa);

        } else if (opcao == 3) {    // Buscar um carro pela placa
            char placa[10];
            printf("Digite a placa do carro a ser buscado: ");
            scanf("%s", placa);

            buscarCarroPorPlaca(arvorePlaca, placa); 
        } else if (opcao == 4) {                            // Listar carros ordenados por placa
            printf("Carros ordenados por placa:\n");
            listarCarros(lista);
        } else if (opcao == 5) {                            // Listar carros ordenados por marca
            printf("Carros ordenados por marca:\n");
            percorrerArvore(arvoreMarca);
        } else if (opcao == 6) {                            // Listar carros ordenados por ano
            printf("Carros ordenados por ano:\n");
            percorrerArvore(arvoreAno);
        }
    } while (opcao != 0);   // Sai do loop quando o usuário digita 0

    return 0;
}