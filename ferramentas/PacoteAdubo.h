#ifndef POO_TRABALHOPRATICO_PACOTEADUBO_H
#define POO_TRABALHOPRATICO_PACOTEADUBO_H
#include "Ferramenta.h"

class PacoteAdubo : public Ferramenta {
    int quantidade;
public:
    PacoteAdubo();
    bool usar(Posicao& pos) override;
    std::string getTipo() const override;
    char getChar() const override;
    bool estaVazia() const override;
    Ferramenta* clone() const override;
};
#endif //POO_TRABALHOPRATICO_PACOTEADUBO_H