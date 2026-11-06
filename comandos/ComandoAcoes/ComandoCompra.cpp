#include "ComandoCompra.h"
#include "../simulador.h"
#include "../jardineiro.h"
#include <iostream>
ComandoCompra::ComandoCompra(std::stringstream& ss) {
    std::string tipo_str, lixo;
    if (ss >> tipo_str && tipo_str.length() == 1 && !(ss >> lixo)) {
        this->tipo = tipo_str[0];
        this->sintaxe_valida = true;
    } else {
        this->sintaxe_valida = false;
    }
}
void ComandoCompra::executa(Simulador& simulador) const {
    if (!sintaxe_valida) {
        std::cout << "Sintaxe invalida. Uso: compra <c>" << std::endl;
        return;
    }
    simulador.getJardineiro()->comprarFerramenta(tipo);
}