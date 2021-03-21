/*
Projeto: Jogo de Xadrez
3º Semestre de Ciências da Computação - UFSCar Sorocaba
Programação orientada a objetos
Profª Katti Faceli
Descrição:Definição da classe "rainha"
*/
#ifndef rainha_h
#define rainha_h
#include <iostream>
#include "peca.h"

using namespace std;

class Rainha : public Peca {
   public:
    //Construtor
    Rainha(int _cor, char _tipo);
    bool checaMovimento(int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino);
    void desenha();
};

#endif