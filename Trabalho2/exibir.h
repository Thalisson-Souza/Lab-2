#ifndef EXIBIR_H
#define EXIBIR_H

#include "time.h"
#include "partida.h"

void exibir_time(Time *time);
void exibir_todos_times(Time times[], int num_times);
void exibir_partida(Partida partida);
void exibir_rodada(Rodada rodada);
void exibir_todas_rodadas(Rodada rodadas[], int num_rodadas);

void exibir_jogador_encontradoPESQUISA(Jogador *jogador);
void exibir_time_encontradoPESQUISA(Time *time);

#endif 
