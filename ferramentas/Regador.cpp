#include "Regador.h"
#include "../Posicao.h"
#include "../Settings.h"
#include <iostream>

Regador::Regador() : Ferramenta() {
    this->capacidade = Settings::Regador::capacidade;
}

Ferramenta* Regador::clone() const {
    return new Regador(*this);
}

bool Regador::usar(Posicao& pos) {
    if (this->capacidade > 0) {
        // Aumenta a água do solo
        pos.setAgua(pos.getAgua() + Settings::Regador::dose);
        // Gasta do depósito
        this->capacidade -= Settings::Regador::dose;
        std::cout << "[FERRAMENTA] Regador usado. Agua no solo: " << pos.getAgua()
                  << " | Restante: " << this->capacidade << std::endl;
        return true;
    } else {
        std::cout << "[FERRAMENTA] O Regador esta vazio!" << std::endl;
        // Aqui podias implementar a lógica de "atirar para longe" (destruir) se quisesses
        return false;
    }
}

std::string Regador::getTipo() const { return "Regador"; }
char Regador::getChar() const { return 'R'; }
bool Regador::estaVazia() const {
    return capacidade <= 0;
}