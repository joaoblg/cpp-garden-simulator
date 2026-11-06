#include "simulador.h"
#include "Jardim.h"
#include "Jardineiro.h"
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include "settings.h"
#include "Posicao.h"
#include "plantas/Planta.h"
#include "comandos/Comando.h"
#include "comandos/ComandoJardim.h"
#include "comandos/ComandoExecuta.h"
#include "comandos/ComandoAvanca.h"
#include "comandos/ComandoAcoes/ComandoPlanta.h"
#include "comandos/ComandoAcoes/ComandoColhe.h"
#include "comandos/ComandoListagem/ComandoLPlantas.h"
#include "comandos/ComandoListagem/ComandoLPlanta.h"
#include "comandos/ComandoListagem/ComandoLArea.h"
#include "comandos/ComandoListagem/ComandoLSolo.h"
#include "comandos/ComandoListagem/ComandoLFerr.h"
#include "comandos/ComandoMove.h"
#include "comandos/ComandoAcoes/ComandoEntra.h"
#include "comandos/ComandoAcoes/ComandoSai.h"
#include "comandos/ComandoAcoes/ComandoPega.h"
#include "comandos/ComandoAcoes/ComandoLarga.h"
#include "comandos/ComandoAcoes/ComandoCompra.h"
#include "comandos/ComandoGestao/ComandoGrava.h"
#include "comandos/ComandoGestao/ComandoRecupera.h"
#include "comandos/ComandoGestao/ComandoApaga.h"
#include "ferramentas/Regador.h"
#include "ferramentas/PacoteAdubo.h"
#include "ferramentas/TesouraPoda.h"
#include "ferramentas/PaDeTransplante.h"

Simulador::Simulador() : jardimCriado(false), jardim(nullptr), jardineiro(new Jardineiro()),
plantas_plantadas_neste_turno(0), plantas_colhidas_neste_turno(0), movimentos_neste_turno(0),
entradas_saidas_neste_turno(0){}

Simulador::~Simulador() {
    delete jardim;
    delete jardineiro;
    for (auto& copia : copias) {
        delete copia.jardim;
    }
    std::cout << "Destrutor do Simulador: Memoria do Jardim e do Jardineiro libertada." << std::endl;
}

void Simulador::iniciar() {
    std::string linha;
    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, linha) || linha == "fim") break;
        executarLinha(linha);
    }
}

void Simulador::executarLinha(const std::string& linha) {
    if (linha.empty()) return;
    Comando* cmd = interpretaComando(linha);
    if (cmd != nullptr) {
        cmd->executa(*this);
        delete cmd;
    }
}

Comando* Simulador::interpretaComando(const std::string& linha) const {
    std::stringstream ss(linha);
    std::string nomeCmd;
    ss >> nomeCmd;
    // A fábrica só lê o nome e passa a 'stream' para o construtor do comando.
    // O próprio comando é que se vai validar.
    if (nomeCmd == "jardim") return new ComandoJardim(ss);
    if (nomeCmd == "executa") return new ComandoExecuta(ss);
    // Bloco de guarda para comandos que precisam do jardim
    if (!jardimCriado) {
        if (nomeCmd != "fim")
            std::cout << "ERRO: O jardim ainda nao foi criado." << std::endl;
        return nullptr;
    }
    if (nomeCmd == "avanca") return new ComandoAvanca(ss);
    if (nomeCmd == "lplantas") return new ComandoLPlantas(ss);
    if (nomeCmd == "lplanta") return new ComandoLPlanta(ss);
    if (nomeCmd == "larea") return new ComandoLArea(ss);
    if (nomeCmd == "lsolo") return new ComandoLSolo(ss);
    if (nomeCmd == "lferr") return new ComandoLFerr(ss);
    if (nomeCmd == "colhe") return new ComandoColhe(ss);
    if (nomeCmd == "planta") return new ComandoPlanta(ss);
    if (nomeCmd == "larga") return new ComandoLarga(ss);
    if (nomeCmd == "pega") return new ComandoPega(ss);
    if (nomeCmd == "compra") return new ComandoCompra(ss);
    if (nomeCmd == "c" || nomeCmd == "b" || nomeCmd == "e" || nomeCmd == "d") {
        // Exceção: O ComandoMove é tão simples que podemos manter a lógica antiga
        // para evitar passar-lhe a stream.
        std::string lixo;
        if (!(ss >> lixo)) return new ComandoMove(nomeCmd[0]);
    }
    if (nomeCmd == "entra") return new ComandoEntra(ss);
    if (nomeCmd == "sai") return new ComandoSai(ss);
    if (nomeCmd == "grava") return new ComandoGrava(ss);
    if (nomeCmd == "recupera") return new ComandoRecupera(ss);
    if (nomeCmd == "apaga") return new ComandoApaga(ss);
    std::cout << "Comando '" << nomeCmd << "' desconhecido." << std::endl;
    return nullptr;
}

void Simulador::criaJardim(int linhas, int colunas) {
    if (jardimCriado) {
        std::cout << "ERRO: O jardim ja foi criado." << std::endl;
        return;
    }
    if (linhas > 0 && colunas > 0 && linhas <= 26 && colunas <= 26) {
        jardim = new Jardim(linhas, colunas);
        jardimCriado = true;
        for (int i = 0; i < 3; ++i) {
            colocarFerramentaAleatoria();
        }
        redesenharJardim();
    } else {
        std::cout << "INVALIDO: Dimensoes do jardim invalidas." << std::endl;
    }
}

void Simulador::tentaPlantar(int linha, int coluna, char tipo) {
    if (!jardim) return;

    if (!jardineiro->estaNoJardim()) {
        std::cout << "ERRO: O jardineiro tem de estar no jardim para poder plantar." << std::endl;
        return;
    }

    if (plantas_plantadas_neste_turno >= Settings::Jardineiro::max_plantacoes) {
        std::cout << "ERRO: Ja plantou o maximo de " << Settings::Jardineiro::max_plantacoes << " plantas neste turno." << std::endl;
        return;
    }

    // Tenta plantar e se for bem-sucedido...
    if (jardim->plantar(linha, coluna, tipo)) {
        plantas_plantadas_neste_turno++; // ...atualiza o contador...
        std::cout << "Planta do tipo '" << tipo << "' plantada com sucesso." << std::endl;
        redesenharJardim();
    }
}

void Simulador::tentaColher(int linha, int coluna) {
    if (!jardim) return;

    //verificar o limite de 5 colheitas por turno
    if (plantas_colhidas_neste_turno >= Settings::Jardineiro::max_colheitas) {
        std::cout << "ERRO: Ja colheu o maximo de " << Settings::Jardineiro::max_colheitas
                  << " plantas neste turno." << std::endl;
        return;
    }
    //verificar se existe planta na posição
    Posicao* pos = jardim->getPosicao(linha, coluna);
    if (pos && pos->getPlanta() != nullptr) {
        //guarda o nome para mostrar na mensagem
        std::string nomePlanta = pos->getPlanta()->getTipo();
        //ação de colher: remove a planta (o setPlanta(nullptr) apaga-a da memória)
        pos->setPlanta(nullptr);
        //atualizar contador e ecrã
        plantas_colhidas_neste_turno++;
        std::cout << "Sucesso: Colheu uma " << nomePlanta << " na posicao "
                  << static_cast<char>('a' + linha) << static_cast<char>('a' + coluna) << "." << std::endl;
        redesenharJardim();
    } else {
        std::cout << "ERRO: Nao ha nenhuma planta nessa posicao para colher." << std::endl;
    }
}

void Simulador::avancarTurno(int n) {
    if (!jardim) return;
    std::cout << "A avancar " << n << " turno(s)..." << std::endl;
    for (int i = 0; i < n; ++i) {
        int instanteAtual = i + 1;
        std::cout << "--- Instante " << instanteAtual << "/" << n << " ---" << std::endl;
        //FAZ AS PLANTAS AGIREM
        for (int l = 0; l < jardim->getLinhas(); ++l) {
            for (int c = 0; c < jardim->getColunas(); ++c) {
                Posicao* pos = jardim->getPosicao(l, c);
                if (pos && pos->getPlanta()) {
                    pos->getPlanta()->atualizar(*jardim, l, c, instanteAtual);
                }
            }
        }
        // 2. FAZER A FERRAMENTA ATIVA AGIR
        // Verifica se o jardineiro está no jardim e tem uma ferramenta
        if (jardineiro->estaNoJardim()) {
            Ferramenta* fer = jardineiro->getFerramentaNaMao();
            if (fer != nullptr) {
                // Obtém a posição onde o jardineiro está
                Posicao* posJardineiro = jardim->getPosicao(jardineiro->getLinha(), jardineiro->getColuna());
                if (posJardineiro) {
                    // Usa a ferramenta nessa posição
                    fer->usar(*posJardineiro);
                    if (fer->estaVazia()) {
                        jardineiro->removerFerramentaAtual();
                    }
                }
            }
        }
    }

    plantas_plantadas_neste_turno = 0;
    plantas_colhidas_neste_turno = 0;
    movimentos_neste_turno = 0;
    entradas_saidas_neste_turno = 0;
    std::cout << "Contadores de acoes por turno foram reiniciados." << std::endl;
    redesenharJardim();
}

void Simulador::listarSolo(int linha, int coluna, int raio) const {
    if (!jardim) return;

    // Se o raio for negativo (não especificado), mostra só a posição central (comportamento original)
    if (raio < 0) {
        Posicao* pos = jardim->getPosicao(linha, coluna);
        if (!pos) return;

        char l = static_cast<char>('a' + linha);
        char c = static_cast<char>('a' + coluna);

        // (O teu código de mostrar detalhes que já tinhas vai aqui)
        std::cout << "Posicao [" << l << c << "]: ";
        std::cout << "Agua: " << pos->getAgua() << " | Nutr: " << pos->getNutrientes();
        if (pos->getPlanta()) {
            std::cout << " | " << pos->getPlanta()->getInfo();
        } else {
            std::cout << " | (Sem planta)";
        }
        if (pos->temFerramenta()) {
            std::cout << " | Tem Ferramenta: " << pos->getFerramenta()->getTipo();
        }else {
            std::cout << " | (Sem Ferramenta)";
        }
        std::cout << std::endl;
        return;
    }

    // Lógica para o Quadrado de Raio N
    std::cout << "\n--- AREA DO SOLO (Centro: " << static_cast<char>('a'+linha)
              << static_cast<char>('a'+coluna) << ", Raio: " << raio << ") ---" << std::endl;

    int inicioL = linha - raio;
    int fimL = linha + raio;
    int inicioC = coluna - raio;
    int fimC = coluna + raio;

    for (int i = inicioL; i <= fimL; ++i) {
        for (int j = inicioC; j <= fimC; ++j) {
            // Verifica se esta coordenada está dentro do jardim
            if (jardim->isPosicaoValida(i, j)) {
                // Chama a si mesmo recursivamente, mas com raio -1 para imprimir só a linha
                listarSolo(i, j, -1);
            }
        }
    }
    std::cout << "---------------------------------------------------------" << std::endl;
}

void Simulador::listarPlantas() const {
    if (!jardim) return;
    std::cout << "\n--- LISTA DE PLANTAS NO JARDIM ---" << std::endl;
    for (int i = 0; i < jardim->getLinhas(); ++i) {
        for (int j = 0; j < jardim->getColunas(); ++j) {
            Posicao* pos = jardim->getPosicao(i, j);
            if (pos && pos->getPlanta()) {
                std::cout << "Posicao [" << static_cast<char>('a' + i) << static_cast<char>('a' + j) << "]: "
                          << pos->getPlanta()->getInfo() << std::endl;
            }
        }
    }
    std::cout << "------------------------------------" << std::endl;
}

void Simulador::listarArea() const {
    if (!jardim) return;
    std::cout << "\n--- LISTAGEM DA AREA (POSICOES NAO VAZIAS) ---" << std::endl;

    bool encontrouAlguma = false;
    for (int i = 0; i < jardim->getLinhas(); ++i) {
        for (int j = 0; j < jardim->getColunas(); ++j) {
            Posicao* pos = jardim->getPosicao(i, j);
            if (pos && (pos->isOcupada() || pos->temFerramenta())) {
                listarSolo(i, j);
                encontrouAlguma = true;
            }
        }
    }

    if (!encontrouAlguma) {
        std::cout << "O jardim esta vazio de plantas." << std::endl;
    }
    std::cout << "----------------------------------------------" << std::endl;
}

void Simulador::listarFerramentasJardineiro() const {
    if (jardineiro) {
        jardineiro->listarFerramentas();
    }
}

void Simulador::redesenharJardim() const {
    if(jardim){
        jardim->mostrar(jardineiro);
    }
}

Jardineiro* Simulador::getJardineiro() const {
    return jardineiro;
}

Jardim* Simulador::getJardim() const {
    return jardim;
}

void Simulador::gravarJardim(const std::string& nome) {
    if (!jardim) {
        std::cout << "ERRO: Nao ha jardim para gravar." << std::endl;
        return;
    }

    // Verifica se já existe e substitui, ou cria novo
    for (auto& copia : copias) {
        if (copia.nome == nome) {
            delete copia.jardim; // Apaga o antigo
            copia.jardim = new Jardim(*jardim); // Cria cópia profunda do atual
            std::cout << "Jogo gravado com sucesso (substituiu anterior): " << nome << std::endl;
            return;
        }
    }

    // Se não existe, cria nova entrada
    copias.push_back({nome, new Jardim(*jardim)});
    std::cout << "Jogo gravado com sucesso: " << nome << std::endl;
}

void Simulador::recuperarJardim(const std::string& nome) {
    for (auto it = copias.begin(); it != copias.end(); ++it) {
        if (it->nome == nome) {
            delete jardim; // Apaga o jardim atual
            jardim = it->jardim; // Recupera o guardado

            // Remove da lista de cópias (o enunciado diz "A cópia é eliminada")
            copias.erase(it);

            std::cout << "Jogo recuperado com sucesso: " << nome << std::endl;
            redesenharJardim();
            return;
        }
    }
    std::cout << "ERRO: Nao existe nenhuma gravacao com o nome '" << nome << "'." << std::endl;
}

void Simulador::apagarJardim(const std::string& nome) {
    for (auto it = copias.begin(); it != copias.end(); ++it) {
        if (it->nome == nome) {
            delete it->jardim; // Liberta a memória
            copias.erase(it);  // Remove do vetor
            std::cout << "Gravacao apagada: " << nome << std::endl;
            return;
        }
    }
    std::cout << "ERRO: Gravacao nao encontrada." << std::endl;
}
int Simulador::getMovimentosNesteTurno() const {
    return movimentos_neste_turno;
}

void Simulador::incrementarMovimentos() {
    movimentos_neste_turno++;
}
void Simulador::colocarFerramentaAleatoria() {
    if (!jardim) return;
    // Gerador aleatório
    static std::random_device rd;
    static std::mt19937 gen(rd());
    // 1. Escolher Tipo Aleatório (0-3)
    std::uniform_int_distribution<> distTipo(0, 3);
    Ferramenta* nova = nullptr;
    switch (distTipo(gen)) {
        case 0: nova = new Regador(); break;
        case 1: nova = new PacoteAdubo(); break;
        case 2: nova = new TesouraPoda(); break;
        case 3: nova = new PaDeTransplante(); break;
        default: ;
    }
    // 2. Escolher Posição Aleatória Livre
    // (Tentamos algumas vezes encontrar um sítio vazio de ferramentas)
    std::uniform_int_distribution<> distL(0, jardim->getLinhas() - 1);
    std::uniform_int_distribution<> distC(0, jardim->getColunas() - 1);
    for (int k = 0; k < 100; ++k) { // Tenta 100 vezes antes de desistir (evita loop infinito se jardim cheio)
        int l = distL(gen);
        int c = distC(gen);
        Posicao* pos = jardim->getPosicao(l, c);
        if (pos && !pos->temFerramenta()) {
            pos->setFerramenta(nova);
            // (Opcional: std::cout << "Debug: Ferramenta criada em " << l << " " << c << std::endl;)
            return;
        }
    }
    // Se não encontrou lugar, limpa a memória
    delete nova;
}
void Simulador::verificarFerramentasNoChao() {
    if (!jardim || !jardineiro->estaNoJardim()) return;
    // Onde está o jardineiro?
    int l = jardineiro->getLinha();
    int c = jardineiro->getColuna();
    Posicao* pos = jardim->getPosicao(l, c);
    // Há ferramenta aqui?
    if (pos && pos->temFerramenta()) {
        // 1. Retirar do chão (a Posição deixa de a ter)
        Ferramenta* f = pos->retirarFerramenta();
        // 2. Dar ao jardineiro (o Jardineiro passa a tê-la)
        jardineiro->adicionarFerramenta(f);
        // 3. A Magia: Criar outra noutro lado
        colocarFerramentaAleatoria();
        std::cout << "[MAGIA] Como apanhaste uma ferramenta, outra apareceu noutro lugar do jardim!" << std::endl;
    }

}
int Simulador::getEntradasSaidasTurno() const {
    return entradas_saidas_neste_turno;
}

void Simulador::incrementarEntradasSaidas() {
    entradas_saidas_neste_turno++;
}


