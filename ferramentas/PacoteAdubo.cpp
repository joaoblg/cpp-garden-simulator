#include "PacoteAdubo.h"
#include "../Posicao.h"
#include "../Settings.h"
#include <iostream>

PacoteAdubo::PacoteAdubo() : Ferramenta() {
    this->quantidade = Settings::Adubo::capacidade;
}
Ferramenta* PacoteAdubo::clone() const {
    return new PacoteAdubo(*this);
}
bool PacoteAdubo::usar(Posicao& pos) {
    if (this->quantidade > 0) {
        pos.setNutrientes(pos.getNutrientes() + Settings::Adubo::dose);
        this->quantidade -= Settings::Adubo::dose;
        std::cout << "[FERRAMENTA] Adubo aplicado. Nutrientes: " << pos.getNutrientes()
                  << " | Restante: " << this->quantidade << std::endl;
        return true;
    } else {
        std::cout << "[FERRAMENTA] O Pacote de Adubo esta vazio!" << std::endl;
        return false;
    }
}

std::string PacoteAdubo::getTipo() const { return "PacoteAdubo"; }
char PacoteAdubo::getChar() const { return 'A'; }
bool PacoteAdubo::estaVazia() const {
    return quantidade <= 0;
}