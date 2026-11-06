#ifndef POO_TRABALHOPRATICO_REGADOR_H
#define POO_TRABALHOPRATICO_REGADOR_H
#include "Ferramenta.h"

class Regador : public Ferramenta {
    int capacidade;
public:
    Regador();
    bool usar(Posicao& pos) override; // Override do novo método
    std::string getTipo() const override;
    char getChar() const override;
    bool estaVazia() const override;
    Ferramenta* clone() const override;
};
#endif //POO_TRABALHOPRATICO_REGADOR_H