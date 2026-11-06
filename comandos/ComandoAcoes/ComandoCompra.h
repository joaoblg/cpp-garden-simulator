#ifndef COMANDOCOMPRA_H
#define COMANDOCOMPRA_H
#include "Comando.h"
#include <sstream>
class ComandoCompra : public Comando {
    char tipo;
    bool sintaxe_valida;
public:
    explicit ComandoCompra(std::stringstream& ss);
    void executa(Simulador& simulador) const override;
};
#endif //COMANDOCOMPRA_H
