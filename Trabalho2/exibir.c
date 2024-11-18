#include <stdio.h>
#include "time.h"
#include "partida.h"
#include "exibir.h"

// Exibe informações detalhadas de um time
void exibir_time(Time *time) {
    // Inicializar as estatísticas antes de exibir
    time->gols_feitos = 0;
    time->gols_sofridos = 0;
    time->cartoes_amarelos = 0;
    time->cartoes_vermelhos = 0;
    time->faltas = 0;

    // Calcular as estatísticas com base nos jogadores
    for (int i = 0; i < time->num_jogadores; i++) {
        Jogador *jogador = &time->jogadores[i];
        time->gols_feitos += jogador->gols;
        // Supondo que o jogador tenha as variáveis de cartões e faltas, acrescente-as
        time->cartoes_amarelos += jogador->cartoes_amarelos;
        time->cartoes_vermelhos += jogador->cartoes_vermelhos;
        // Se faltas também forem uma variável dos jogadores, faça a soma
        // time->faltas += jogador->faltas;
    }

    // Exibir o time
    printf("===============================================================\n");
    printf("Time: %s\n", time->nome);
    printf("Estado: %s\n", time->estado);

    if (time->num_jogadores > 0) {
        printf("\nJogadores:\n");
        printf("---------------------------------------------------------------\n");
        printf("| %-20s | %-12s | %-4s | %-7s | %-4s |\n", "Nome", "Posicao", "Idade", "Numero", "Gols");
        printf("---------------------------------------------------------------\n");
        for (int i = 0; i < time->num_jogadores; i++) {
            Jogador jogador = time->jogadores[i];
            printf("| %-20s | %-12s | %-4d | %-7d | %-4d |\n", 
                   jogador.nome, jogador.posicao, jogador.idade, jogador.numero_camisa, jogador.gols);
        }
        printf("---------------------------------------------------------------\n");
    } else {
        printf("Nenhum jogador cadastrado.\n");
    }

    // Exibir as estatísticas do time
    printf("\nEstatisticas do Time:\n");
    printf("  Gols Feitos:       %d\n", time->gols_feitos);
    printf("  Gols Sofridos:     %d\n", time->gols_sofridos);
    printf("  Cartoes Amarelos:  %d\n", time->cartoes_amarelos);
    printf("  Cartoes Vermelhos: %d\n", time->cartoes_vermelhos);
    printf("  Faltas:            %d\n", time->faltas);

    printf("===============================================================\n\n\n");
}


// Exibe todos os times cadastrados
void exibir_todos_times(Time times[], int num_times) {
    if (num_times == 0) {
        printf("Nenhum time cadastrado.\n");
        return;
    }

    for (int i = 0; i < num_times; i++) {
        exibir_time(&times[i]);
    }
}

// Exibe informações detalhadas de uma partida
void exibir_partida(Partida partida) {
    printf("\n---------------------------------------------------------------\n");
    printf("Partida: %s x %s\n", partida.time1->nome, partida.time2->nome);

    if (partida.num_eventos > 0) {
        printf("Eventos da Partida:\n");
        for (int i = 0; i < partida.num_eventos; i++) {
            printf("  - Minuto %d: %s\n", partida.eventos[i].minuto, partida.eventos[i].descricao);
        }
    } else {
        printf("Nenhum evento registrado nesta partida.\n");
    }
    printf("---------------------------------------------------------------\n\n\n");
}

// Exibe informações detalhadas de uma rodada
void exibir_rodada(Rodada rodada) {
    printf("===============================================================\n");
    printf("Rodada %d:\n", rodada.numero_rodada);
    for (int i = 0; i < rodada.num_partidas; i++) {
        exibir_partida(rodada.partidas[i]);
    }
    // printf("===============================================================\n");
}

// Exibe todas as rodadas cadastradas
void exibir_todas_rodadas(Rodada rodadas[], int num_rodadas) {
    if (num_rodadas == 0) {
        printf("Nenhuma rodada cadastrada.\n");
        return;
    }

    for (int i = 0; i < num_rodadas; i++) {
        exibir_rodada(rodadas[i]);
    }
}


// Exibe as informações de um time encontrado
void exibir_time_encontradoPESQUISA(Time *time) {
    if (time != NULL) {
        printf("\n=== Time Encontrado ===\n");
        printf("- Nome: %s\n", time->nome);
        printf("- Estado: %s\n", time->estado);
        printf("- Numero de Jogadores: %d\n", time->num_jogadores);
        printf("- Gols Feitos: %d\n", time->gols_feitos);
        printf("- Gols Sofridos: %d\n", time->gols_sofridos);
        printf("- Cartoes Amarelos: %d\n", time->cartoes_amarelos);
        printf("- Cartoes Vermelhos: %d\n", time->cartoes_vermelhos);
        printf("- Faltas: %d\n", time->faltas);
        printf("\n=======================\n");
    } else {
        printf("\nTime nao encontrado.\n");
    }
}

void exibir_jogador_encontradoPESQUISA(Jogador *jogador) {
    if (jogador != NULL) {
        printf("\n=== Jogador Encontrado ===\n");
        printf("- Nome: %s\n", jogador->nome);
        printf("- Posicao: %s\n", jogador->posicao);
        printf("- Idade: %d\n", jogador->idade);
        printf("- Numero da Camisa: %d\n", jogador->numero_camisa);
        printf("- Gols: %d\n", jogador->gols);
        printf("\n==========================\n");
    } else {
        printf("\nJogador nao encontrado.\n");
    }
}