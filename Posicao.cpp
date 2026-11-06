#include "Posicao.h"

#include <Ferramenta.h>

#include "plantas/Planta.h"
#include "Settings.h"
#include <random>

Posicao::Posicao() : planta(nullptr), ferramenta(nullptr) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distribAgua(Settings::Jardim::agua_min, Settings::Jardim::agua_max);
    std::uniform_int_distribution<> distribNutri(Settings::Jardim::nutrientes_min, Settings::Jardim::nutrientes_max);
    this->agua = distribAgua(gen);
    this->nutrientes = distribNutri(gen);
}
// Construtor de Cópia (Deep Copy)
Posicao::Posicao(const Posicao& outra)
    : agua(outra.agua), nutrientes(outra.nutrientes), ferramenta(nullptr) // Ferramentas não são copiadas (regra simplificada)
{
    if (outra.planta != nullptr) {
        this->planta = outra.planta->clone();
    } else {
        this->planta = nullptr;
    }

    if (outra.ferramenta != nullptr) {
        this->ferramenta = outra.ferramenta->clone();
    } else {
        this->ferramenta = nullptr;
    }
}
Posicao::~Posicao() {
    delete planta;
    delete ferramenta;
}
bool Posicao::isOcupada() const {
    return planta != nullptr;
}
void Posicao::setPlanta(Planta* p) {
    if (this->planta != nullptr) {
        delete this->planta;
    }
    this->planta = p;
}
Planta* Posicao::getPlanta() const {
    return planta;
}

double Posicao::getAgua() const {
    return agua;
}

void Posicao::setAgua(double valor) {
    this->agua = (valor < 0) ? 0 : valor; // Garante que a água não fica negativa
}
double Posicao::getNutrientes() const {
    return nutrientes;
}

void Posicao::setNutrientes(double valor) {
    this->nutrientes = (valor < 0) ? 0 : valor; // Garante que nutrientes não ficam negativos
}
// Retira a planta e entrega a responsabilidade de memória a quem chamou
Planta* Posicao::retirarPlanta() {
    Planta* p = this->planta;
    this->planta = nullptr; // Desliga a planta desta posição
    return p; // Devolve a planta viva
}
bool Posicao::temFerramenta() const { return ferramenta != nullptr; }

void Posicao::setFerramenta(Ferramenta* f) {
    if (this->ferramenta != nullptr) delete this->ferramenta;
    this->ferramenta = f;
}

Ferramenta* Posicao::retirarFerramenta() {
    Ferramenta* f = this->ferramenta;
    this->ferramenta = nullptr;
    return f;
}

Ferramenta* Posicao::getFerramenta() const { return ferramenta; }