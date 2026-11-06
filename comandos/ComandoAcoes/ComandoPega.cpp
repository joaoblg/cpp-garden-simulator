#include "ComandoPega.h"
#include "../simulador.h"
#include "../jardineiro.h"
#include <iostream>
ComandoPega::ComandoPega(std::stringstream& ss) {
    std::string lixo;
    if (ss >> n_serie && !(ss >> lixo)) {
        sintaxe_valida = true;
    } else {
        sintaxe_valida = false;
    }
}
void ComandoPega::executa(Simulador& simulador) const {
    if (!sintaxe_valida) {
        std::cout << "Sintaxe invalida. Uso: pega <n>" << std::endl;
        return;
    }
    simulador.getJardineiro()->pegarFerramenta(n_serie);
}