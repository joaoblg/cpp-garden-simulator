#ifndef COMANDOAVANCA_H
#define COMANDOAVANCA_H
#include "Comando.h"
#include <sstream>

class ComandoAvanca : public Comando {
private:
    int n_instantes;
    bool sintaxe_valida;
public:
    explicit ComandoAvanca(std::stringstream& ss);
    void executa(Simulador& simulador) const override;
};
#endif //COMANDOAVANCA_H
