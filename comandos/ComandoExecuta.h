#ifndef COMANDOEXECUTA_H
#define COMANDOEXECUTA_H
#include "Comando.h"
#include <string>
#include <sstream>

class ComandoExecuta : public Comando {
    std::string nomeFicheiro;
    bool sintaxe_valida;
public:
    explicit ComandoExecuta(std::stringstream& ss);
    void executa(Simulador& simulador) const override;
};
#endif //COMANDOEXECUTA_H