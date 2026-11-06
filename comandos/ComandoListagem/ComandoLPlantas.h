#ifndef COMANDOLPLANTAS_H
#define COMANDOLPLANTAS_H
#include "Comando.h"
#include <sstream>

class ComandoLPlantas : public Comando {
private:
    bool sintaxe_valida;
public:
    explicit ComandoLPlantas(std::stringstream& ss);
    void executa(Simulador& simulador) const override;
};
#endif //COMANDOLPLANTAS_H
