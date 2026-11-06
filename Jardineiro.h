#ifndef POO_TRABALHOPRATICO_JARDINEIRO_H
#define POO_TRABALHOPRATICO_JARDINEIRO_H

#include <vector>
#include "ferramentas/Ferramenta.h"

class Jardineiro {
private:
    int linha;
    int coluna;
    bool esta_no_jardim;
    std::vector<Ferramenta*> ferramentas_transportadas;
    Ferramenta* ferramenta_na_mao;

public:
    Jardineiro();
    ~Jardineiro();
    void adicionarFerramenta(Ferramenta* f);
    // Métodos de Ação
    void mover(char direcao);
    void entrarNoJardim(int l, int c);
    void sairDoJardim();
    void pegarFerramenta(int numero_serie);
    void largarFerramenta();
    void comprarFerramenta(char tipo);
    void listarFerramentas() const;
    void removerFerramentaAtual();

    // Getters para que outras classes possam saber o estado do Jardineiro
    [[nodiscard]] bool estaNoJardim() const;
    [[nodiscard]] int getLinha() const;
    [[nodiscard]] int getColuna() const;
    [[nodiscard]] Ferramenta* getFerramentaNaMao() const;
};

#endif //POO_TRABALHOPRATICO_JARDINEIRO_H
