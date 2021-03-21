/*
Projeto: Jogo de Xadrez
3º Semestre de Ciências da Computação - UFSCar Sorocaba
Programação orientada a objetos
Profª Katti Faceli
Integrantes: Giovanni Alvarenga, Fábio Yamaya, João Victor Vilar
Implementação da classe "peao"
Descrição:Implementa as funções da classe "peao" contidas no arquivo .h
*/
#include "peao.h"

//Construtor da classe
Peao::Peao(int _cor, char _tipo) : Peca(_cor, _tipo) {
    jaMoveu = false;
}

bool Peao::checaMovimento(int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino, bool haPeca) {
    //Calcula a diferença entre linha e coluna para obter o movimento
    int diferencaLinha = linhaDestino - linhaOrigem;
    int diferencaColuna = colunaDestino - colunaOrigem;
    //Verifica a movimentação do peão

    //Caso a posição de destino esteja vazia
    if (haPeca == 0) {
        //Caso o peao ja tenha se movido antes, não poderá mais executar o movimento de 2 casas
        if (jaMoveu) {
            if (cor == 1 && diferencaLinha == 1 && diferencaColuna == 0) {
                return true;
            } else if (cor == 0 && diferencaLinha == -1 && diferencaColuna == 0) {
                return true;
            }
        }
        //Caso o peão ainda não tenha se movido, poderá se mover 2 casas
        else {
            jaMoveu = true;
            if (cor == 1 && (diferencaLinha == 1 || diferencaLinha == 2) && diferencaColuna == 0) {
                return true;
            }
            if (cor == 0 && (diferencaLinha == -1 || diferencaLinha == -2) && diferencaColuna == 0) {
                return true;
            }
        }
        return false;
    }
    //Caso exista uma peça na posição de destino
    else {
        if (colunaOrigem == colunaDestino) {
            return false;
        }

        if (diferencaColuna == 1 || diferencaColuna == -1) {
            if (cor == 1 && diferencaLinha == 1) {
                jaMoveu = true;
                return true;
            } else if (cor == 0 && diferencaLinha == -1) {
                jaMoveu = true;
                return true;
            }
        }
        return false;
    }
}
//imprime na tela o caracter correspondente a peca
void Peao::desenha() {
    if (cor == 1) {
        cout << "p";
    } else {
        cout << "P";
    }
}