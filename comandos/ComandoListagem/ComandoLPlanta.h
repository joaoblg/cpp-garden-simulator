#ifndef COMANDOLPLANTA_H
#define COMANDOLPLANTA_H
#include "Comando.h"
#include <sstream>
class ComandoLPlanta : public Comando {
    int linha, coluna;
    bool sintaxe_valida;
public:
    explicit ComandoLPlanta(std::stringstream& ss);
    void executa(Simulador& simulador) const override;
};
#endif //COMANDOLPLANTA_H