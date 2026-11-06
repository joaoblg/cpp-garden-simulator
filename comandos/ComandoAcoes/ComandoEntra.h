#ifndef COMANDOENTRA_H
#define COMANDOENTRA_H
#include "Comando.h"
#include <sstream>
class ComandoEntra : public Comando {
    int linha, coluna;
    bool sintaxe_valida;
public:
    explicit ComandoEntra(std::stringstream& ss);
    void executa(Simulador& simulador) const override;
};
#endif //COMANDOENTRA_H