#include "Ferramenta.h"

// Inicialização da variável estática.
int Ferramenta::proximo_numero_serie = 1;

Ferramenta::Ferramenta() {
    // Atribui o número de série atual e incrementa o contador para a próxima
    this->numero_serie = proximo_numero_serie++;
}

int Ferramenta::getNumeroSerie() const {
    return numero_serie;
}
