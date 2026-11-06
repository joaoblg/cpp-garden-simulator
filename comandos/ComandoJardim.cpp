#include "ComandoJardim.h"
#include "../simulador.h"
#include <iostream>
ComandoJardim::ComandoJardim(std::stringstream& ss) {
    std::string lixo;
    if (ss >> linhas && ss >> colunas && !(ss >> lixo)) {
        sintaxe_valida = true;
    } else {
        sintaxe_valida = false;
    }
}
void ComandoJardim::executa(Simulador& simulador) const {
    if (!sintaxe_valida) {
        std::cout << "Sintaxe invalida. Uso: jardim <linhas> <colunas>" << std::endl;
        return;
    }
    simulador.criaJardim(linhas, colunas);
}