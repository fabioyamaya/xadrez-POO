/*
Projeto: Jogo de Xadrez
3º Semestre de Ciências da Computação - UFSCar Sorocaba
Programação orientada a objetos
Profª Katti Faceli
Integrantes: Giovanni Alvarenga, Fábio Yamaya, João Victor Vilar
Implementação da classe "bispo"
Descrição:Implementa as funções da classe "bispo" contidas no arquivo .h
*/
#include "bispo.h"

//Construtor da classe
Bispo::Bispo(int _cor, char _tipo) : Peca(_cor, _tipo) {}

//Verifica se o movimento da peça está correto
bool Bispo::checaMovimento(int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino) {
    //Calcula a diferença entre linha e coluna para obter o movimento
    int diferencaLinha = linhaDestino - linhaOrigem;
    int diferencaColuna = colunaDestino - colunaOrigem;
    //Verifica se o movimento eh na diagonal
    if (diferencaColuna == diferencaLinha || diferencaColuna == -diferencaLinha) {
        return true;
    }
    return false;
}

//imprime na tela o caracter correspondente a peca
void Bispo::desenha() {
    if (cor == 1) {
        cout << "b";
    } else {
        cout << "B";
    }
}
