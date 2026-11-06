#include "ComandoGrava.h"
#include "../simulador.h"
#include <iostream>
ComandoGrava::ComandoGrava(std::stringstream& ss) {
    std::string lixo;
    if (ss >> nome && !(ss >> lixo)) {
        sintaxe_valida = true;
    } else {
        sintaxe_valida = false;
    }
}
void ComandoGrava::executa(Simulador& simulador) const {
    simulador.gravarJardim(nome);
}