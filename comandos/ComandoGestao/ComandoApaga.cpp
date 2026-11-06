#include "ComandoApaga.h"
#include "../simulador.h"
#include <iostream>
ComandoApaga::ComandoApaga(std::stringstream& ss) {
    std::string lixo;
    if (ss >> nome && !(ss >> lixo)) {
        sintaxe_valida = true;
    } else {
        sintaxe_valida = false;
    }
}
void ComandoApaga::executa(Simulador& simulador) const {
    simulador.apagarJardim(nome);
}