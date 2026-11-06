#include "ComandoMove.h"
#include "../Simulador.h"
#include "../Jardim.h"
#include "../Jardineiro.h"
#include "../Settings.h"
#include <iostream>

ComandoMove::ComandoMove(char dir) : direcao(dir) {}

void ComandoMove::executa(Simulador& simulador) const {
    Jardineiro* jardineiro = simulador.getJardineiro();
    Jardim* jardim = simulador.getJardim();

    // 1. Validação: O jardineiro tem de estar no jardim
    if (!jardineiro->estaNoJardim()) {
        std::cout << "ERRO: O jardineiro nao se pode mover porque nao esta no jardim." << std::endl;
        return;
    }

    // 2. Validação: Limite de movimentos por turno
    if (simulador.getMovimentosNesteTurno() >= Settings::Jardineiro::max_movimentos) {
        std::cout << "ERRO: O jardineiro esta cansado! Ja se moveu "
                  << Settings::Jardineiro::max_movimentos << " vezes neste turno." << std::endl;
        return;
    }

    // 3. Validação: Limites do Jardim (Cálculo da posição futura)
    int prox_linha = jardineiro->getLinha();
    int prox_coluna = jardineiro->getColuna();

    // Usamos este switch apenas para CALCULAR a futura posição
    switch (direcao) {
        case 'c': prox_linha--; break;
        case 'b': prox_linha++; break;
        case 'e': prox_coluna--; break;
        case 'd': prox_coluna++; break;
        default: ;
    }

    if (jardim && jardim->isPosicaoValida(prox_linha, prox_coluna)) {

        // 1. Executa o movimento
        jardineiro->mover(direcao);

        simulador.verificarFerramentasNoChao();
        // 2. Atualiza o contador no simulador
        simulador.incrementarMovimentos();

        // 3. Atualiza o ecrã
        simulador.redesenharJardim();
    } else {
        std::cout << "ERRO: Nao pode mover-se para fora do jardim." << std::endl;
    }
}