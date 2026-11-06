#include "ComandoLArea.h"
#include "../simulador.h"
#include <iostream>

ComandoLArea::ComandoLArea(std::stringstream& ss) {
    std::string lixo;
    sintaxe_valida = !(ss >> lixo);
}

void ComandoLArea::executa(Simulador& simulador) const {
    if (!sintaxe_valida) {
        std::cout << "Sintaxe invalida. Comando 'larea' nao aceita parametros." << std::endl;
        return;
    }
    simulador.listarArea();
}