/*
Projeto: Jogo de Xadrez
3º Semestre de Ciências da Computação - UFSCar Sorocaba
Programação orientada a objetos
Profª Katti Faceli
Descrição:Definição da classe "jogador", utilizada para principalmente guardar e exibir as informações dos jogadores
*/
#ifndef jogador_h
#define jogador_h
#include <string>
#include "peca.h"

using namespace std;

class Jogador {
   private:
    string nome;
    const int cor;
    Peca* pecasAtivas[16];

   public:
    //Construtor recebe o nome do jogador e a sua cor como parâmetros
    Jogador(string _nome, int _cor);
    void printNome();
    Peca** getPecasAtivas();
};

#endif