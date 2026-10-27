#include <iostream>


struct Robo {
 int linha;
 int coluna;
 int energia = 100;
 int vidas = 3;
 int pontos;
};

struct Estatistica {
 char nome[40];
 int partidasJogadas;
 int vitorias;
 int derrotas;
 int maiorPontuacao;
 int fasesConcluidas;
};

/*
void desenharCenario();
void desenharRobo(const Robo &robo);
void moverRobo(Robo &robo, int direcao);
void atualizarInimigos();
void verificarColisoes(Robo &robo);
void aplicarObstaculos(Robo &robo);
bool verificarFimDeJogo(const Robo &robo);
*/

int main(){
    Robo robo1;
    int mapa[30][30];
    return 0;
}

