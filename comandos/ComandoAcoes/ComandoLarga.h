#ifndef COMANDOLARGA_H
#define COMANDOLARGA_H
#include "Comando.h"
#include <sstream>
class ComandoLarga : public Comando {
    bool sintaxe_valida;
public:
    explicit ComandoLarga(std::stringstream& ss);
    void executa(Simulador& simulador) const override;
};
#endif //COMANDOLARGA_H