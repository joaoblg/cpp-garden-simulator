#ifndef POO_TRABALHOPRATICO_ERVADANINHA_H
#define POO_TRABALHOPRATICO_ERVADANINHA_H

#include "Planta.h"

class ErvaDaninha : public Planta {
    private:
    int instantes_vida;
    int contador_multiplicacao{};
public:
    ErvaDaninha();
    Planta* clone() const override;
    void atualizar(Jardim& jardim, int linha, int coluna, int instante) override;
    std::string getTipo() const override;
    char getChar() const override;
};

#endif //POO_TRABALHOPRATICO_ERVADANINHA_H
