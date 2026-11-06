#ifndef POO_TRABALHOPRATICO_PLANTA_H
#define POO_TRABALHOPRATICO_PLANTA_H

#include <string>

// Forward declarations
class Jardim;

class Planta {
protected:
    int saude;
    double agua_acumulada;
    double nutrientes_acumulados;

    // Atributo de beleza
    enum class BelezaPlanta { FEIA, NEUTRA, BONITA } beleza;

public:
    // Precisamos de expor o enum para ser usado fora
    using Beleza = BelezaPlanta;
    virtual Planta* clone() const = 0;
    Planta(Beleza beleza);
    virtual ~Planta();

    // --- ALTERAÇÃO CRUCIAL AQUI ---
    // A planta agora recebe o Jardim e as suas coordenadas para poder ver os vizinhos
    virtual void atualizar(Jardim& jardim, int linha, int coluna, int instante) = 0;

    virtual std::string getTipo() const = 0;
    virtual char getChar() const = 0;
    virtual std::string getInfo() const;
    Beleza getBeleza() const;
};
#endif //POO_TRABALHOPRATICO_PLANTA_H