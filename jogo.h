/*
Projeto: Jogo de Xadrez
3º Semestre de Ciências da Computação - UFSCar Sorocaba
Programação orientada a objetos
Profª Katti Faceli
Descrição:Definição da classe "jogo", chamada ao iniciar o programa para criar os principais objetos necessários e receber os nomes dos jogadores
*/
#ifndef jogo_h
#define jogo_h
#include <iostream>
#include <string>
#include "jogador.h"
#include "peca.h"
#include "tabuleiro.h"

class Jogo {
   private:
    Tabuleiro* tabuleiro1;
    Jogador* jogador1;
    Jogador* jogador2;
    Peca* pecasBrancas[16];
    Peca* pecasPretas[16];

    int turnoJogador;

   public:
    //Construtor
    Jogo();
    //Destrutor
    ~Jogo();

    //Metodos usados na execução do jogo
    //Especificados no .cpp
    void turnos();
    bool movimenta(int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino);
    bool movimentoValido(int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino);
    bool estaEmXeque(int cor);
    void achaRei(int cor, int posicaoRei[]);
    bool verificaXeque(int iRei, int jRei, int cor);
    bool estaEmXequeMate(int cor);
};

#endif