/*
Projeto: Jogo de Xadrez
3º Semestre de Ciências da Computação - UFSCar Sorocaba
Programação orientada a objetos
Profª Katti Faceli
Descrição:Definição da classe "posicao" que mantém as informações referente a todas as possíveis posições do tabuleiro
*/
#ifndef posicao_h
#define posicao_h
#include "bispo.h"
#include "cavalo.h"
#include "peao.h"
#include "peca.h"
#include "rainha.h"
#include "rei.h"
#include "torre.h"

using namespace std;

class Posicao {
   private:
    const int cor;
    char linha;
    int coluna;
    Peca* peca;

   public:
    //Construtor para cada posição do jogo, com sua cor, linha e coluna
    Posicao(char _linha, int _coluna, int _cor);
    //Altera peça
    void setPeca(Peca* p);
    Peca* getPeca();
    int getCor();
    //Verifica se está ocupado
    bool estaOcupado();
};

#endif