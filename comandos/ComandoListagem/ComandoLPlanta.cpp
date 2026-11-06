#include "ComandoLPlanta.h"
#include "../simulador.h"
#include "../jardim.h"
#include <iostream>
#include <cctype>
ComandoLPlanta::ComandoLPlanta(std::stringstream& ss) {
    std::string pos, lixo;
    if (ss >> pos && pos.length() == 2 && isalpha(pos[0]) && isalpha(pos[1]) && !(ss >> lixo)) {
        this->linha = pos[0] - 'a';
        this->coluna = pos[1] - 'a';
        this->sintaxe_valida = true;
    } else {
        this->sintaxe_valida = false;
    }
}
void ComandoLPlanta::executa(Simulador& simulador) const {
    if (!sintaxe_valida) {
        std::cout << "Sintaxe invalida. Uso: lplanta <lc>" << std::endl;
        return;
    }
    if (simulador.getJardim() && simulador.getJardim()->isPosicaoValida(linha, coluna)) {
        simulador.listarSolo(linha, coluna); // Reutiliza o lsolo
    } else if (simulador.getJardim()) {
        std::cout << "ERRO: A posicao esta fora dos limites do jardim." << std::endl;
    }
}