#include "Jardim.h"
#include <iostream>
#include <cctype>
#include "Jardineiro.h"
#include "plantas/Planta.h"
#include "plantas/Cato.h"
#include "plantas/Roseira.h"
#include "plantas/ErvaDaninha.h"
#include "plantas/FlorDeOrvalho.h"
//constroi primeiro um array de ponteiros para posiçao(como se fossem portas)e dps  criamos os corredors
// que já alocam objetos posicao reais
Jardim::Jardim(int l, int c) : linhas(l), colunas(c), grelha(nullptr) {
    grelha = new Posicao*[linhas];
    for (int i = 0; i < linhas; ++i) grelha[i] = new Posicao[colunas];
}
// Construtor de Cópia
// Jardim.cpp

Jardim::Jardim(const Jardim& outro) : linhas(outro.linhas), colunas(outro.colunas) {
    grelha = new Posicao*[linhas];
    for (int i = 0; i < linhas; ++i) {
        grelha[i] = new Posicao[colunas];
    }

    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            Posicao* original = &outro.grelha[i][j];
            Posicao* copia = &this->grelha[i][j];
            copia->setAgua(original->getAgua());
            copia->setNutrientes(original->getNutrientes());
            // Copia Planta
            if (original->getPlanta()) {
                copia->setPlanta(original->getPlanta()->clone());
            }
            if (original->temFerramenta()) {
                copia->setFerramenta(original->getFerramenta()->clone());
            }
        }
    }
}
//apagar primeiro colunas e dps linhas para evitar fugas(inverso)
Jardim::~Jardim() {
    for (int i = 0; i < linhas; ++i) delete[] grelha[i];
    delete[] grelha;
    std::cout << "Destrutor do Jardim: Grelha de posicoes libertada." << std::endl;
}
//metodo de classe jardim chamado mostrar e n devolve valores (void)
// recebe um ponteiro para o jardineiro,para saber onde o desenhar
// const significa que promete nao alterar o objeto jardineiro nem o jardim
void Jardim::mostrar(const Jardineiro* jardineiro) const {
    std::cout << "\n--- JARDIM ---" << std::endl;
    std::cout << "  ";
    for (int j = 0; j < colunas; ++j) {
        std::cout << static_cast<char>('A' + j) << " ";
    }
    std::cout << std::endl;

    for (int i = 0; i < linhas; ++i) {
        std::cout << static_cast<char>('A' + i) << " ";
        for (int j = 0; j < colunas; ++j) {
            if (jardineiro && jardineiro->estaNoJardim() && jardineiro->getLinha() == i && jardineiro->getColuna() == j) {
                std::cout << "* "; 
            } else {
                Posicao* pos = getPosicao(i, j);
                if (pos && pos->getPlanta() != nullptr) {
                    std::cout << pos->getPlanta()->getChar() << " ";
                }
                else if (pos && pos->temFerramenta()) {
                    std::cout << pos->getFerramenta()->getChar() << " ";
                }
                else {
                    std::cout << ". ";
                }
            }
        }
        std::cout << std::endl;
    }
    std::cout << "--------------" << std::endl;
}

bool Jardim::isPosicaoValida(int l, int c) const {
    return l >= 0 && l < linhas && c >= 0 && c < colunas;
}

Posicao* Jardim::getPosicao(int l, int c) const {
    if (isPosicaoValida(l, c)) return &grelha[l][c];
    return nullptr;
}

bool Jardim::plantar(int l, int c, char t) const {
    Posicao* pos = getPosicao(l, c);
    if (!pos) { return false; }
    if (pos->isOcupada()) {
        std::cout << "ERRO: A posicao ja esta ocupada." << std::endl;
        return false;
    }
    Planta* novaPlanta = nullptr;
    switch (tolower(t)) {
        case 'c': novaPlanta = new Cato(); break;
        case 'r': novaPlanta = new Roseira(); break;
        case 'e': novaPlanta = new ErvaDaninha(); break;
        case 'x': novaPlanta = new FlorDeOrvalho(); break;
        default:
            std::cout << "ERRO: Tipo de planta '" << t << "' desconhecido." << std::endl;
            return false;
    }
    pos->setPlanta(novaPlanta);
    return true;
}

int Jardim::getLinhas() const { return linhas; }
int Jardim::getColunas() const { return colunas; }