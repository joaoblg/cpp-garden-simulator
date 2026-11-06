#include "ComandoPlanta.h"
#include "../simulador.h"
#include "../Jardim.h"
#include <iostream>
#include <cctype>

ComandoPlanta::ComandoPlanta(std::stringstream& ss) {
    std::string pos, tipo_str, lixo;

    // 1. Validação de Sintaxe movida para o construtor
    if (ss >> pos && pos.length() == 2 && isalpha(pos[0]) && isalpha(pos[1]) &&
        ss >> tipo_str && tipo_str.length() == 1 && !(ss >> lixo))
    {
        this->linha = pos[0] - 'a';
        this->coluna = pos[1] - 'a';
        this->tipo = tipo_str[0];
        this->sintaxe_valida = true;
    } else {
        this->sintaxe_valida = false;
    }
}

void ComandoPlanta::executa(Simulador& simulador) const {
    // 1. O 'executa' agora verifica primeiro a sintaxe
    if (!sintaxe_valida) {
        std::cout << "Comando 'planta' com sintaxe invalida. Uso: planta <lc> <tipo>" << std::endl;
        return;
    }

    // 2. Se a sintaxe estiver OK, executa a Validação Semântica
    if (simulador.getJardim() && simulador.getJardim()->isPosicaoValida(linha, coluna)) {
        simulador.tentaPlantar(linha, coluna, tipo);
    } else if (simulador.getJardim()) {
        std::cout << "ERRO: A posicao esta fora dos limites do jardim." << std::endl;
    }
}
