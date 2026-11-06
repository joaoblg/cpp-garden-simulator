#include "ComandoEntra.h"
#include "../Simulador.h"
#include "../Jardim.h"
#include "../Jardineiro.h"
#include "../Settings.h" // Necessário para o limite
#include <iostream>
#include <cctype>

ComandoEntra::ComandoEntra(std::stringstream& ss) {
    std::string pos, lixo;
    if (ss >> pos && pos.length() == 2 && isalpha(pos[0]) && isalpha(pos[1]) && !(ss >> lixo)) {
        this->linha = pos[0] - 'a';
        this->coluna = pos[1] - 'a';
        this->sintaxe_valida = true;
    } else {
        this->sintaxe_valida = false;
    }
}

void ComandoEntra::executa(Simulador& simulador) const {
    if (!sintaxe_valida) {
        std::cout << "Sintaxe invalida. Uso: entra <lc>" << std::endl;
        return;
    }

    // --- VALIDAÇÃO DO LIMITE DE TURNO ---
    if (simulador.getEntradasSaidasTurno() >= Settings::Jardineiro::max_entradas_saidas) {
        std::cout << "ERRO: Ja esgotou as entradas/saidas neste turno ("
                  << Settings::Jardineiro::max_entradas_saidas << ")." << std::endl;
        return;
    }

    if (simulador.getJardim() && simulador.getJardim()->isPosicaoValida(linha, coluna)) {
        simulador.getJardineiro()->entrarNoJardim(linha, coluna);

        simulador.incrementarEntradasSaidas();

        simulador.verificarFerramentasNoChao();

        simulador.redesenharJardim();
    } else if (simulador.getJardim()) {
        std::cout << "ERRO: A posicao esta fora dos limites do jardim." << std::endl;
    }
}