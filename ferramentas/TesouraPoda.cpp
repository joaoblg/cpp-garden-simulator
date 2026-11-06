#include "TesouraPoda.h"
#include "../Posicao.h"
#include "../plantas/Planta.h" // Precisa de conhecer a Planta
#include <iostream>

TesouraPoda::TesouraPoda() : Ferramenta() {}
Ferramenta* TesouraPoda::clone() const {
    return new TesouraPoda(*this);
}
bool TesouraPoda::usar(Posicao& pos) {
    Planta* p = pos.getPlanta();

    // --- CORREÇÃO AQUI ---
    // Usamos 'Planta::Beleza::FEIA' ou 'Planta::BelezaPlanta::FEIA'
    // Como definiste 'using Beleza = BelezaPlanta', podes usar 'Planta::Beleza'
    if (p != nullptr && p->getBeleza() == Planta::Beleza::FEIA) {
        std::cout << "[FERRAMENTA] Tesoura cortou uma planta feia (" << p->getTipo() << ")!" << std::endl;
        pos.setPlanta(nullptr); // Mata a planta (o destrutor é chamado automaticamente)
        return true;
    }
    return false;
}

std::string TesouraPoda::getTipo() const { return "TesouraPoda"; }
char TesouraPoda::getChar() const { return 'T'; }