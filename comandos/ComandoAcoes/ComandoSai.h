#ifndef COMANDOSAI_H
#define COMANDOSAI_H
#include "Comando.h"
#include <sstream>
class ComandoSai : public Comando {
    bool sintaxe_valida;
public:
    explicit ComandoSai(std::stringstream& ss);
    void executa(Simulador& simulador) const override;
};
#endif //COMANDOSAI_H