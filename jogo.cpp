/*
Projeto: Jogo de Xadrez
3º Semestre de Ciências da Computação - UFSCar Sorocaba
Programação orientada a objetos
Profª Katti Faceli
Integrantes: Giovanni Alvarenga, Fábio Yamaya, João Victor Vilar
Implementação da classe "jogo"
Descrição:Implementa as funções da classe "jogo" contidas no arquivo .h
*/

#include "jogo.h"
#include <fstream>
#include <limits>
#include <string>
#include "tabuleiro.h"

using namespace std;

//Construtor da classe
Jogo::Jogo() {
    string nomeJogador;
    cout << "---------------Jogo de Xadrez---------------" << endl;
    cout << "Digite o nome do Jogador 1:" << endl;
    cin >> nomeJogador;
    jogador1 = new Jogador(nomeJogador, 0);
    cout << "Digite o nome do Jogador 2:" << endl;
    cin >> nomeJogador;
    jogador2 = new Jogador(nomeJogador, 1);

    //Cria o objeto tabuleiro usando a classe Tabuleiro
    tabuleiro1 = new Tabuleiro();

    //Cria os peões e coloca no vetor de pecas
    for (int i = 0; i < 8; i++) {
        pecasBrancas[i] = new Peao(0, 'P');
        pecasPretas[i] = new Peao(1, 'p');
    }

    //Cria o restante das pecas brancas e coloca no vetor em ordem
    pecasBrancas[8] = new Torre(0, 'T');
    pecasBrancas[15] = new Torre(0, 'T');
    pecasBrancas[9] = new Cavalo(0, 'C');
    pecasBrancas[14] = new Cavalo(0, 'C');
    pecasBrancas[10] = new Bispo(0, 'B');
    pecasBrancas[13] = new Bispo(0, 'B');
    pecasBrancas[11] = new Rei(0, 'K');
    pecasBrancas[12] = new Rainha(0, 'Q');

    //Cria o restante das pecas pretas e coloca no vetor em ordem
    pecasPretas[8] = new Torre(1, 't');
    pecasPretas[15] = new Torre(1, 't');
    pecasPretas[9] = new Cavalo(1, 'c');
    pecasPretas[14] = new Cavalo(1, 'c');
    pecasPretas[10] = new Bispo(1, 'b');
    pecasPretas[13] = new Bispo(1, 'b');
    pecasPretas[11] = new Rei(1, 'k');
    pecasPretas[12] = new Rainha(1, 'q');

    //Pega o vetor de pecas ativas de cada jogador
    Peca** pecasAtivas1 = jogador1->getPecasAtivas();
    Peca** pecasAtivas2 = jogador2->getPecasAtivas();

    //inicializa todas as pecas como pecas ativas
    for (size_t i = 0; i < 16; i++) {
        pecasAtivas1[i] = pecasBrancas[i];
        pecasAtivas2[i] = pecasPretas[i];
    }

    //Coloca as pecas no tabuleiro em ordem
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 7; j++) {
            if (i == 1) {
                tabuleiro1->setPeca(pecasPretas[j], i, j);
                tabuleiro1->setPeca(pecasBrancas[j], 6, j);
            }
            if (i == 0) {
                tabuleiro1->setPeca(pecasPretas[j + 8], i, j);
                tabuleiro1->setPeca(pecasBrancas[j + 8], 7, j);
            }
        }
    }

    //Chama o metodo que irá efetivamente rodar o jogo
    turnos();
}

//Metodo que alterna os turnos dos jogadores e verifica o estado do jogo
void Jogo::turnos() {
    //O jogo sempre começa com a cor branca, no caso 0;
    int turno = 0;

    //Flag de termino do jogo
    int acabou = 0;

    //Variaveis usadas para ler os comandos passados pelo usuário
    int lO, cO, lD, cD;
    char lOletra, lDletra;

    //Flag de saida
    int sair = 0;

    //Flag de entrada valida
    int entradaValida = 0;

    //Usado para ler input do usuário
    char continuar;

    //Cria o arquivo usado para salvar o estado do jogo
    fstream arq;

    //Desenha o tabuleiro inicial
    tabuleiro1->desenhar();

    while (!entradaValida) {
        //Decide se o usuário deseja continuar ou abandonar a partida anterior salva
        cout << "Deseja continuar o último jogo? <S/N>" << endl;

        try {
            cin >> continuar;
            if (!cin) {
                throw 2;
            }
        } catch (int erro) {
            //Limpa o buffer
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (erro == 2) {
                entradaValida = 0;
            }
        }

        //Caso o jogador opte por continuar a partida salva
        if (continuar == 'S') {
            //Abre o arquivo salvo
            arq.open("save.txt");

            //Refaz todos os movimentos do jogo anterior salvos no arquivo
            while (arq) {
                arq >> lO;
                arq >> cO;
                arq >> lD;
                arq >> cD;
                if (!arq) {
                    break;
                }
                movimenta(lO, cO, lD, cD);
                turno = !turno;
            }
            //Desenha o tabuleiro novamente após retomar o estado do jogo anterior
            tabuleiro1->desenhar();

            //Fecha o arquivo
            arq.close();

            //Reabre o arquivo no fim, para continuar salvando os próximos movimentos
            arq.open("save.txt", ios::in | ios::out | ios::ate);

            entradaValida = 1;
        } else if (continuar == 'N') {
            //Abre o arquivo e limpa os dados gravados, para salvar os próximos movimentos
            arq.open("save.txt", fstream::in | fstream::out | fstream::trunc);

            entradaValida = 1;
        }
        if (!entradaValida) {
            cout << "Entrada Invalida" << endl;
        }
    }

    //Alterna os turnos até que um dos jogadores esteja em Xeque Mate
    while (!acabou) {
        if (!turno) {
            jogador1->printNome();
            cout << " Insira seu movimento:" << endl;
        } else {
            jogador2->printNome();
            cout << " Insira seu movimento:" << endl;
        }

        cout << "Para sair do jogo, insira 'q'" << endl;

        //Recebe as entradas e testa para entradas inválidas
        try {
            cin >> lOletra;
            if (!cin) {
                throw 1;
            }
            //Caso o jogadro decida sair do jogo
            if (lOletra == 'q') {
                return;
            }
            cin >> cO;
            if (!cin) {
                throw 1;
            }
            cin >> lDletra;
            if (!cin) {
                throw 1;
            }
            cin >> cD;
            if (!cin) {
                throw 1;
            }
            cout << lOletra << cO << lDletra << cD << endl;
            //Verifica se o movimento esta dentro do tabuleiro
            if (lOletra < 'a' || lOletra > 'h' || lDletra < 'a' || lDletra > 'h') {
                cout << "fora 1" << endl;
                throw 1;
            } else if (cO < 1 || cO > 8 || cD < 1 || cD > 8) {
                cout << "fora " << endl;
                throw 1;
            }
            //Converte os caracteres em int nos valores reais do vetor
            lO = (int)lOletra - 97;
            cO--;
            lD = (int)lDletra - 97;
            cD--;
        }

        catch (int erro) {
            if (erro == 1) {
                cout << "exceção" << endl;
                //Limpa o buffer
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                //força um erro na condição de parada do while
                //fazendo com que o usuário tenha que inserir outro movimento
                lO = 0, cO = 0, lD = 0, cD = 0;
            }
        }

        //Caso o movimento seja inválido
        //Repete até o jogador inserir um movimento válido
        Peca* temp = tabuleiro1->getPeca(lO, cO);
        while (temp == NULL || temp->getCor() != turno || !movimenta(lO, cO, lD, cD)) {
            cout << "Movimento inválido, insira outro movimento" << endl;

            //Recebe as entradas e testa para entradas inválidas
            try {
                cin >> lOletra;
                if (!cin) {
                    throw 1;
                }
                //Caso o jogador decida sair do jogo
                if (lOletra == 'q') {
                    return;
                }
                cin >> cO;
                if (!cin) {
                    throw 1;
                }
                cin >> lDletra;
                if (!cin) {
                    throw 1;
                }
                cin >> cD;
                if (!cin) {
                    throw 1;
                }
                //Verifica se o movimento esta dentro do tabuleiro
                if (lOletra < 'a' || lOletra > 'h' || lDletra < 'a' || lDletra > 'h') {
                    throw 1;
                } else if (cO < 1 || cO > 8 || cD < 1 || cD > 8) {
                    throw 1;
                }
                //Converte os caracteres em int nos valores reais do vetor
                lO = (int)lOletra - 97;
                cO--;
                lD = (int)lDletra - 97;
                cD--;
                temp = tabuleiro1->getPeca(lO, cO);
            }

            catch (int erro) {
                if (erro == 1) {
                    //Limpa o buffer
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    //força um erro na condição de parada do while
                    //fazendo com que o usuário tenha que inserir outro movimento
                    lO = 0, cO = 0, lD = 0, cD = 0;
                }
            }
        }

        //Escreve o movimento no arquivo
        arq << lO << endl;
        arq << cO << endl;
        arq << lD << endl;
        arq << cD << endl;

        //Desenha o tabuleiro após o movimento
        tabuleiro1->desenhar();

        //Verifica se o jogador esta em xeque
        if (estaEmXeque(turno)) {
            if (turno) {
                jogador2->printNome();
            } else {
                jogador1->printNome();
            }
            cout << " Esta em Xeque" << endl;
        }

        //Verifica se o jogador está em Xeque Mate
        if (estaEmXequeMate(turno)) {
            cout << "xxxxxxxxxxxxxxxxx Xeque Mate xxxxxxxxxxxxxxxxx" << endl;
            if (turno) {
                jogador1->printNome();
            } else {
                jogador2->printNome();
            }
            cout << " Venceu o Jogo!!" << endl;
        }
        turno = !turno;
    }
    arq.close();
}

//Verifica se o movimento inserido é válido
bool Jogo::movimentoValido(int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino) {
    Peca* origem = tabuleiro1->getPeca(linhaOrigem, colunaOrigem);
    Peca* destino = tabuleiro1->getPeca(linhaDestino, colunaDestino);

    //Caso não haja peca na origem
    if (origem == NULL) {
        return false;
    }

    if (tabuleiro1->estaDentro(linhaOrigem, colunaOrigem, linhaDestino, colunaDestino)) {
        //Se for peao, verificar se ira executar movimento regular ou de captura
        if (origem->getTipo() == 'p' || origem->getTipo() == 'P') {
            if (destino != NULL) {
                if (origem->checaMovimento(linhaOrigem, colunaOrigem, linhaDestino, colunaDestino, 1)) {
                    return true;
                }
            } else {
                if (!tabuleiro1->caminhoLivre(linhaOrigem, colunaOrigem, linhaDestino, colunaDestino)) {
                    return false;
                }
                if (origem->checaMovimento(linhaOrigem, colunaOrigem, linhaDestino, colunaDestino, 0)) {
                    return true;
                }
            }
        }
        //Caso seja rei, verificar se o movimento não o deixará em Xeque
        else if (origem->getTipo() == 'k') {
            if (verificaXeque(linhaDestino, colunaDestino, 0)) {
                return false;
            } else {
                if (origem->checaMovimento(linhaOrigem, colunaOrigem, linhaDestino, colunaDestino)) {
                    if (tabuleiro1->caminhoLivre(linhaOrigem, colunaOrigem, linhaDestino, colunaDestino)) {
                        return true;
                    }
                }
            }
        } else if (origem->getTipo() == 'K') {
            if (verificaXeque(linhaDestino, colunaDestino, 1)) {
                return false;
            } else {
                if (origem->checaMovimento(linhaOrigem, colunaOrigem, linhaDestino, colunaDestino)) {
                    if (tabuleiro1->caminhoLivre(linhaOrigem, colunaOrigem, linhaDestino, colunaDestino)) {
                        return true;
                    }
                }
            }
        }
        //Caso contrário, verifica somente com o checaMovimento da peca
        else {
            if (origem->checaMovimento(linhaOrigem, colunaOrigem, linhaDestino, colunaDestino)) {
                if (tabuleiro1->caminhoLivre(linhaOrigem, colunaOrigem, linhaDestino, colunaDestino)) {
                    return true;
                }
            }
        }
    }
    return false;
}

//Movimenta e/ou captura a peca
bool Jogo::movimenta(int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino) {
    Peca* origem = tabuleiro1->getPeca(linhaOrigem, colunaOrigem);
    Peca* destino = tabuleiro1->getPeca(linhaDestino, colunaDestino);

    if (movimentoValido(linhaOrigem, colunaOrigem, linhaDestino, colunaDestino)) {
        //Se houver peca no destino
        if (destino != NULL) {
            int corOrigem = origem->getCor();
            int corDestino = destino->getCor();
            if (corDestino != corOrigem) {
                //Encontra a peca no vetor de pecas ativas e remove
                Peca** pecasAtivas;
                if (origem->getCor() == 0) {
                    pecasAtivas = jogador2->getPecasAtivas();
                } else {
                    pecasAtivas = jogador1->getPecasAtivas();
                }
                for (size_t i = 0; i < 16; i++) {
                    if (destino == pecasAtivas[i]) {
                        pecasAtivas[i] = NULL;
                    }
                }
            }
        }
        //Deixa a posição original vazia e move a peca para a posicao final
        tabuleiro1->setPeca(NULL, linhaOrigem, colunaOrigem);
        tabuleiro1->setPeca(origem, linhaDestino, colunaDestino);
        return true;
    }
}

//Retorna o estado do rei
bool Jogo::estaEmXeque(int cor) {
    int posicaoRei[2];
    Jogo::achaRei(cor, posicaoRei);
    return Jogo::verificaXeque(posicaoRei[0], posicaoRei[1], cor);
}

//Encontra o rei no tabuleiro, percorrendo todas as posicoes
void Jogo::achaRei(int cor, int posicaoRei[]) {
    int iRei, jRei;
    bool achou = 0;
    char tipo = ' ';
    for (iRei = 0; iRei < 8 && !achou; iRei++) {
        if (!cor) {
            for (jRei = 0; jRei < 8 && !achou; jRei++) {
                Peca* rei = tabuleiro1->getPeca(iRei, jRei);
                if (rei) {
                    tipo = rei->getTipo();
                    if (tipo == 'k') {
                        achou = 1;
                    }
                }
            }
        } else {
            for (jRei = 0; jRei < 8 && !achou; jRei++) {
                Peca* rei = tabuleiro1->getPeca(iRei, jRei);
                if (rei) {
                    tipo = rei->getTipo();
                    if (tipo == 'K') {
                        achou = 1;
                    }
                }
            }
        }
    }

    posicaoRei[0] = iRei - 1;
    posicaoRei[1] = jRei - 1;

    return;
}

//Verifica se o rei esta sendo ameacado
bool Jogo::verificaXeque(int iRei, int jRei, int cor) {
    Peca* atual;

    Peca* rei = tabuleiro1->getPeca(iRei, jRei);
    tabuleiro1->setPeca(NULL, iRei, jRei);

    //Verifica se alguma peca do adversario consegue se mover para a posicao do rei
    for (size_t i = 0; i < 8; i++) {
        for (size_t j = 0; j < 8; j++) {
            atual = tabuleiro1->getPeca(i, j);
            if (atual != NULL) {
                if (atual->getCor() == cor) {
                    if (atual->getTipo() != 'k' && atual->getTipo() != 'K') {
                        if (Jogo::movimentoValido(i, j, iRei, jRei)) {
                            //Caso consiga, o rei esta em Xeque
                            tabuleiro1->setPeca(rei, iRei, jRei);
                            return true;
                        }
                    }
                }
            }
        }
    }
    tabuleiro1->setPeca(rei, iRei, jRei);
    return false;
}

//Verifica se o rei esta em estado de Xeque Mate
bool Jogo::estaEmXequeMate(int cor) {
    int posicaoRei[2];
    Jogo::achaRei(cor, posicaoRei);

    //Primeiramente verifica se o rei esta em Xeque
    if (!Jogo::verificaXeque(posicaoRei[0], posicaoRei[1], cor)) {
        return false;
    }

    int i = posicaoRei[0] - 1;
    int j = posicaoRei[1] - 1;

    //Verifica se o rei consegue se mover para alguma posiçãp válida onde não esteja em Xeque
    for (; i <= posicaoRei[0] + 1; i++) {
        j = posicaoRei[1] - 1;
        for (; j <= posicaoRei[1] + 1; j++) {
            //cout << "Verificando se a posicao " << i << " " << j << " é válida" << endl;
            if (i >= 0 && i <= 7 && j >= 0 && j <= 7) {
                if (Jogo::movimentoValido(posicaoRei[0], posicaoRei[1], i, j)) {
                    return false;
                }
            }
        }
    }

    int iAmeacas[16];
    int jAmeacas[16];
    int nAmeacas = 0;

    //Encontra e guarda a posição de cada peca que atualmente esta deixando o rei em Xeque
    //Chamamos a peca que deixa o rei em Xeque de ameaca
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            if (Jogo::movimentoValido(i, j, posicaoRei[0], posicaoRei[1])) {
                //cout << "Ameaça da posicao: " << i << " " << j << endl;
                iAmeacas[nAmeacas] = i;
                jAmeacas[nAmeacas] = j;
                nAmeacas++;
            }
        }
    }

    //Verifica se alguma peca consegue capturar a ameaca ou bloquear
    // seu caminho até o rei, neutralizando o Xeque
    for (size_t ameaca = 0; ameaca < nAmeacas; ameaca++) {
        while ((iAmeacas[ameaca] != posicaoRei[0]) && (jAmeacas[ameaca] != posicaoRei[1])) {
            for (size_t linha = 0; linha < 8; linha++) {
                for (size_t coluna = 0; coluna < 8; coluna++) {
                    Peca* temp = tabuleiro1->getPeca(linha, coluna);
                    if (temp != NULL && (temp->getCor()) != cor) {
                        if (Jogo::movimentoValido(linha, coluna, iAmeacas[ameaca], jAmeacas[ameaca])) {
                            Peca* bloqueador = tabuleiro1->getPeca(linha, coluna);
                            Peca* bloqueio = tabuleiro1->getPeca(iAmeacas[ameaca], jAmeacas[ameaca]);
                            tabuleiro1->setPeca(bloqueador, iAmeacas[ameaca], jAmeacas[ameaca]);
                            if (!verificaXeque(posicaoRei[0], posicaoRei[1], cor)) {
                                return false;
                            }
                            tabuleiro1->setPeca(bloqueador, linha, coluna);
                            tabuleiro1->setPeca(bloqueio, iAmeacas[ameaca], jAmeacas[ameaca]);
                        }
                    }
                }
            }

            //Percorre todo o caminho da ameaça até o rei
            if (iAmeacas[ameaca] > posicaoRei[0]) {
                iAmeacas[ameaca]--;
            } else if (iAmeacas[ameaca] < posicaoRei[0]) {
                iAmeacas[ameaca]++;
            }
            if (jAmeacas[ameaca] > posicaoRei[1]) {
                jAmeacas[ameaca]--;
            } else if (jAmeacas[ameaca] < posicaoRei[1]) {
                jAmeacas[ameaca]++;
            }
        }
    }
    return true;
}

Jogo::~Jogo() {
    delete jogador1;
    delete jogador2;
    delete tabuleiro1;

    for (int i = 0; i < 16; i++) {
        delete pecasBrancas[i];
        delete pecasPretas[i];
    }
}