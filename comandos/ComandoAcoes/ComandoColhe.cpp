#include "ComandoColhe.h"
#include "../simulador.h"
#include "../Jardim.h"
#include <iostream>
#include <cctype>

ComandoColhe::ComandoColhe(std::stringstream& ss) {
    std::string pos, lixo;
    // Validação de sintaxe
    if (ss >> pos && pos.length() == 2 && isalpha(pos[0]) && isalpha(pos[1]) && !(ss >> lixo)) {
        this->linha = pos[0] - 'a';
        this->coluna = pos[1] - 'a';
        this->sintaxe_valida = true;
    } else {
        this->sintaxe_valida = false;
    }
}

void ComandoColhe::executa(Simulador& simulador) const {
    if (!sintaxe_valida) {
        std::cout << "Sintaxe invalida. Uso: colhe <lc>" << std::endl;
        return;
    }

    // Validação Semântica (limites do jardim)
    if (simulador.getJardim() && simulador.getJardim()->isPosicaoValida(linha, coluna)) {
        simulador.tentaColher(linha, coluna);

    } else if (simulador.getJardim()) {
        std::cout << "ERRO: A posicao " << static_cast<char>('a' + linha)
                  << static_cast<char>('a' + coluna) << " esta fora dos limites do jardim." << std::endl;
    }
}