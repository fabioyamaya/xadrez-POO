/*
Projeto: Jogo de Xadrez
3º Semestre de Ciências da Computação - UFSCar Sorocaba
Programação orientada a objetos
Profª Katti Faceli
Integrantes: Giovanni Alvarenga, Fábio Yamaya, João Victor Vilar
Implementação da classe "rei"
Descrição:Implementa as funções da classe "rei" contidas no arquivo .h
*/
#include "rei.h"

//Construtor da classe
Rei::Rei(int _cor, char _tipo) : Peca(_cor, _tipo) {}

bool Rei::checaMovimento(int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino) {
    //Calcula a diferença entre linha e coluna para obter o movimento
    int diferencaLinha = linhaDestino - linhaOrigem;
    int diferencaColuna = colunaDestino - colunaOrigem;

    //Verifica a movimentação de acordo com a peça
    if (diferencaColuna >= -1 && diferencaColuna <= 1) {
        if (diferencaLinha >= -1 && diferencaLinha <= 1) {
            return true;
        }
    }
    return false;
}

//imprime na tela o caracter correspondente a peca
void Rei::desenha() {
    if (cor == 1) {
        cout << "k";
    } else {
        cout << "K";
    }
}
