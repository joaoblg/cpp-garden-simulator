#ifndef POO_TRABALHOPRATICO_POSICAO_H
#define POO_TRABALHOPRATICO_POSICAO_H

class Planta;
class Ferramenta;

class Posicao {
private:
    double agua;
    double nutrientes;
    Planta* planta;
    Ferramenta* ferramenta;

public:
    Posicao();
    Posicao(const Posicao& outra);
    ~Posicao();
    bool isOcupada() const;
    void setPlanta(Planta* p);
    Planta* retirarPlanta();
    Planta* getPlanta() const;
    double getAgua() const;
    void setAgua(double valor);
    double getNutrientes() const;
    void setNutrientes(double valor);
    bool temFerramenta() const;
    void setFerramenta(Ferramenta* f);
    Ferramenta* retirarFerramenta(); // Para quando o jardineiro a apanha
    Ferramenta* getFerramenta() const; // Para ver sem tirar
};

#endif //POO_TRABALHOPRATICO_POSICAO_H
