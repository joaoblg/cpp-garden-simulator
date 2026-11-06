#include "Planta.h"
#include <sstream> // Necessário para o ostringstream
#include <iostream>

// Construtor da classe base
Planta::Planta(BelezaPlanta beleza) : saude(100),
      agua_acumulada(10.0),
      nutrientes_acumulados(10.0),
      beleza(beleza) {}
// Adiciona este destrutor (pode estar vazio, o importante é que exista para a mensagem)
Planta::~Planta() {
    std::cout << "Destrutor da Planta: Uma planta foi destruida." << std::endl;
}

// Implementação do método getInfo, que será herdado por todas as plantas
std::string Planta::getInfo() const {
    std::ostringstream oss;
    oss << getTipo() << " | Saude: " << saude
        << " | Agua Acum.: " << agua_acumulada
        << " | Nutr. Acum.: " << nutrientes_acumulados;
    return oss.str();
}

Planta::Beleza Planta::getBeleza() const {
    return beleza;
}
