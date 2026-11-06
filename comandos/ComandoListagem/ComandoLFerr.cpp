#include "ComandoLFerr.h"
#include "../simulador.h"
#include <iostream>

ComandoLFerr::ComandoLFerr(std::stringstream& ss) {
    std::string lixo;
    sintaxe_valida = !(ss >> lixo);
}

void ComandoLFerr::executa(Simulador& simulador) const {
    if (!sintaxe_valida) {
        std::cout << "Sintaxe invalida. Comando 'lferr' nao aceita parametros." << std::endl;
        return;
    }
    simulador.listarFerramentasJardineiro();
}