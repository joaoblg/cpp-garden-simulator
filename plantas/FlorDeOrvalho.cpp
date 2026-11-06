#include "FlorDeOrvalho.h"
#include "../Posicao.h" // Ajusta o caminho conforme a tua estrutura de pastas
#include "../Settings.h"
#include "../Jardim.h"
#include <iostream>
#include <algorithm>

FlorDeOrvalho::FlorDeOrvalho()
    : Planta(BelezaPlanta::NEUTRA), // Beleza Neutra
      instantes_vida(0),
      instantes_sem_agua(0)
{}

Planta* FlorDeOrvalho::clone() const {
    return new FlorDeOrvalho(*this); // Usa o construtor de cópia automático do C++
}

void FlorDeOrvalho::atualizar(Jardim& jardim, int linha, int coluna, int instante) {
    // Obter a posição atual
    Posicao* pos = jardim.getPosicao(linha, coluna);
    if (!pos) return; // Segurança
    this->instantes_vida++;

    // --- 1. VERIFICAR CONDIÇÕES DE MORTE ---

    // Verifica seca (água no solo <= 0)
    if (pos->getAgua() <= 0.0) {
        this->instantes_sem_agua++;
    } else {
        this->instantes_sem_agua = 0; // Reset se houver água
    }

    // Se atingiu o limite de vida OU o limite de seca -> MORRE
    if (this->instantes_vida >= Settings::FlorDeOrvalho::TEMPO_VIDA_MAX ||
        this->instantes_sem_agua >= Settings::FlorDeOrvalho::MAX_INSTANTES_SEM_AGUA)
    {
        std::cout << "[Instante " << instante <<"] INFO: Uma Flor-de-Orvalho morreu e enriqueceu o solo!" << std::endl;

        // Bónus de Morte: Devolve muitos recursos ao solo
        pos->setAgua(pos->getAgua() + Settings::FlorDeOrvalho::BONUS_AGUA_MORTE);
        pos->setNutrientes(pos->getNutrientes() + Settings::FlorDeOrvalho::BONUS_NUTRIENTES_MORTE);

        pos->setPlanta(nullptr); // Remove-se a si própria
        return; // Pára a execução
    }

    // --- 2. REGRA ESPECIAL: REGENERAÇÃO ---
    // Se estiver "doente" e o solo for rico, cura-se consumindo nutrientes
    if (this->saude < Settings::FlorDeOrvalho::LIMITE_SAUDE_PARA_CURA &&
        pos->getNutrientes() > Settings::FlorDeOrvalho::MIN_NUTRIENTES_SOLO_PARA_CURA)
    {
        // Consome nutrientes do solo para se curar
        pos->setNutrientes(pos->getNutrientes() - Settings::FlorDeOrvalho::CUSTO_NUTRIENTES_CURA);
        this->saude += Settings::FlorDeOrvalho::GANHO_SAUDE_CURA;

        if (this->saude > 100) this->saude = 100; // Limite máximo de saúde
    }

    // --- 3. COMPORTAMENTO NORMAL ---

    // Absorve água (consumo normal)
    double aguaSolo = pos->getAgua();
    double aguaAbsorvida = std::min(Settings::FlorDeOrvalho::ABSORCAO_AGUA, aguaSolo);
    pos->setAgua(aguaSolo - aguaAbsorvida);
    this->agua_acumulada += aguaAbsorvida;

    // Produz nutrientes (característica única: em vez de consumir, dá nutrientes)
    // Nota: Isto acontece sempre que ela está viva.
    double nutSolo = pos->getNutrientes();
    pos->setNutrientes(nutSolo + Settings::FlorDeOrvalho::PRODUCAO_NUTRIENTES);
}

std::string FlorDeOrvalho::getTipo() const {
    return "Exotica";
}

char FlorDeOrvalho::getChar() const {
    return 'x'; // Representação visual
}