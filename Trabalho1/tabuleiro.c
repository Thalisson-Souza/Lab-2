#include <stdio.h>
#include "peca.h"
#include <stdlib.h>
#include <string.h>

int jogadorAtual = 0; // PECA PRETA

bool posicaoValida(int x, int y){
    return (x >= 0 && x < 8 && y >= 0 && y < 8);
}

bool destinoCapturou(Peca* casaDestino, Peca* pecaMovendo) {
    return casaDestino == NULL || !pecaAliada(pecaMovendo, casaDestino);
}

bool pecaAliada(Peca* peca1, Peca* peca2) {
    return (peca1->cor == peca2->cor);
}

bool caminhoLinhaColunaLivre(Peca*** tabuleiro, int inicioX, int inicioY, int fimX, int fimY) { 
     // Verifica se o movimento é apenas na vertical ou horizontal
    if (inicioX != fimX && inicioY != fimY) {
        return false; 
    }
    // Determina a direção e o incremento para cada eixo
    int adicionaX = (fimX > inicioX) ? 1 : (fimX < inicioX ? -1 : 0);
    int adicionaY = (fimY > inicioY) ? 1 : (fimY < inicioY ? -1 : 0);

    // Itera sobre as casas entre a posição inicial e final
    for (int i = inicioX + adicionaX; i != fimX; i += adicionaX) {
        for (int j = inicioY + adicionaY; j != fimY; j += adicionaY) {
            if (tabuleiro[i][j] != NULL) {
                return false; // Há uma peça no caminho
            }
        }
    }
    return true;
}

bool caminhoDiagonalLivre(Peca*** tabuleiro, int inicioX, int inicioY, int fimX, int fimY){
    int casasAndadasX = (fimX > inicioX) ? 1 : -1;
    int casasAndadasY = (fimY > inicioY) ? 1 : -1;

    int x = inicioX + casasAndadasX;
    int y = inicioY + casasAndadasY;

    while (x != fimX && y != fimY) {
        if (tabuleiro[x][y] != NULL && tabuleiro[x][y]->tipo != ' ') { // Verifica se há uma peça na casa (se não for NULL e não for ' ')
            printf("Movimento invalido, existe uma peca no caminho!");
            return false;  
        }
        x += casasAndadasX;  // Move para a próxima casa na direção X
        y += casasAndadasY;
    }
    if (tabuleiro[fimX][fimY] != NULL && tabuleiro[fimX][fimY]->tipo != ' ') {  // Verifica se a casa de destino está ocupada por uma peça inimiga
        printf("\nMovimento invalido, a casa de destino contem uma peca inimiga!\n");
        return false;  
    }
    return true; 
}

void promoverPeao(Peca*** tabuleiro, int x, int y, Peca* peao) {
    char novaPeca;
    int pecaValida = 0;

    while (!pecaValida) { // Escolha de peça pela promoçao do Peão
        printf("Promoção! Escolha a nova peça:\n");
        printf("D - Dama\n");
        printf("T - Torre\n");
        printf("B - Bispo\n");
        printf("C - Cavalo\n");
        printf("Escolha: ");
        scanf(" %c", &novaPeca);

        switch (novaPeca) {
            case 'D': case 'd':
                novaPeca = 'D'; // Dama
                pecaValida = 1;
                break;
            case 'T': case 't':
                novaPeca = 'T'; // Torre
                pecaValida = 1;
                break;
            case 'B': case 'b':
                novaPeca = 'B'; // Bispo
                pecaValida = 1;
                break;
            case 'C': case 'c':
                novaPeca = 'C'; // Cavalo
                pecaValida = 1;
                break;
            default:
                printf("Entrada invalida! Tente novamente.\n");
                break;
        }
    }
    Peca* nova = malloc(sizeof(Peca)); // Escolha de peça pela promoçao do Peão
    nova->tipo = novaPeca; 
    nova->cor = peao->cor;  

    tabuleiro[x][y] = nova; // Substitui o peão
    free(peao);
}

int moverPeao(Peca*** tabuleiro, int inicioX, int inicioY, int fimX, int fimY) {
    Peca* peao = tabuleiro[inicioX][inicioY];
    int direcao = (peao->tipo == '@') ? -1 : 1; // Determinar a direção do movimento (peões '@' avançam para baixo, '*' avançam para cima)

    // Verificar numero de casas que o peão irá andar
    int casasAvancadas = fimX - inicioX;
    Peca* casaDestino = tabuleiro[fimX][fimY]; // Casa de destino
    Peca* casaIntermediaria = tabuleiro[inicioX + direcao][inicioY];

    // Verificar se o movimento é um avanço de uma casa
        bool movimentoSimples = (fimX == inicioX + direcao && fimY == inicioY);
    if (movimentoSimples) {
        if (casaDestino == NULL || casaDestino->tipo == ' ') { // Verificar se a casa de destino está vazia
            return true; 
        }
            printf("\nMovimento invalido! A casa de destino nao esta vazia.\n");
        }

    // Verificar se o movimento é um avanço de duas casas
        bool primeiroMovimento = (peao->tipo == '@' && inicioX == 6) || (peao->tipo == '*' && inicioX == 1);
    if (primeiroMovimento && casasAvancadas == 2 * direcao && fimY == inicioY) {
        if ((casaIntermediaria == NULL || casaIntermediaria->tipo == ' ') && (casaDestino == NULL || casaDestino->tipo == ' ')) {
            return true;
        }
    }

    // Verificar se é um movimento de captura (diagonal)
        bool movimentoCapturaDiagonal = (fimX == inicioX + direcao && (fimY == inicioY + 1 || fimY == inicioY - 1));
    if (movimentoCapturaDiagonal) {
        if ( (casaDestino != NULL && casaDestino->tipo != ' ') && ( !pecaAliada(peao, casaDestino) ) ) {
            return true; 
        }
        printf("\nMovimento invalido! Não ha peça inimiga para capturar.\n");
    }
    printf("\nMovimento invalido para o peao!\n");
    return false;
}

int moverCavalo(Peca*** tabuleiro, int inicioX, int inicioY, int fimX, int fimY) {
    // Verificar se a posição de destino está dentro dos limites do tabuleiro
    if (!posicaoValida(fimX, fimY)) {
        printf("\nMovimento invalido! A posicao de destino esta fora do tabuleiro.\n");
        return false;
    }

    int casasAndadasX = fimX - inicioX;
    int casasAndadasY = fimY - inicioY;
    if ( ( (casasAndadasX == 2 || casasAndadasX == -2) && (casasAndadasY == 1 || casasAndadasY == -1) ) ||  // Valida as casas para fazer o movimento em L
         ( (casasAndadasX == 1 || casasAndadasX == -1) && (casasAndadasY == 2 || casasAndadasY == -2) ) ) {
            
        Peca* pecaMovendo = tabuleiro[inicioX][inicioY];
        Peca* pecaDestino = tabuleiro[fimX][fimY];

        // Verifica se a casa de destino está vazia ou pode capturar
        if (destinoCapturou(pecaDestino, pecaMovendo)) {
            return true; 
        } else {
            printf("\nMovimento invalido! A casa de destino esta ocupada por uma peca aliada.\n");
        }
    } else {
        printf("\nO cavalo nao pode ir para essa posicao, tente novamente!\n");
    }
    return false;
}

int moverBispo(Peca*** tabuleiro, int inicioX, int inicioY, int fimX, int fimY) {
    int casasAndadasX = fimX - inicioX;
    int casasAndadasY = fimY - inicioY;

    if (casasAndadasX == casasAndadasY || casasAndadasX == -casasAndadasY){     // Valida as casas entre as colunas e as linhas para verificar a diagonal
        Peca* pecaMovendo = tabuleiro[inicioX][inicioY];
        Peca* pecaDestino = tabuleiro[fimX][fimY];
        if(destinoCapturou(pecaDestino, pecaMovendo)){
            return caminhoDiagonalLivre(tabuleiro,inicioX, inicioY, fimX, fimY);
        }
    }
    return false; 
}

int moverTorre(Peca*** tabuleiro, int inicioX, int inicioY, int fimX, int fimY){
    Peca* pecaMovendo = tabuleiro [inicioX][inicioY];
    Peca* pecaDestino = tabuleiro [fimX][fimY];

    if(caminhoLinhaColunaLivre(tabuleiro, inicioX, inicioY, fimX, fimY)){
        if(destinoCapturou(pecaDestino, pecaMovendo)){
            return true;
        }
    }
    return false;
}

int moverDama(Peca*** tabuleiro, int inicioX, int inicioY, int fimX, int fimY){ 
    Peca* pecaMovendo = tabuleiro[inicioX][inicioY];
    Peca* pecaDestino = tabuleiro[fimX][fimY];
    
    if(caminhoLinhaColunaLivre(tabuleiro, inicioX, inicioY, fimX, fimY) || caminhoDiagonalLivre(tabuleiro,inicioX, inicioY, fimX, fimY)){
        if (destinoCapturou(pecaDestino, pecaMovendo)) {
            return true;
        }
    }
    return false;
}

int moverRei(Peca*** tabuleiro, int inicioX, int inicioY, int fimX, int fimY){  
    Peca* pecaMovendo = tabuleiro[inicioX][inicioY];
    Peca* pecaDestino = tabuleiro[fimX][fimY];

    if(caminhoLinhaColunaLivre(tabuleiro, inicioX, inicioY, fimX, fimY)){
        if (destinoCapturou(pecaDestino, pecaMovendo)) {
            return true;
        }
    }
    return false;
}

void localizarRei(Peca*** tabuleiro, char rei, int* posReiX, int* posReiY){
    *posReiX = -1;
    *posReiY = -1;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (tabuleiro[i][j] != NULL && tabuleiro[i][j]->tipo == rei) {
                *posReiX = i;
                *posReiY = j;
                return;
            }
        }
    }
}

int emXeque(Peca*** tabuleiro, char rei, char peaoInimigo, char torreInimiga, char cavaloInimigo, char bispoInimigo, char rainhaInimiga){
    int posReiX, posReiY;

    localizarRei(tabuleiro, rei, &posReiX, &posReiY);
    if (posReiX == -1 || posReiY == -1) {
        return false; // Rei não encontrado
    }

    // Verifica ataque de peão inimigo
    int direcaoPeao = (peaoInimigo == '@') ? 1 : -1; // Define a direção do peão
    if (posicaoValida(posReiX + direcaoPeao, posReiY - 1) &&
        tabuleiro[posReiX + direcaoPeao][posReiY - 1] != NULL &&
        (tabuleiro[posReiX + direcaoPeao][posReiY - 1]->tipo == '@' || tabuleiro[posReiX + direcaoPeao][posReiY - 1]->tipo == '*') && // Verifica se é um peão
        tabuleiro[posReiX + direcaoPeao][posReiY - 1]->cor != tabuleiro[posReiX][posReiY]->cor) {
    return true;
    }

    if (posicaoValida(posReiX + direcaoPeao, posReiY + 1) &&
        tabuleiro[posReiX + direcaoPeao][posReiY + 1] != NULL &&
        (tabuleiro[posReiX + direcaoPeao][posReiY + 1]->tipo == '@' || tabuleiro[posReiX + direcaoPeao][posReiY + 1]->tipo == '*') && // Verifica se é um peão
        tabuleiro[posReiX + direcaoPeao][posReiY + 1]->cor != tabuleiro[posReiX][posReiY]->cor) {
    return true;
}

    // Verifica ataque de cavalo inimigo
    int movimentosCavalo[8][2] = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};
    for (int k = 0; k < 8; k++) {
        int novoX = posReiX + movimentosCavalo[k][0];
        int novoY = posReiY + movimentosCavalo[k][1];
        if (posicaoValida(novoX, novoY) &&
            tabuleiro[novoX][novoY] != NULL &&
            tabuleiro[novoX][novoY]->tipo == cavaloInimigo &&
            tabuleiro[novoX][novoY]->cor != tabuleiro[posReiX][posReiY]->cor) {
            return true;
        }
    }

    // Verifica ataque de torre ou rainha inimiga nas linhas e colunas
    for (int i = posReiX + 1; i < 8; i++) {
        if (tabuleiro[i][posReiY] != NULL &&
            (tabuleiro[i][posReiY]->tipo == torreInimiga || tabuleiro[i][posReiY]->tipo == rainhaInimiga) &&
            tabuleiro[i][posReiY]->cor != tabuleiro[posReiX][posReiY]->cor) {
            return true;
        }
        if (tabuleiro[i][posReiY] != NULL) break; // Bloqueado por outra peça
    }

    for (int i = posReiX - 1; i >= 0; i--) {
        if (tabuleiro[i][posReiY] != NULL &&
            (tabuleiro[i][posReiY]->tipo == torreInimiga || tabuleiro[i][posReiY]->tipo == rainhaInimiga) &&
            tabuleiro[i][posReiY]->cor != tabuleiro[posReiX][posReiY]->cor) {
            return true;
        }
        if (tabuleiro[i][posReiY] != NULL) break; // Bloqueado por outra peça
    }

    for (int j = posReiY + 1; j < 8; j++) {
        if (tabuleiro[posReiX][j] != NULL &&
            (tabuleiro[posReiX][j]->tipo == torreInimiga || tabuleiro[posReiX][j]->tipo == rainhaInimiga) &&
            tabuleiro[posReiX][j]->cor != tabuleiro[posReiX][posReiY]->cor) {
            return true;
        }
        if (tabuleiro[posReiX][j] != NULL) break; // Bloqueado por outra peça
    }

    for (int j = posReiY - 1; j >= 0; j--) {
        if (tabuleiro[posReiX][j] != NULL &&
            (tabuleiro[posReiX][j]->tipo == torreInimiga || tabuleiro[posReiX][j]->tipo == rainhaInimiga) &&
            tabuleiro[posReiX][j]->cor != tabuleiro[posReiX][posReiY]->cor) {
            return true;
        }
        if (tabuleiro[posReiX][j] != NULL) break; // Bloqueado por outra peça
    }

    // Verifica ataque de bispo ou rainha inimiga nas diagonais
    for (int i = 1; posicaoValida(posReiX + i, posReiY + i); i++) {
        if (tabuleiro[posReiX + i][posReiY + i] != NULL &&
            (tabuleiro[posReiX + i][posReiY + i]->tipo == bispoInimigo || tabuleiro[posReiX + i][posReiY + i]->tipo == rainhaInimiga) &&
            tabuleiro[posReiX + i][posReiY + i]->cor != tabuleiro[posReiX][posReiY]->cor) {
            return true;
        }
        if (tabuleiro[posReiX + i][posReiY + i] != NULL) break; // Bloqueado por outra peça
    }

    for (int i = 1; posicaoValida(posReiX - i, posReiY - i); i++) {
        if (tabuleiro[posReiX - i][posReiY - i] != NULL &&
            (tabuleiro[posReiX - i][posReiY - i]->tipo == bispoInimigo || tabuleiro[posReiX - i][posReiY - i]->tipo == rainhaInimiga) &&
            tabuleiro[posReiX - i][posReiY - i]->cor != tabuleiro[posReiX][posReiY]->cor) {
            return true;
        }
        if (tabuleiro[posReiX - i][posReiY - i] != NULL) break; // Bloqueado por outra peça
    }

    for (int i = 1; posicaoValida(posReiX + i, posReiY - i); i++) {
        if (tabuleiro[posReiX + i][posReiY - i] != NULL &&
            (tabuleiro[posReiX + i][posReiY - i]->tipo == bispoInimigo || tabuleiro[posReiX + i][posReiY - i]->tipo == rainhaInimiga) &&
            tabuleiro[posReiX + i][posReiY - i]->cor != tabuleiro[posReiX][posReiY]->cor) {
            return true;
        }
        if (tabuleiro[posReiX + i][posReiY - i] != NULL) break; // Bloqueado por outra peça
    }

    for (int i = 1; posicaoValida(posReiX - i, posReiY + i); i++) {
        if (tabuleiro[posReiX - i][posReiY + i] != NULL &&
            (tabuleiro[posReiX - i][posReiY + i]->tipo == bispoInimigo || tabuleiro[posReiX - i][posReiY + i]->tipo == rainhaInimiga) &&
            tabuleiro[posReiX - i][posReiY + i]->cor != tabuleiro[posReiX][posReiY]->cor) {
            return true;
        }
        if (tabuleiro[posReiX - i][posReiY + i] != NULL) break; // Bloqueado por outra peça
    }
    return false; // Rei não está em xeque
}

int verificaXequeMate(Peca*** tabuleiro, char rei, char peaoInimigo, char torreInimiga, char cavaloInimigo, char bispoInimigo, char rainhaInimiga) {
    int posReiX, posReiY;
    
    // Verifica se o rei está em xeque
    if (!emXeque(tabuleiro, rei, peaoInimigo, torreInimiga, cavaloInimigo, bispoInimigo, rainhaInimiga)) {
        return false; // Se não está em xeque, não é xeque-mate
    }

    localizarRei(tabuleiro, rei, &posReiX, &posReiY);
    if (posReiX == -1 || posReiY == -1) {
        return false; // Rei não encontrado
    }

    // Verifica todas as possíveis jogadas para remover o cheque
    int direcoes[8][2] = {
        {1, 0}, {0, 1}, {-1, 0}, {0, -1},  // Cima, Direita, Baixo, Esquerda
        {1, 1}, {1, -1}, {-1, 1}, {-1, -1} // Diagonais
    };

    for (int d = 0; d < 8; d++) {
        int novoX = posReiX + direcoes[d][0];
        int novoY = posReiY + direcoes[d][1];

        if (posicaoValida(novoX, novoY)) { // Simula o movimento do rei para uma nova posição
            Peca* pecaDestino = tabuleiro[novoX][novoY];
            if (pecaDestino == NULL || !pecaAliada(tabuleiro[posReiX][posReiY], pecaDestino)) {
                Peca* temp = tabuleiro[novoX][novoY];  
                tabuleiro[novoX][novoY] = tabuleiro[posReiX][posReiY]; // Move o rei
                tabuleiro[posReiX][posReiY] = NULL;

                // Verifica se o rei ainda estaria em xeque após o movimento
                if (!emXeque(tabuleiro, rei, peaoInimigo, torreInimiga, cavaloInimigo, bispoInimigo, rainhaInimiga)) {
                    tabuleiro[posReiX][posReiY] = tabuleiro[novoX][novoY];
                    tabuleiro[novoX][novoY] = temp;
                    return false; // Não é xeque-mate, o rei pode escapar
                }
                tabuleiro[posReiX][posReiY] = tabuleiro[novoX][novoY];  // Desfaz o movimento
                tabuleiro[novoX][novoY] = temp;
            }
        }
    }
    return true;
}

void avisoXeque(Peca*** tabuleiro, int jogadorAtual) {  
    if (jogadorAtual == 1) { 
        if (emXeque(tabuleiro, 'R', '@', 't', 'c', 'b', 'd')) {
            printf("----------------------------------------------------");
            printf("\nAviso: O Rei branco esta em cheque!\n");

            if(verificaXequeMate(tabuleiro, 'R', '*', 't', 'c', 'b', 'd')){
                printf("----------------------------------------------------");
                printf("\nXeque-Mate! O jogador das pretas venceu.\n");
                exit(1);
            }
        }
    } else { 
        if(emXeque(tabuleiro, 'r', '*', 'T', 'C', 'B', 'D')){
            printf("----------------------------------------------------");
            printf("\nAviso: O Rei preto esta em cheque!\n");

            if(verificaXequeMate(tabuleiro, 'r', '*', 'T', 'C', 'B', 'D')){
                printf("----------------------------------------------------");
                printf("\nXeque-Mate! O jogador das brancas venceu.\n");
                exit(1);
            }
        }
    }
}

void moverPecaNoTabuleiro(Peca*** tabuleiro, int inicioX, int inicioY, int fimX, int fimY, Peca* pecaMovida) {
    if (tabuleiro[fimX][fimY] != NULL) { // Remover a peça capturada
        free(tabuleiro[fimX][fimY]);
    }
    tabuleiro[fimX][fimY] = pecaMovida;  // Mover a peça para a nova posição
    tabuleiro[inicioX][inicioY] = NULL;  // Esvazia posição antiga
}

void alterarJogador(int *jogadorAtual) {
    if (*jogadorAtual == 0) {
        *jogadorAtual = 1; // Troca para BRANCO
    } else {
        *jogadorAtual = 0; // Troca para PRETO
    }
}

bool insuficienciaMaterial(Peca*** tabuleiro) {
    int brancos = 0, pretos = 0;
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            Peca* peca = tabuleiro[x][y];
            if (peca != NULL) {
                if (peca->cor == 'B') brancos++;
                else if (peca->cor == 'P') pretos++;
            }
        }
    }
    // verificar insuficiência de material
    if ((brancos == 1 && pretos == 1) || // Ambos têm apenas o rei
        (brancos == 1 && pretos == 2) || // Branco: rei e bispo ou cavalo
        (brancos == 2 && pretos == 1)) { // Preto: rei e bispo ou cavalo
        return true;
    }
    return false;
}

void moverPeca(Peca*** tabuleiro, int inicioX, int inicioY, int fimX, int fimY) {
    Peca* pecaMovida = tabuleiro[inicioX][inicioY];
    
    if (pecaMovida == NULL || pecaMovida->tipo == ' ') {    // Verificar se existe uma peça na posição inicial
        printf("\nNao ha peca nessa posicao para mover!");
        return;
    }
    // Verificar qual peça está sendo movida e chamar a função de mover
    int movimentoValido = 0;
    switch (pecaMovida->tipo) {
        case '*': case'@': // Peão
            movimentoValido = moverPeao(tabuleiro, inicioX, inicioY, fimX, fimY);
            break;
        case 'C': case 'c': // Cavalo
            movimentoValido = moverCavalo(tabuleiro, inicioX, inicioY, fimX, fimY);
            break;
        case 'B': case 'b': // Bispo
            movimentoValido = moverBispo(tabuleiro, inicioX, inicioY, fimX, fimY);
            break;
        case 'T': case 't': // Torre
            movimentoValido = moverTorre(tabuleiro, inicioX, inicioY, fimX, fimY);
            break;
        case 'D': case 'd': // Dama
            movimentoValido = moverDama(tabuleiro, inicioX, inicioY, fimX, fimY);
            break;
        case 'R': case 'r': // Rei
            movimentoValido = moverRei(tabuleiro, inicioX, inicioY, fimX, fimY);
            break;
        default:
            printf("Peca desconhecida!");
            return;
    }
    
    if (movimentoValido) {     // Se o movimento for válido, atualizar o tabuleiro
        moverPecaNoTabuleiro(tabuleiro, inicioX, inicioY, fimX, fimY, pecaMovida);

        if ((pecaMovida->tipo == '*' && fimX == 0) || (pecaMovida->tipo == '@' && fimX == 7)) { // Verificar se o peão chegou ao final para promover
            promoverPeao(tabuleiro, fimX, fimY, pecaMovida); // Promover Peão
        } else { 
            alterarJogador(&jogadorAtual);
        }

        if (insuficienciaMaterial(tabuleiro)) {
            printf("Empate por Insuficiência de Material!\n");
            exit(1);
        }
        avisoXeque(tabuleiro, jogadorAtual);
        desenhar_tabuleiro(tabuleiro);
    }else{
        printf("\nMovimento nao foi validado!\n");
        printf("----------------------------------------------------");
    }
}

void converterCoordenadas(char *entrada, int *linha, int *coluna) {
    char colunaChar = entrada[0]; 
    int linhaNum = entrada[1] - '0'; 

    // Calcular o índice da coluna
    if(colunaChar >= 'A' && colunaChar <= 'H'){
        *coluna = colunaChar - 'A'; // 'A' -> 0, 'B' -> 1, ..., 'H' -> 7
    } else if(colunaChar >= 'a' && colunaChar <= 'h') {
        *coluna = colunaChar - 'a'; 
    }
    *linha = 8 - linhaNum;  // Calcular o índice da linha
}

void movimentoUsuario(Peca*** tabuleiro, int jogdadorAtual){
    char entradaInicio[3], entradaFim[3];
    int inicioX, inicioY, fimX, fimY;

    // Entrada Usuário
    printf("\nDigite '0' e pressione Enter para encerrar o jogo/desistir.\n");

    if (jogadorAtual == 0){
        printf("\n\n--- Jogador das pecas PRETAS, sua vez! ---\n\n");
    } else{
        printf("\n\n--- Jogador das pecas BRANCAS, sua vez! ---\n\n");
    }
    
    // Entrada Usuário
    printf("\nInsira a peca que sera movimentada (ex: e2): ");
    scanf("%s", entradaInicio);

    if (strcmp(entradaInicio, "0") == 0) { // Encerra a função e o jogo se for digitado 0
        exit(1); 
    }

    printf("\nInsira para onde a peca sera movimentada (ex: e4): ");
    scanf("%s", entradaFim);

    // Converte as coordenadas
    converterCoordenadas(entradaInicio, &inicioX, &inicioY);
    converterCoordenadas(entradaFim, &fimX, &fimY);

    // Verifica qual peça foi selecionada e se pertence ao Jogador atual
    Peca* pecaSelecionada = tabuleiro[inicioX][inicioY];
    if(pecaSelecionada == NULL || pecaSelecionada->tipo == ' '){
        printf("----------------------------------------------------");
        printf("\nA posicao selecionada esta vazia. Tente novamente!\n");
        return;
    }
    if((jogadorAtual == 1 && pecaSelecionada->cor == 'P') || (jogadorAtual == 0 && pecaSelecionada->cor == 'B')){
        printf("\n--- Voce nao pode mover a peca do adversario! ---\n\n");
        printf("----------------------------------------------------");
        return;
    }
    moverPeca(tabuleiro, inicioX, inicioY, fimX, fimY); // Chama a função moverPeca
}
