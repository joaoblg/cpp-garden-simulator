#ifndef POO_TRABALHOPRATICO_FERRAMENTA_H
#define POO_TRABALHOPRATICO_FERRAMENTA_H

#include <string>

class Posicao;

class Ferramenta {
protected:
    int numero_serie;
    static int proximo_numero_serie;

public:
    Ferramenta();
    virtual ~Ferramenta() = default;
    virtual Ferramenta* clone() const = 0;
    virtual bool usar(Posicao& pos) = 0;
    virtual std::string getTipo() const = 0;
    virtual char getChar() const = 0;
    virtual bool estaVazia() const { return false; } // Por defeito não gasta (Tesoura, Pá)
    int getNumeroSerie() const;
};

#endif //POO_TRABALHOPRATICO_FERRAMENTA_H