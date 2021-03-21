/*
Projeto: Jogo de Xadrez
3º Semestre de Ciências da Computação - UFSCar Sorocaba
Programação orientada a objetos
Profª Katti Faceli
Integrantes: Giovanni Alvarenga, Fábio Yamaya, João Victor Vilar
Implementação da classe "rainha"
Descrição:Implementa as funções da classe "rainha" contidas no arquivo .h
*/
#include "rainha.h"

//Construtor da classe
Rainha::Rainha(int _cor, char _tipo) : Peca(_cor, _tipo) {}

bool Rainha::checaMovimento(int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino) {
    //Calcula a diferença entre linha e coluna para obter o movimento
    int diferencaLinha = linhaDestino - linhaOrigem;
    int diferencaColuna = colunaDestino - colunaOrigem;

    //Verifica a movimentação de acordo com a peça
    if (diferencaColuna == 0) {
        return true;
    } else if (diferencaLinha == 0) {
        return true;
    } else if (diferencaColuna == diferencaLinha || diferencaColuna == -diferencaLinha) {
        return true;
    }
    return false;
}

//imprime na tela o caracter correspondente a peca
void Rainha::desenha() {
    if (cor == 1) {
        cout << "q";
    } else {
        cout << "Q";
    }
}
