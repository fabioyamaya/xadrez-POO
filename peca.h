/*
Projeto: Jogo de Xadrez
3º Semestre de Ciências da Computação - UFSCar Sorocaba
Programação orientada a objetos
Profª Katti Faceli
Descrição:Definição da classe "peca" que irá conter as informações não específicas de peça, como sua posição e se está presente
*/
#ifndef peca_h
#define peca_h
#include <iostream>

using namespace std;

class Peca {
   protected:
    const int cor;
    char tipo;

   public:
    Peca(int _cor, char _tipo);
    char getTipo();
    int getCor();
    virtual void desenha();
    //Metodo que verifica se o movimento da peca é valido
    virtual bool checaMovimento(int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino);
    //Metodo que verifica se o movimento do Peao é valido
    virtual bool checaMovimento(int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino, bool haPeca);
};
#endif