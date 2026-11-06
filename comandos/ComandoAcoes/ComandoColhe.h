#ifndef COMANDOCOLHE_H
#define COMANDOCOLHE_H
#include "Comando.h"
#include <sstream>
class ComandoColhe : public Comando {
    int linha, coluna;
    bool sintaxe_valida;
public:
    explicit ComandoColhe(std::stringstream& ss);
    void executa(Simulador& simulador) const override;
};
#endif //COMANDOCOLHE_H