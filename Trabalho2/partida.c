#include <stdio.h>
#include <string.h>
#include "partida.h"

void cadastrar_partida(Rodada *rodada, Time *time1, Time *time2) {
    if (rodada->num_partidas >= MAX_PARTIDAS) {
        printf("Limite de partidas na rodada atingido.\n");
        return;
    }
    Partida *partida = &rodada->partidas[rodada->num_partidas];
    partida->time1 = time1;
    partida->time2 = time2;
    partida->num_eventos = 0;
    partida->gols_time1 = 0;
    partida->gols_time2 = 0;

    rodada->num_partidas++; 
}

void registrar_evento(Partida *partida, int minuto, char descricao[]) {
    if (partida->num_eventos >= MAX_EVENTOS) {
        printf("Limite de eventos na partida atingido.\n");
        return;
    }

    // Registra o evento na partida
    Evento *evento = &partida->eventos[partida->num_eventos];
    evento->minuto = minuto;
    strcpy(evento->descricao, descricao);
    partida->num_eventos++;

    // Verifica se o evento é um gol
    if (strstr(descricao, "Gol") != NULL) {
        if (strstr(descricao, partida->time1->nome) != NULL) {
            // Gol do time1
            partida->gols_time1++;
            partida->time1->gols_feitos++;

            // Atualizando o jogador que fez o gol
            for (int i = 0; i < partida->time1->num_jogadores; i++) {
                if (strstr(descricao, partida->time1->jogadores[i].nome) != NULL) {
                    partida->time1->jogadores[i].gols++;
                    break;
                }
            }
        } else if (strstr(descricao, partida->time2->nome) != NULL) {
            // Gol do time2
            partida->gols_time2++;
            partida->time2->gols_feitos++;

            // Atualizando o jogador que fez o gol
            for (int i = 0; i < partida->time2->num_jogadores; i++) {
                if (strstr(descricao, partida->time2->jogadores[i].nome) != NULL) {
                    partida->time2->jogadores[i].gols++;
                    break;
                }
            }
        }
        // Atualizando os gols sofridos para o time adversário
        if (strstr(descricao, partida->time1->nome) != NULL) {
            partida->time2->gols_sofridos++;
        } else if (strstr(descricao, partida->time2->nome) != NULL) {
            partida->time1->gols_sofridos++;
        }
    }
    // Verifica se o evento é um cartão amarelo
    if (strstr(descricao, "Cartao Amarelo") != NULL) {
        if (strstr(descricao, partida->time1->nome) != NULL) {
            // Cartão Amarelo para um jogador do time1
            partida->time1->cartoes_amarelos++;
            for (int i = 0; i < partida->time1->num_jogadores; i++) {
                if (strstr(descricao, partida->time1->jogadores[i].nome) != NULL) {
                    partida->time1->jogadores[i].cartoes_amarelos++;
                    break;
                }
            }
        } else if (strstr(descricao, partida->time2->nome) != NULL) {
            // Cartão Amarelo para um jogador do time2
            partida->time2->cartoes_amarelos++;
            for (int i = 0; i < partida->time2->num_jogadores; i++) {
                if (strstr(descricao, partida->time2->jogadores[i].nome) != NULL) {
                    partida->time2->jogadores[i].cartoes_amarelos++;
                    break;
                }
            }
        }
    }
    // Verifica se o evento é um cartão vermelho
    if (strstr(descricao, "Cartao Vermelho") != NULL) {
        if (strstr(descricao, partida->time1->nome) != NULL) {
            // Cartão Vermelho para um jogador do time1
            partida->time1->cartoes_vermelhos++;
            for (int i = 0; i < partida->time1->num_jogadores; i++) {
                if (strstr(descricao, partida->time1->jogadores[i].nome) != NULL) {
                    partida->time1->jogadores[i].cartoes_vermelhos++;
                    break;
                }
            }
        } else if (strstr(descricao, partida->time2->nome) != NULL) {
            // Cartão Vermelho para um jogador do time2
            partida->time2->cartoes_vermelhos++;
            for (int i = 0; i < partida->time2->num_jogadores; i++) {
                if (strstr(descricao, partida->time2->jogadores[i].nome) != NULL) {
                    partida->time2->jogadores[i].cartoes_vermelhos++;
                    break;
                }
            }
        }
    }
}