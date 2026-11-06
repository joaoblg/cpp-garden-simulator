#ifndef COMANDOAPAGA_H
#define COMANDOAPAGA_H
#include "Comando.h"
#include <string>
#include <sstream>
class ComandoApaga : public Comando {
    std::string nome;
    bool sintaxe_valida;
public:
    explicit ComandoApaga(std::stringstream& ss);
    void executa(Simulador& simulador) const override;
};
#endif //COMANDOAPAGA_H