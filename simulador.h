#ifndef POO_TRABALHOPRATICO_SIMULADOR_H
#define POO_TRABALHOPRATICO_SIMULADOR_H

#include <string>
#include <vector>

class Jardim;
class Jardineiro;
class Comando;
struct CopiaJardim {
    std::string nome;
    Jardim* jardim;
};

class Simulador {
public:
    Simulador();
    ~Simulador();
    void iniciar();
    void criaJardim(int linhas, int colunas);
    void tentaPlantar(int linha, int coluna, char tipo);
    void tentaColher(int linha, int coluna);
    int getMovimentosNesteTurno() const;
    void incrementarMovimentos();
    void colocarFerramentaAleatoria();
    void avancarTurno(int n);
    void listarPlantas() const;
    void listarFerramentasJardineiro() const;
    void listarArea() const;
    void listarSolo(int linha, int coluna, int raio = -1) const;
    void redesenharJardim() const;
    void executarLinha(const std::string& linha);
    Jardineiro* getJardineiro() const;
    Jardim* getJardim() const;
    void gravarJardim(const std::string& nome);
    void recuperarJardim(const std::string& nome);
    void apagarJardim(const std::string& nome);
    void verificarFerramentasNoChao();
    int getEntradasSaidasTurno() const;
    void incrementarEntradasSaidas();

private:
    Comando* interpretaComando(const std::string& linha) const;
    bool jardimCriado;
    Jardim* jardim;
    Jardineiro* jardineiro;
    int plantas_plantadas_neste_turno;
    int plantas_colhidas_neste_turno;
    std::vector<CopiaJardim> copias;
    int movimentos_neste_turno;
    int entradas_saidas_neste_turno;
};

#endif //POO_TRABALHOPRATICO_SIMULADOR_H