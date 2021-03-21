/*
Projeto: Jogo de Xadrez
3º Semestre de Ciências da Computação - UFSCar Sorocaba
Programação orientada a objetos
Profª Katti Faceli
Integrantes: Giovanni Alvarenga, Fábio Yamaya, João Victor Vilar
Implementação da classe "Tabuleiro"
Descrição:Implementa as funções da classe "Tabuleiro" contidas no arquivo .h
*/
#include "tabuleiro.h"

//Construtor da classe
Tabuleiro::Tabuleiro() {
    int flag = 1;
    //Cria o tabuleiro alternando as cores com uma matriz 8x8
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            //Usa a flag para saber quando é necessário alterar a cor
            if (flag == 1) {
                posicoes[i][j] = new Posicao(i, j, 0);
                flag = 0;
            } else {
                posicoes[i][j] = new Posicao(i, j, 1);
                flag = 1;
            }
        }
        if (flag == 1) {
            flag = 0;
        } else {
            flag = 1;
        }
    }
}

//Coloca o endereço da peca na posicao passada
void Tabuleiro::setPeca(Peca* peca, int i, int j) {
    posicoes[i][j]->setPeca(peca);
}

//Função que desenha o tabuleiro no terminal
void Tabuleiro::desenhar() {
    cout << "  ";  // espaço para compensar o espaço usado para imprimir as linhas
    //imprime o número das colunas
    for (size_t i = 1; i <= 8; i++) {
        cout << "   " << i << "  ";
    }
    cout << endl;
    //Imprime as letras que indicam as linhas
    for (size_t i = 97; i < 105; i++) {
        for (size_t t = 0; t < 3; t++) {
            if (t == 1) {
                cout << (char)i << " ";
            } else {
                cout << "  ";
            }
            for (size_t j = 1; j <= 8; j++) {
                //Verifica se a posição está ocupada
                if (posicoes[i - 97][j - 1]->Posicao::estaOcupado() && t == 1) {
                    //Recebe a peça caso a posição esteja ocupada
                    Peca* temp = posicoes[i - 97][j - 1]->Posicao::getPeca();
                    //Imprime as casas e as peças, alterando a cor de fundo
                    if (posicoes[i - 97][j - 1]->Posicao::getCor()) {
                        cout << "\e[22;45m"
                             << "   ";
                        temp->desenha();
                        cout << "  "
                             << "\033[0m";
                    } else {
                        cout << "   ";
                        temp->desenha();
                        cout << "  ";
                    }
                } else {
                    if (posicoes[i - 97][j - 1]->Posicao::getCor()) {
                        cout << "\e[22;45m"
                             << "      "
                             << "\033[0m";
                    } else {
                        cout << "      ";
                    }
                }
            }
            cout << endl;
        }
    }
    cout << endl
         << endl
         << endl;
}

//Verifica se o movimento esta dentro dos limites do tabuleiro
bool Tabuleiro::estaDentro(int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino) {
    Peca* origem = posicoes[linhaOrigem][colunaOrigem]->getPeca();
    if (origem == NULL) {
        return false;
    }
    if (colunaOrigem >= 0 && colunaDestino >= 0 && colunaOrigem <= 7 && colunaDestino <= 7) {
        if (linhaOrigem >= 0 && linhaDestino >= 0 && linhaOrigem <= 7 && linhaDestino <= 7) {
            if ((linhaOrigem != linhaDestino) || (colunaOrigem != colunaDestino)) {
                //Verifica se haverá conflito de pecase certifica de que o conflito ocorra entre
                //pecas de cor diferente
                if (posicoes[linhaDestino][colunaDestino]->estaOcupado()) {
                    Peca* destino = posicoes[linhaDestino][colunaDestino]->getPeca();
                    if (destino->getCor() != origem->getCor()) {
                        return true;
                    }
                } else {
                    return true;
                }
            }
        }
    }
    return false;
}

//Verifica se o caminho entre a posição de origem e a posição destino está livre
bool Tabuleiro::caminhoLivre(int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino) {
    Peca* peca = posicoes[linhaOrigem][colunaOrigem]->getPeca();
    char tipo = peca->getTipo();

    //Caso a peça seja um cavalo, nao é necessario verificar
    //pois o cavalo pode saltar sobre outras pecas
    if (tipo == 'c' || tipo == 'C') {
        return true;
    }

    int cor = peca->getCor();

    //Caso movimento ocorra na mesma linha
    if (linhaOrigem == linhaDestino) {
        //Caso o movimento esteja ocorrendo da esquerda para a direita
        if (colunaDestino > colunaOrigem) {
            for (size_t i = colunaOrigem + 1; i < colunaDestino; i++) {
                if (posicoes[linhaOrigem][i]->estaOcupado()) {
                    return false;
                }
            }
            return true;
        }
        //Caso o movimento esteja ocorrendo da direita para a esquerda
        else {
            for (size_t i = colunaOrigem - 1; i > colunaDestino; i--) {
                if (posicoes[linhaOrigem][i]->estaOcupado()) {
                    return false;
                }
            }
            return true;
        }
    }

    //Caso o movimento ocorra de cima para baixo
    if (linhaDestino > linhaOrigem) {
        //Caso o movimento ocorra na mesma coluna
        if (colunaOrigem == colunaDestino) {
            for (size_t i = linhaOrigem + 1; i < linhaDestino; i++) {
                if (posicoes[i][colunaOrigem]->estaOcupado()) {
                    return false;
                }
            }
            return true;
        }
        //Caso o movimento ocorra na diagonal de cima para baixo
        // da esquerda para a direita
        else {
            if (colunaDestino > colunaOrigem) {
                for (size_t i = linhaOrigem + 1, j = colunaOrigem + 1; i < linhaDestino; i++, j++) {
                    if (posicoes[i][j]->estaOcupado()) {
                        //cout << "caminho obstruido" << endl;
                        return false;
                    }
                }
                return true;
            }
            //Caso ocorra na diagonal de cima para baixo
            // da direita para a esquerda
            else {
                for (size_t i = linhaOrigem + 1, j = colunaOrigem - 1; i < linhaDestino; i++, j--) {
                    if (posicoes[i][j]->estaOcupado()) {
                        //cout << "caminho obstruido" << endl;
                        return false;
                    }
                }
                return true;
            }
        }
    }
    //Caso o movimento ocorra de baixo para cima
    else {
        //Caso o movimento se mantenha na mesma coluna
        if (colunaOrigem == colunaDestino) {
            for (size_t i = linhaOrigem - 1; i > linhaDestino; i--) {
                if (posicoes[i][colunaOrigem]->estaOcupado()) {
                    return false;
                }
            }
            return true;
        } else {
            //Movimento na diagonal de baixo para cima
            // da esquerda para a direita
            if (colunaDestino > colunaOrigem) {
                for (size_t i = linhaOrigem - 1, j = colunaOrigem + 1; i > linhaDestino; i--, j++) {
                    if (posicoes[i][j]->estaOcupado()) {
                        //cout << "caminho obstruido" << endl;
                        return false;
                    }
                }
                return true;
            }
            //Movimento na diagonal de baixo para cima
            // da direita para a esquerda
            else {
                for (size_t i = linhaOrigem - 1, j = colunaOrigem - 1; i > linhaDestino; i--, j--) {
                    if (posicoes[i][j]->estaOcupado()) {
                        return false;
                    }
                }
                return true;
            }
        }
    }
}

//Retorna o endereço de uma peca em uma dada posição
Peca* Tabuleiro::getPeca(int linha, int coluna) {
    return posicoes[linha][coluna]->getPeca();
}

//Destrutor desaloca todas as posicoes
Tabuleiro::~Tabuleiro() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            delete posicoes[i][j];
        }
    }
}