#ifndef PARTIDA_H
#define PARTIDA_H

#include "time.h"

#define MAX_PARTIDAS 20
#define MAX_EVENTOS 100

typedef struct {
    int minuto;
    char descricao[100];
} Evento;

typedef struct {
    Time *time1;
    Time *time2;
    Evento eventos[MAX_EVENTOS];
    int num_eventos;
    int gols_time1;
    int gols_time2;
} Partida;

typedef struct {
    int numero_rodada;
    Partida partidas[MAX_PARTIDAS];
    int num_partidas;
} Rodada;

void cadastrar_partida(Rodada *rodada, Time *time1, Time *time2);
void registrar_evento(Partida *partida, int minuto, char descricao[]);

#endif
