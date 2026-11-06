#ifndef FLORDEORVALHO_H
#define FLORDEORVALHO_H

#include "Planta.h"
class Posicao; // Forward declaration

class FlorDeOrvalho : public Planta {
private:
    int instantes_vida;
    int instantes_sem_agua{};
public:
    FlorDeOrvalho();
    Planta* clone() const override;
    // Assinatura atualizada
    void atualizar(Jardim& jardim, int linha, int coluna, int instante) override;
    [[nodiscard]] std::string getTipo() const override;
    [[nodiscard]] char getChar() const override;
};

#endif //FLORDEORVALHO_H