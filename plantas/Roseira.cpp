#include "Roseira.h"
#include "../Posicao.h"    // Incluir para poder usar os métodos da Posição
#include "../settings.h"
#include "../Jardim.h"
#include <iostream>
#include <algorithm>   // Incluir para usar std::min

Roseira::Roseira() : Planta(BelezaPlanta::BONITA) {
    this->agua_acumulada = Settings::Roseira::inicial_agua;
    this->nutrientes_acumulados = Settings::Roseira::inicial_nutrientes;
}

Planta* Roseira::clone() const {
    return new Roseira(*this); // Usa o construtor de cópia automático do C++
}

void Roseira::atualizar(Jardim& jardim, int linha, int coluna, int instante) {
    Posicao* pos = jardim.getPosicao(linha, coluna);
    // 1. Perda Natural de Recursos [cite: 509]
    this->agua_acumulada -= Settings::Roseira::perda_agua;
    this->nutrientes_acumulados -= Settings::Roseira::perda_nutrientes;

    // 2. Absorção de Recursos do Solo [cite: 510]
    // Água
    double aguaSolo = pos->getAgua();
    double aguaAbsorver = std::min((double)Settings::Roseira::absorcao_agua, aguaSolo);
    pos->setAgua(aguaSolo - aguaAbsorver);
    this->agua_acumulada += aguaAbsorver;

    // Nutrientes
    double nutSolo = pos->getNutrientes();
    double nutAbsorver = std::min((double)Settings::Roseira::absorcao_nutrientes, nutSolo);
    pos->setNutrientes(nutSolo - nutAbsorver);
    this->nutrientes_acumulados += nutAbsorver;

    // 3. Verificar Morte [cite: 512, 513]
    if (this->agua_acumulada <= 0 ||
        this->nutrientes_acumulados <= 0 ||
        this->nutrientes_acumulados >= Settings::Roseira::morre_nutrientes_maior)
    {
        std::cout << "[Instante " << instante << "] INFO: Uma Roseira morreu devido as condicoes do solo." << std::endl;
        // Devolve metade do que tinha ao solo
        pos->setAgua(pos->getAgua() + (this->agua_acumulada / 2.0));
        pos->setNutrientes(pos->getNutrientes() + (this->nutrientes_acumulados / 2.0));

        pos->setPlanta(nullptr); // Morre
        return;
    }
    // --- LÓGICA DE MULTIPLICAÇÃO ---
    // Regra: Nutrientes > 100
    if (this->nutrientes_acumulados > Settings::Roseira::multiplica_nutrientes_maior) {
        
        int dL[] = {-1, 1, 0, 0};
        int dC[] = {0, 0, -1, 1};

        for (int i = 0; i < 4; ++i) {
            int vizL = linha + dL[i];
            int vizC = coluna + dC[i];

            if (jardim.isPosicaoValida(vizL, vizC)) {
                Posicao* vizinho = jardim.getPosicao(vizL, vizC);
                if (!vizinho->isOcupada()) {
                    auto* filho = new Roseira();

                    // Regras específicas de nascimento da Roseira
                    filho->nutrientes_acumulados = Settings::Roseira::nova_nutrientes;
                    filho->agua_acumulada = this->agua_acumulada * (Settings::Roseira::nova_agua_percentagem / 100.0);

                    // Regras de custo para a Mãe
                    this->nutrientes_acumulados = Settings::Roseira::original_nutrientes; // Reset para 100? Verificar enunciado.
                    // O enunciado diz: "A roseira original fica com 100 unidades de nutrientes"
                    this->agua_acumulada = this->agua_acumulada * (Settings::Roseira::original_agua_percentagem / 100.0);

                    vizinho->setPlanta(filho);
                    std::cout << "INFO: Uma Roseira multiplicou-se para (" << vizL << "," << vizC << ")!" << std::endl;
                    break;
                }
            }
        }
    }
}

std::string Roseira::getTipo() const {
    return "Roseira";
}

char Roseira::getChar() const {
    return 'r';
}