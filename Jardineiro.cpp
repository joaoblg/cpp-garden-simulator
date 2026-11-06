#include "Jardineiro.h"
#include <iostream>
#include <algorithm> // Para std::find_if, se quiséssemos usar, mas vamos usar for simples

// Includes das ferramentas concretas para a "compra"
#include "ferramentas/Regador.h"
#include "ferramentas/PacoteAdubo.h"
#include "ferramentas/TesouraPoda.h"
#include "ferramentas/PaDeTransplante.h"
#include <algorithm>

Jardineiro::Jardineiro()
    : linha(-1), coluna(-1), esta_no_jardim(false), ferramenta_na_mao(nullptr) {}

Jardineiro::~Jardineiro() {
    // Ao destruir o jardineiro, libertamos a memória de todas as ferramentas que ele tem
    std::cout << "[INFO] Destrutor do Jardineiro: A libertar ferramentas..." << std::endl;
    for (Ferramenta* f : ferramentas_transportadas) {
        delete f;
    }
    ferramentas_transportadas.clear();
}

void Jardineiro::entrarNoJardim(int l, int c) {
    this->linha = l;
    this->coluna = c;
    this->esta_no_jardim = true;
    std::cout << " Jardineiro entrou no jardim." << std::endl;
}

void Jardineiro::sairDoJardim() {
    this->linha = -1;
    this->coluna = -1;
    this->esta_no_jardim = false;
    std::cout << " Jardineiro saiu do jardim." << std::endl;
}

void Jardineiro::mover(char direcao) {
    if (!esta_no_jardim) return;
    switch (direcao) {
        case 'c': linha--; break;
        case 'b': linha++; break;
        case 'e': coluna--; break;
        case 'd': coluna++; break;
        default: ;
    }
}

// --- LÓGICA DE FERRAMENTAS IMPLEMENTADA ---

void Jardineiro::comprarFerramenta(char tipo) {
    Ferramenta* nova = nullptr;

    switch (tipo) {
        case 'r': case 'g': // Aceita 'r' ou 'g' para Regador
            nova = new Regador();
            break;
        case 'a':
            nova = new PacoteAdubo();
            break;
        case 't':
            nova = new TesouraPoda();
            break;
        case 'p': case 'z': // Aceita 'p' ou 'z' para a Pá/FerramentaZ
            nova = new PaDeTransplante();
            break;
        default:
            std::cout << "ERRO: Tipo de ferramenta '" << tipo << "' desconhecido." << std::endl;
            return;
    }

    if (nova != nullptr) {
        ferramentas_transportadas.push_back(nova);
        std::cout << "Jardineiro comprou um(a) " << nova->getTipo()
                  << " (ID: " << nova->getNumeroSerie() << ")." << std::endl;
    }
}

void Jardineiro::pegarFerramenta(int numero_serie) {
    // 1. Verifica se já tem uma na mão
    if (ferramenta_na_mao != nullptr) {
        std::cout << "Aviso: Ja tens uma ferramenta na mao (" << ferramenta_na_mao->getTipo()
                  << "). Usa 'larga' primeiro ou troca direta." << std::endl;
        // No enunciado diz que "muda a ferramenta", por isso vamos simplesmente trocar
    }

    // 2. Procura a ferramenta no inventário
    bool encontrou = false;
    for (Ferramenta* f : ferramentas_transportadas) {
        if (f->getNumeroSerie() == numero_serie) {
            ferramenta_na_mao = f;
            encontrou = true;
            std::cout << "Jardineiro pegou na ferramenta ID " << numero_serie
                      << " (" << f->getTipo() << ")." << std::endl;
            break;
        }
    }

    if (!encontrou) {
        std::cout << "ERRO: Nao tens nenhuma ferramenta com o ID " << numero_serie << "." << std::endl;
    }
}

void Jardineiro::largarFerramenta() {
    if (ferramenta_na_mao != nullptr) {
        std::cout << "Jardineiro guardou a ferramenta " << ferramenta_na_mao->getTipo() << "." << std::endl;
        ferramenta_na_mao = nullptr; // A ferramenta continua no vetor (inventário), só sai da mão
    } else {
        std::cout << "Jardineiro nao tem nada na mao para largar." << std::endl;
    }
}

Ferramenta* Jardineiro::getFerramentaNaMao() const {
    return ferramenta_na_mao;
}

void Jardineiro::listarFerramentas() const {
    std::cout << "\n--- MOCHILA DO JARDINEIRO ---" << std::endl;

    if (ferramenta_na_mao != nullptr) {
        std::cout << "Na Mao: " << ferramenta_na_mao->getTipo()
                  << " (ID: " << ferramenta_na_mao->getNumeroSerie() << ")" << std::endl;
    } else {
        std::cout << "Na Mao: (Vazia)" << std::endl;
    }

    size_t qtdNaMochila = ferramentas_transportadas.size();
    if (ferramenta_na_mao != nullptr) {
        qtdNaMochila--;
    }
    std::cout << "Na Mochila (" << qtdNaMochila << "):" << std::endl;

    if (qtdNaMochila == 0) {
        std::cout << "  (Vazia)" << std::endl;
    } else {
        for (const auto* f : ferramentas_transportadas) {
            if (f != ferramenta_na_mao) {
                std::cout << "  - " << f->getTipo() << " (ID: " << f->getNumeroSerie() << ")" << std::endl;
            }
        }
    }
    std::cout << "-----------------------------" << std::endl;
}
void Jardineiro::adicionarFerramenta(Ferramenta* f) {
    if (f != nullptr) {
        ferramentas_transportadas.push_back(f);
        std::cout << "[AUTO] Apanhaste uma ferramenta do chao: " << f->getTipo()
                  << " (ID: " << f->getNumeroSerie() << ")." << std::endl;
    }
}

void Jardineiro::removerFerramentaAtual() {
    if (ferramenta_na_mao == nullptr) return;

    // Encontra a ferramenta no vetor
    auto it = std::find(ferramentas_transportadas.begin(), ferramentas_transportadas.end(), ferramenta_na_mao);

    if (it != ferramentas_transportadas.end()) {
        delete *it; // Liberta a memória
        ferramentas_transportadas.erase(it); // Remove do vetor
    }

    ferramenta_na_mao = nullptr; // Fica de mãos vazias
    std::cout << "[JARDINEIRO] A ferramenta acabou e foi deitada fora." << std::endl;
}

bool Jardineiro::estaNoJardim() const { return esta_no_jardim; }
int Jardineiro::getLinha() const { return linha; }
int Jardineiro::getColuna() const { return coluna; }