#ifndef POO_TRABALHOPRATICO_CATO_H
#define POO_TRABALHOPRATICO_CATO_H

#include "Planta.h"

class Cato : public Planta {
    private:
    int instantes_excesso_agua;
    int instantes_falta_nutrientes;
public:
    Cato();
    Planta* clone() const override;
    // Declaração de que esta classe cumpre o contrato da classe base,
    // substituindo (override) os seus métodos virtuais puros.
    void atualizar(Jardim& jardim, int linha, int coluna, int instante) override;
    std::string getTipo() const override;
    char getChar() const override;
};

#endif //POO_TRABALHOPRATICO_CATO_H