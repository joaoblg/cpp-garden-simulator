#ifndef POO_TRABALHOPRATICO_PADETRANSPLANTE_H
#define POO_TRABALHOPRATICO_PADETRANSPLANTE_H

#include "Ferramenta.h"
class Planta; // Forward declaration

class PaDeTransplante : public Ferramenta {
private:
    // A pá pode carregar uma planta (ponteiro)
    Planta* planta_carregada;

public:
    PaDeTransplante();
    // Não esquecer o destrutor para limpar a planta se ela ficar na pá
    ~PaDeTransplante() override;
    bool usar(Posicao& pos) override;
    std::string getTipo() const override;
    char getChar() const override;
    Ferramenta* clone() const override;
};

#endif //POO_TRABALHOPRATICO_PADETRANSPLANTE_H
