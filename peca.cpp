/*
Projeto: Jogo de Xadrez
3º Semestre de Ciências da Computação - UFSCar Sorocaba
Programação orientada a objetos
Profª Katti Faceli
Integrantes: Giovanni Alvarenga, Fábio Yamaya, João Victor Vilar
Implementação da classe "peca"
Descrição:Implementa as funções da classe "peca" contidas no arquivo .h
*/
#include "peca.h"

using namespace std;

//Construtor da classe
Peca::Peca(int _cor, char _tipo) : cor(_cor), tipo(_tipo) {
}

//Metodos get para acessar atributos
int Peca::getCor() {
    return cor;
}

char Peca::getTipo() {
    return tipo;
}

//Metodos comuns à todas as peças, implementação foi feita em cada peça específica
void Peca::desenha() {
}

bool Peca::checaMovimento(int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino) {
}

bool Peca::checaMovimento(int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino, bool haPeca) {
}