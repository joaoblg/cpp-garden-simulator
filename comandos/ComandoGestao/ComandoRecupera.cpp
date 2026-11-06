#include "ComandoRecupera.h"
#include "../simulador.h"
#include <iostream>
ComandoRecupera::ComandoRecupera(std::stringstream& ss) {
    std::string lixo;
    if (ss >> nome && !(ss >> lixo)) {
        sintaxe_valida = true;
    } else {
        sintaxe_valida = false;
    }
}
void ComandoRecupera::executa(Simulador& simulador) const {
    simulador.recuperarJardim(nome);
}