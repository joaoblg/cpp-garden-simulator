#include "ErvaDaninha.h"
#include "../Posicao.h"
#include "../settings.h"
#include "../Jardim.h"
#include <iostream>
#include <algorithm> // Para std::min

ErvaDaninha::ErvaDaninha() : Planta(BelezaPlanta::FEIA), instantes_vida(0) {
    this->agua_acumulada = Settings::ErvaDaninha::inicial_agua;
    this->nutrientes_acumulados = Settings::ErvaDaninha::inicial_nutrientes;
}

Planta* ErvaDaninha::clone() const {
    return new ErvaDaninha(*this); // Usa o construtor de cópia automático do C++
}

void ErvaDaninha::atualizar(Jardim& jardim, int linha, int coluna, int instante) {
    Posicao* pos = jardim.getPosicao(linha, coluna);    this->instantes_vida++;

    // 1. Verificar Morte por Velhice [cite: 524]
    if (this->instantes_vida >= Settings::ErvaDaninha::morre_instantes) {
std::cout << "[Instante " << instante << "] INFO: Uma Erva Daninha morreu de velhice." << std::endl;
        pos->setPlanta(nullptr); // Morre
        return;
    }

    // 2. Absorver Água (1 unidade) [cite: 523]
    double aguaSolo = pos->getAgua();
    double aguaAbsorver = std::min((double)Settings::ErvaDaninha::absorcao_agua, aguaSolo);
    pos->setAgua(aguaSolo - aguaAbsorver);
    this->agua_acumulada += aguaAbsorver;

    // 3. Absorver Nutrientes (1 unidade) [cite: 524]
    double nutSolo = pos->getNutrientes();
    double nutAbsorver = std::min((double)Settings::ErvaDaninha::absorcao_nutrientes, nutSolo);
    pos->setNutrientes(nutSolo - nutAbsorver);
    this->nutrientes_acumulados += nutAbsorver;

    this->contador_multiplicacao++;

    // --- LÓGICA DE MULTIPLICAÇÃO ---
    // Regra: Nutrientes > 30 E passaram 5 instantes
    if (this->nutrientes_acumulados > Settings::ErvaDaninha::multiplica_nutrientes_maior &&
        this->contador_multiplicacao >= Settings::ErvaDaninha::multiplica_instantes)
    {
        int dL[] = {-1, 1, 0, 0};
        int dC[] = {0, 0, -1, 1};

        // A Erva Daninha é agressiva: tenta invadir!
        for (int i = 0; i < 4; ++i) {
            int vizL = linha + dL[i];
            int vizC = coluna + dC[i];

            if (jardim.isPosicaoValida(vizL, vizC)) {
                Posicao* vizinho = jardim.getPosicao(vizL, vizC);

                // Pode ocupar se estiver vazia OU se tiver uma planta (mata-a!)
                // Nota: O setPlanta já faz o delete da planta anterior automaticamente.
                auto* filho = new ErvaDaninha();

                // Filho nasce com 5 e 5
                filho->agua_acumulada = Settings::ErvaDaninha::nova_nutrientes; // Assumindo igual para agua
                filho->nutrientes_acumulados = Settings::ErvaDaninha::nova_nutrientes;

                vizinho->setPlanta(filho);

                // Reset do cooldown da mãe
                this->contador_multiplicacao = 0;
                std::cout << "INFO: Uma Erva Daninha invadiu (" << vizL << "," << vizC << ")!" << std::endl;
                break;
            }
        }
    }
}

std::string ErvaDaninha::getTipo() const {
    return "ErvaDaninha";
}

char ErvaDaninha::getChar() const {
    return 'e';
}
