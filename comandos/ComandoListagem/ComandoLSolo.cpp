#include "ComandoLSolo.h"
#include "../simulador.h"
#include "../jardim.h"
#include <iostream>
#include <cctype>
ComandoLSolo::ComandoLSolo(std::stringstream& ss) : raio(-1) {
    std::string pos, lixo;
    if (ss >> pos && pos.length() == 2 && isalpha(pos[0]) && isalpha(pos[1])) {
        this->linha = pos[0] - 'a';
        this->coluna = pos[1] - 'a';
        this->sintaxe_valida = true;
        if (ss >> raio) { // Tenta ler o 'n' opcional
            if (ss >> lixo) { // Se houver mais alguma coisa, é inválido
                this->sintaxe_valida = false;
            }
        }
    } else {
        this->sintaxe_valida = false;
    }
}
void ComandoLSolo::executa(Simulador& simulador) const {
    // 1. Validação de Sintaxe
    if (!sintaxe_valida) {
        std::cout << "Sintaxe invalida. Uso: lsolo <lc> [n]" << std::endl;
        return;
    }

    // 2. Validação Semântica (Posição válida?)
    if (simulador.getJardim() && simulador.getJardim()->isPosicaoValida(linha, coluna)) {

        // CORREÇÃO: Apenas uma chamada, passando o raio.
        // O método listarSolo no Simulador já decide o que mostrar.
        simulador.listarSolo(linha, coluna, raio);

    } else if (simulador.getJardim()) {
        std::cout << "ERRO: A posicao "
                  << static_cast<char>('a' + linha)
                  << static_cast<char>('a' + coluna)
                  << " esta fora dos limites do jardim." << std::endl;
    }
}