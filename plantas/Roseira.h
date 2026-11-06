#ifndef POO_TRABALHOPRATICO_ROSEIRA_H
#define POO_TRABALHOPRATICO_ROSEIRA_H

#include "Planta.h"

class Posicao;

class Roseira : public Planta {
public:
    Roseira();
    Planta* clone() const override;
    void atualizar(Jardim& jardim, int linha, int coluna, int instante) override;
    [[nodiscard]] std::string getTipo() const override;
    [[nodiscard]] char getChar() const override;
};

#endif //POO_TRABALHOPRATICO_ROSEIRA_H