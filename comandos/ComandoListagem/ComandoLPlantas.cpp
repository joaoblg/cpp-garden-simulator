#include "ComandoLPlantas.h"
#include "../simulador.h"
#include <iostream>

ComandoLPlantas::ComandoLPlantas(std::stringstream& ss) {
    std::string lixo;
    if (!(ss >> lixo)) { // Verifica se NÃO há parâmetros a mais
        sintaxe_valida = true;
    } else {
        sintaxe_valida = false;
    }
}

void ComandoLPlantas::executa(Simulador& simulador) const {
    if (!sintaxe_valida) {
        std::cout << "Comando 'lplantas' nao aceita parametros." << std::endl;
        return;
    }
    simulador.listarPlantas();
}
