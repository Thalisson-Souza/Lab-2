#ifndef TIME_H
#define TIME_H

#define MAX_JOGADORES 25

typedef struct {
    char nome[50];
    char posicao[20];
    int idade;
    int numero_camisa;
    int gols;
    int cartoes_amarelos;
    int cartoes_vermelhos;
} Jogador;

typedef struct {
    char nome[50];
    char estado[20];
    Jogador jogadores[MAX_JOGADORES];
    int num_jogadores;
    int gols_feitos;
    int gols_sofridos;
    int cartoes_amarelos;
    int cartoes_vermelhos;
    int faltas;
} Time;

void cadastrar_time(Time times[], int *num_times, char nome[], char estado[]);
void cadastrar_jogador(Time *time, char nome[], char posicao[], int idade, int numero_camisa, int gols);
void excluir_jogador(Time *time, int numero_camisa);
void excluir_time(Time times[], int *num_times, char nome[]);

Time* buscar_time(Time times[], int num_times, char nome[]);
Jogador* buscar_jogador(Time *time, int numero_camisa);

#endif