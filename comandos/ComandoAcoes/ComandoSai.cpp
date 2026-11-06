#include "ComandoSai.h"
#include "../Simulador.h"
#include "../Jardineiro.h"
#include "../Settings.h" // Necessário para o limite
#include <iostream>

ComandoSai::ComandoSai(std::stringstream& ss) {
    std::string lixo;
    sintaxe_valida = !(ss >> lixo);
}

void ComandoSai::executa(Simulador& simulador) const {
    if (!sintaxe_valida) {
        std::cout << "Sintaxe invalida. Comando 'sai' nao aceita parametros." << std::endl;
        return;
    }

    if (simulador.getEntradasSaidasTurno() >= Settings::Jardineiro::max_entradas_saidas) {
        std::cout << "ERRO: Ja esgotou as entradas/saidas neste turno ("
                  << Settings::Jardineiro::max_entradas_saidas << ")." << std::endl;
        return;
    }

    if (simulador.getJardineiro()->estaNoJardim()) {
        simulador.getJardineiro()->sairDoJardim();

        simulador.incrementarEntradasSaidas();

        simulador.redesenharJardim();
    } else {
        std::cout << "ERRO: O jardineiro nao pode sair, pois ja esta fora do jardim." << std::endl;
    }
}