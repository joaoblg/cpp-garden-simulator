#include "PaDeTransplante.h"
#include "../Posicao.h"
#include "../plantas/Planta.h"
#include <iostream>

PaDeTransplante::PaDeTransplante() : Ferramenta(), planta_carregada(nullptr) {}

PaDeTransplante::~PaDeTransplante() {
        delete planta_carregada;

}
Ferramenta* PaDeTransplante::clone() const {
    return new PaDeTransplante(*this);
}
bool PaDeTransplante::usar(Posicao& pos) {
    // CASO 1: Largar planta (Se temos uma planta na pá e o solo está vazio)
    if (planta_carregada != nullptr) {
        if (!pos.isOcupada()) {
            pos.setPlanta(planta_carregada); // Planta no solo
            std::cout << "[FERRAMENTA] Pa de Transplante: Replantou uma "
                      << planta_carregada->getTipo() << "." << std::endl;
            planta_carregada = nullptr; // A pá fica vazia
            return true;
        }
        std::cout << "[FERRAMENTA] Nao podes plantar aqui, o solo ja esta ocupado." << std::endl;
        return false;
    }

    // CASO 2: Apanhar planta (Se a pá está vazia e o solo tem planta)
    if (pos.isOcupada()) {
        planta_carregada = pos.retirarPlanta();

        std::cout << "[FERRAMENTA] Pa de Transplante: Levantaste uma "
                << planta_carregada->getTipo() << " do solo." << std::endl;
        return true;
    }
    std::cout << "[FERRAMENTA] Nao ha nada aqui para transplantar." << std::endl;
    return false;
}

std::string PaDeTransplante::getTipo() const { return "PaDeTransplante"; }
char PaDeTransplante::getChar() const { return 'Z'; }