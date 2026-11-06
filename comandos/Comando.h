#ifndef POO_TRABALHOPRATICO_COMANDO_H
#define POO_TRABALHOPRATICO_COMANDO_H
#include <string>
class Simulador;
class Comando {
public:
    virtual ~Comando() = default;
    virtual void executa(Simulador& simulador) const = 0;
};
#endif //POO_TRABALHOPRATICO_COMANDO_H