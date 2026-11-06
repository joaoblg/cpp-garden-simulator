#ifndef COMANDOPLANTA_H
#define COMANDOPLANTA_H
#include "Comando.h"
#include <sstream> // Incluir para receber a stream

class ComandoPlanta : public Comando {
private:
    int linha, coluna;
    char tipo;
    bool sintaxe_valida; // Flag para o resultado da validação

public:
    explicit ComandoPlanta(std::stringstream& ss); // Construtor recebe a stream
    void executa(Simulador& simulador) const override;
};
#endif //COMANDOPLANTA_H