#ifndef POO_TRABALHOPRATICO_TESOURAPODA_H
#define POO_TRABALHOPRATICO_TESOURAPODA_H
#include "Ferramenta.h"

class TesouraPoda : public Ferramenta {
public:
    TesouraPoda();
    bool usar(Posicao& pos) override;
    std::string getTipo() const override;
    char getChar() const override;
    Ferramenta* clone() const override;
};
#endif //POO_TRABALHOPRATICO_TESOURAPODA_H