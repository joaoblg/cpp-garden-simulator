#ifndef COMANDORECUPERA_H
#define COMANDORECUPERA_H
#include "Comando.h"
#include <string>
#include <sstream>
class ComandoRecupera : public Comando {
    std::string nome;
    bool sintaxe_valida;
public:
    explicit ComandoRecupera(std::stringstream& ss);
    void executa(Simulador& simulador) const override;
};
#endif //COMANDORECUPERA_H