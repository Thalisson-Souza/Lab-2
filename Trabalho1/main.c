#include <stdio.h>
#include "tabuleiro.h"
#include "peca.h"


int corATUAL = 0;

int main(){
    // Cria o tabuleiro e inicializa
    Peca*** tabuleiro = criar_tabuleiro();
    if (tabuleiro == NULL) {
        fprintf(stderr, "Falha ao alocar memória para o tabuleiro.\n");
        return 1;
    }
    desenhar_tabuleiro(tabuleiro);
    while(true){
    movimentoUsuario(tabuleiro, corATUAL);
    }

    destruir_tabuleiro(tabuleiro);
    return 0;
}