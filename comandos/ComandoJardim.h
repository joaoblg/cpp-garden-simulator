#ifndef COMANDOJARDIM_H
#define COMANDOJARDIM_H
#include "Comando.h"
#include <sstream>
class ComandoJardim : public Comando {
    int linhas, colunas;
    bool sintaxe_valida;
public:
    explicit ComandoJardim(std::stringstream& ss);
    void executa(Simulador& simulador) const override;
};
#endif //COMANDOJARDIM_H