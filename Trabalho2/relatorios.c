#include <stdio.h>
#include "relatorios.h"

void gerar_relatorio_classificacao(Time times[], int num_times) {
    printf("===============================================================\n");
    printf("                   Relatorio de Classificacao\n");
    printf("===============================================================\n");

    // Loop para percorrer cada time
    for (int i = 0; i < num_times; i++) {
        printf("Time: %s\n", times[i].nome);
        printf(" - Gols Feitos: %d, Gols Sofridos: %d, Cartoes Amarelos: %d, Cartoes Vermelhos: %d\n", 
               times[i].gols_feitos, times[i].gols_sofridos, 
               times[i].cartoes_amarelos, times[i].cartoes_vermelhos);
    }
    printf("===============================================================\n\n\n\n");
}

void ordenar_jogadores_por_gols(Jogador jogadores[], int num_jogadores) {
    for (int i = 0; i < num_jogadores - 1; i++) {
        for (int j = 0; j < num_jogadores - 1 - i; j++) {
            if (jogadores[j].gols < jogadores[j + 1].gols) {
                // Troca os jogadores
                Jogador temp = jogadores[j];
                jogadores[j] = jogadores[j + 1];
                jogadores[j + 1] = temp;
            }
        }
    }
}

void gerar_relatorio_artilharia(Time times[], int num_times) {
    printf("===============================================================\n");
    printf("                   Relatorio de Artilharia\n");
    printf("===============================================================\n");

    for (int i = 0; i < num_times; i++) {
        ordenar_jogadores_por_gols(times[i].jogadores, times[i].num_jogadores);

        printf("\n---------------------------------------------------------------\n");
        printf("Time: %s\n", times[i].nome);

        // Loop para percorrer os jogadores do time
        int encontrou_gols = 0;
        for (int j = 0; j < times[i].num_jogadores; j++) {
            Jogador jogador = times[i].jogadores[j];
            if (jogador.gols > 0) {
                printf(" - %s - Gols: %d\n", jogador.nome, jogador.gols);
                encontrou_gols = 1;
            }
        }
        if (!encontrou_gols) {
            printf("Nenhum gol marcado.\n");
        }
        printf("---------------------------------------------------------------\n");
    }
    printf("===============================================================\n\n\n");
}



void gerar_relatorio_estatisticas(Time times[], int num_times) {
    printf("===============================================================\n");
    printf("                   Relatorio de Estatisticas\n");
    printf("===============================================================\n");

    for (int i = 0; i < num_times; i++) {
        printf("Time: %s\n", times[i].nome);
        printf("  - Gols Feitos: %d, Gols Sofridos: %d, Cartoes Amarelos: %d, Cartoes Vermelhos: %d, Faltas: %d\n",
            times[i].gols_feitos, times[i].gols_sofridos, times[i].cartoes_amarelos, times[i].cartoes_vermelhos, times[i].faltas);
    }
    printf("===============================================================\n");
}
