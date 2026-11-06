#ifndef COMANDOPEGA_H
#define COMANDOPEGA_H
#include "Comando.h"
#include <sstream>
class ComandoPega : public Comando {
    int n_serie;
    bool sintaxe_valida;
public:
    explicit ComandoPega(std::stringstream& ss);
    void executa(Simulador& simulador) const override;
};
#endif //COMANDOPEGA_H