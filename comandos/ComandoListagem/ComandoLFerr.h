#ifndef COMANDOLFERR_H
#define COMANDOLFERR_H
#include "Comando.h"
#include <sstream>
class ComandoLFerr : public Comando {
    bool sintaxe_valida;
public:
    explicit ComandoLFerr(std::stringstream& ss);
    void executa(Simulador& simulador) const override;
};
#endif //COMANDOLFERR_H