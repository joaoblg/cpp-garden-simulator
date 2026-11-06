#include "ComandoLarga.h"
#include "../simulador.h"
#include "../jardineiro.h"
#include <iostream>
ComandoLarga::ComandoLarga(std::stringstream& ss) {
    std::string lixo;
    sintaxe_valida = !(ss >> lixo);
}
void ComandoLarga::executa(Simulador& simulador) const {
    if (!sintaxe_valida) {
        std::cout << "Sintaxe invalida. Comando 'larga' nao aceita parametros." << std::endl;
        return;
    }
    simulador.getJardineiro()->largarFerramenta();
}