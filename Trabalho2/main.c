#include <stdio.h>
#include "time.h"
#include "partida.h"
#include "exibir.h"
#include "relatorios.h"

#define MAX_TIMES 10
#define MAX_RODADAS 5

int main() {
    Time times[MAX_TIMES];
    int num_times = 0;

    cadastrar_time(times, &num_times, "Internacional", "Rio Grande do Sul");
    cadastrar_time(times, &num_times, "Gremio", "Rio Grande do Sul");

    // Cadastro de jogadores para o time 1
    cadastrar_jogador(&times[0], "Sergio Rochet", "Goleiro", 30, 1, 0);
    cadastrar_jogador(&times[0], "Rodrigo Moledo", "Zagueiro", 30, 2, 0);
    cadastrar_jogador(&times[0], "Victor Cuesta", "Zagueiro", 32, 3, 0);
    cadastrar_jogador(&times[0], "Alexandro Bernabei", "Lateral", 22, 26, 3);
    cadastrar_jogador(&times[0], "Edenilson", "Meio-campo", 31, 5, 1);
    cadastrar_jogador(&times[0],"Bruno Tabata", "Meio-campo", 28, 17, 2);
    cadastrar_jogador(&times[0], "Enner Valencia", "Atacante", 34, 77, 2);
    cadastrar_jogador(&times[0], "Alan Patrick", "Meio-campo", 32, 10, 7);
    cadastrar_jogador(&times[0], "Gabriel Mercado", "Zagueiro", 34, 9, 1);
    cadastrar_jogador(&times[0], "Thiago Maia", "Meio-campo", 27, 40, 2);
    cadastrar_jogador(&times[0], "Rafael Borre", "Atacante", 28, 19, 8);

    // Cadastro de jogadores para o time 2
    cadastrar_jogador(&times[1], "Braithwaite", "Atacante", 33, 13, 0);
    cadastrar_jogador(&times[1], "Arezo", "Atacante", 21, 9, 0); 
    cadastrar_jogador(&times[1], "Franco Cristaldo", "Meio-campo", 28, 30, 5); 
    cadastrar_jogador(&times[1], "Edenilson", "Meio-campo", 34, 26, 1); 
    cadastrar_jogador(&times[1], "Dodi", "Meio-campo", 28, 28, 0); 
    cadastrar_jogador(&times[1], "Mathias Villasanti", "Meio-campo", 27, 22, 0); 
    cadastrar_jogador(&times[1], "Jemerson", "Defensor", 32, 12, 0); 
    cadastrar_jogador(&times[1], "Rodrigo Ely", "Defensor", 31, 20, 1); 
    cadastrar_jogador(&times[1], "Joao Pedro", "Defensor", 28, 27, 0); 
    cadastrar_jogador(&times[1], "Marchesin", "Goleiro", 35, 0, 0); 


    printf("\nExibindo todos os times cadastrados:\n");
    exibir_todos_times(times, num_times);

    // Buscar time
    printf("\n===============================================================");
    printf("\nBuscando pelo time 'Internacional' ...\n");
    Time *time_internacional = buscar_time(times, num_times, "Internacional");
    
    // Buscar jogador
    printf("===============================================================");
    printf("\nBuscando jogador com numero 30 no Gremio...\n");
    Jogador *jogador = buscar_jogador(&times[1], 30);
    
    // Criando rodadas
    Rodada rodadas[MAX_RODADAS];
    int num_rodadas = 0;

    // Primeira rodada e registro de situações no jogo
    rodadas[num_rodadas].numero_rodada = 1;
    rodadas[num_rodadas].num_partidas = 0;
    cadastrar_partida(&rodadas[num_rodadas], &times[0], &times[1]);
    registrar_evento(&rodadas[num_rodadas].partidas[0], 10, "Gol do Internacional!"); // Registrar um evento para a primeira partida (gol aos 10 minutos)
    num_rodadas++;

    // Segunda rodada e registro de situações no jogo
    rodadas[num_rodadas].numero_rodada = 2;
    rodadas[num_rodadas].num_partidas = 0;
    cadastrar_partida(&rodadas[num_rodadas], &times[0], &times[1]);
    registrar_evento(&rodadas[num_rodadas].partidas[0], 10, "Gol do Internacional!"); // Registrar um evento para a primeira partida da segunda rodada (gol aos 10 minutos)
    registrar_evento(&rodadas[num_rodadas].partidas[0], 16, "Gol do Internacional!");
    registrar_evento(&rodadas[num_rodadas].partidas[0], 18, "Gol do Internacional!");
    num_rodadas++;

    // Exibir rodadas e eventos
    printf("\n\nExibindo rodadas e eventos:\n");
    exibir_todas_rodadas(rodadas, num_rodadas);

    
    gerar_relatorio_classificacao(times, num_times);

    gerar_relatorio_artilharia(times, num_times);

    gerar_relatorio_estatisticas(times, num_times);

    return 0;
}
