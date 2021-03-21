/*
Projeto: Jogo de Xadrez
3º Semestre de Ciências da Computação - UFSCar Sorocaba
Programação orientada a objetos
Profª Katti Faceli
Integrantes: Giovanni Alvarenga, Fábio Yamaya, João Victor Vilar
Implementação da classe "cavalo"
Descrição:Implementa as funções da classe "cavalo" contidas no arquivo .h
*/
#include "cavalo.h"
#include <stdlib.h>

//Construtor da classe
Cavalo::Cavalo(int _cor, char _tipo) : Peca(_cor, _tipo) {}

bool Cavalo::checaMovimento(int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino) {
    //Calcula a diferença entre linha e coluna para obter o movimento
    int diferencaLinha = linhaDestino - linhaOrigem;
    int diferencaColuna = colunaDestino - colunaOrigem;

    diferencaLinha = abs(diferencaLinha);
    diferencaColuna = abs(diferencaColuna);

    //Verifica se o movimento esta de acordo com as regras
    if (diferencaColuna == 2 && diferencaLinha == 1) {
        return true;
    }
    if (diferencaColuna == 1 && diferencaLinha == 2) {
        return true;
    }
    return false;
}

//imprime na tela o caracter correspondente a peca
void Cavalo::desenha() {
    if (cor == 1) {
        cout << "c";
    } else {
        cout << "C";
    }
}
