#ifndef COMANDOLSOLO_H
#define COMANDOLSOLO_H
#include "Comando.h"
#include <sstream>
class ComandoLSolo : public Comando {
    int linha, coluna, raio;
    bool sintaxe_valida;
public:
    explicit ComandoLSolo(std::stringstream& ss);
    void executa(Simulador& simulador) const override;
};
#endif //COMANDOLSOLO_H