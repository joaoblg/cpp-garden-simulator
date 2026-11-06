#ifndef COMANDOMOVE_H
#define COMANDOMOVE_H
#include "Comando.h"
class ComandoMove : public Comando {
    char direcao;
public:
    ComandoMove(char dir);
    void executa(Simulador& simulador) const override;
};
#endif //COMANDOMOVE_H
