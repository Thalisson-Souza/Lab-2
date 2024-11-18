#include <stdio.h>
#include <string.h>
#include "time.h"

void cadastrar_time(Time times[], int *num_times, char nome[], char estado[]) {
    if (*num_times >= 10) {
        printf("Limite de times atingido.\n");
        return;
    }
    strcpy(times[*num_times].nome, nome);
    strcpy(times[*num_times].estado, estado);
    times[*num_times].num_jogadores = 0;
    times[*num_times].gols_feitos = 0;
    times[*num_times].gols_sofridos = 0;
    times[*num_times].cartoes_amarelos = 0;
    times[*num_times].cartoes_vermelhos = 0;
    times[*num_times].faltas = 0;
    (*num_times)++;
}

void cadastrar_jogador(Time *time, char nome[], char posicao[], int idade, int numero_camisa, int gols) {
    if (time->num_jogadores >= 11) {
        printf("Limite de jogadores atingido.\n");
        return;
    }
    Jogador *jogador = &time->jogadores[time->num_jogadores];
    strcpy(jogador->nome, nome);
    strcpy(jogador->posicao, posicao);
    jogador->idade = idade;
    jogador->numero_camisa = numero_camisa;
    jogador->gols = gols;
    jogador->cartoes_amarelos = 0; 
    jogador->cartoes_vermelhos = 0; 
    time->num_jogadores++;
}

void excluir_jogador(Time *time, int numero_camisa) {
    int encontrado = -1;
    for (int i = 0; i < time->num_jogadores; i++) {
        if (time->jogadores[i].numero_camisa == numero_camisa) {
            encontrado = i;
            break;
        }
    }
    if (encontrado != -1) {
        for (int i = encontrado; i < time->num_jogadores - 1; i++) {
            time->jogadores[i] = time->jogadores[i + 1];
        }
        time->num_jogadores--;
        printf("Jogador com número %d removido.\n", numero_camisa);
    } else {
        printf("Jogador não encontrado.\n");
    }
}

Time* buscar_time(Time times[], int num_times, char nome[]) {
    for (int i = 0; i < num_times; i++) {
        if (strcmp(times[i].nome, nome) == 0) {
            printf(" - Time '%s' encontrado.\n", nome);
            printf("===============================================================\n");
            return &times[i];
        }
    }
    printf(" - Time '%s' nao encontrado.\n", nome);
    printf("===============================================================\n");
    return NULL;
}

Jogador* buscar_jogador(Time *time, int numero_camisa) {
    for (int i = 0; i < time->num_jogadores; i++) {
        if (time->jogadores[i].numero_camisa == numero_camisa) {
            printf(" - Jogador com numero %d encontrado no time '%s'.\n", numero_camisa, time->nome);
            printf("===============================================================\n");
            return &time->jogadores[i];
        }
    }
    printf(" - Jogador com numero %d nao encontrado no time '%s'.\n", numero_camisa, time->nome);
    printf("===============================================================\n");
    return NULL;
}

void excluir_time(Time times[], int *num_times, char nome[]) {
    int encontrado = -1;
    for (int i = 0; i < *num_times; i++) {
        if (strcmp(times[i].nome, nome) == 0) {
            encontrado = i;
            break;
        }
    }
    if (encontrado != -1) {
        for (int i = encontrado; i < *num_times - 1; i++) {
            times[i] = times[i + 1];
        }
        (*num_times)--;
        printf("Time '%s' removido.\n", nome);
    } else {
        printf("Time '%s' não encontrado.\n");
    }
}