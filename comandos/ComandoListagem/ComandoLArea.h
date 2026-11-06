#ifndef COMANDOLAREA_H
#define COMANDOLAREA_H
#include "Comando.h"
#include <sstream>
class ComandoLArea : public Comando {
    bool sintaxe_valida;
public:
    explicit ComandoLArea(std::stringstream& ss);
    void executa(Simulador& simulador) const override;
};
#endif //COMANDOLAREA_H