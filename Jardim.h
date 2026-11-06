#ifndef POO_TRABALHOPRATICO_JARDIM_H
#define POO_TRABALHOPRATICO_JARDIM_H
#include "Posicao.h"

class Jardineiro; // Forward Declaration

class Jardim {
private:
    int linhas;
    int colunas;
    Posicao** grelha;
public:
    Jardim(int linhas, int colunas);
    Jardim(const Jardim& outro);
    ~Jardim();
    void mostrar(const Jardineiro* jardineiro) const;
    [[nodiscard]] bool isPosicaoValida(int linha, int coluna) const;
    [[nodiscard]] bool plantar(int linha, int coluna, char tipo) const;
    [[nodiscard]] Posicao* getPosicao(int linha, int coluna) const;
    [[nodiscard]] int getLinhas() const;
    [[nodiscard]] int getColunas() const;
};
#endif //POO_TRABALHOPRATICO_JARDIM_H