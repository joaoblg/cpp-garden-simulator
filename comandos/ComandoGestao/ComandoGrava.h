#ifndef COMANDOGRAVA_H
#define COMANDOGRAVA_H
#include "Comando.h"
#include <string>
#include <sstream>
class ComandoGrava : public Comando {
    std::string nome;
    bool sintaxe_valida;
public:
    explicit ComandoGrava(std::stringstream& ss);
    void executa(Simulador& simulador) const override;
};
#endif //COMANDOGRAVA_H