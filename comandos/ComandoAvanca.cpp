#include "ComandoAvanca.h"
#include "../simulador.h"
#include <iostream>

ComandoAvanca::ComandoAvanca(std::stringstream& ss) {
    int n;
    if (ss >> n) { // Tenta ler um número
        std::string lixo;
        if (n > 0 && !(ss >> lixo)) {
            this->n_instantes = n;
            this->sintaxe_valida = true;
        } else {
            this->sintaxe_valida = false; // Parâmetro inválido (ex: "avanca 0" ou "avanca 5 5")
        }
    } else {
        ss.clear(); // Limpa o estado de erro
        std::string lixo;
        if (ss >> lixo) { // Havia texto (ex: "avanca xyz")
            this->sintaxe_valida = false;
        } else { // Não havia mais nada
            this->n_instantes = 1; // Valor padrão
            this->sintaxe_valida = true;
        }
    }
}

void ComandoAvanca::executa(Simulador& simulador) const {
    if (!sintaxe_valida) {
        std::cout << "Comando 'avanca' com sintaxe invalida. Uso: avanca [n]" << std::endl;
        return;
    }
    simulador.avancarTurno(n_instantes);
}