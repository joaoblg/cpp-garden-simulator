#include "Cato.h"
#include "../Posicao.h" // Precisa de saber o que é uma Posição
#include "../settings.h"
#include "../Jardim.h"
#include <iostream>
#include <algorithm> // Para std::min

Cato::Cato() : Planta(BelezaPlanta::NEUTRA),
instantes_excesso_agua(0),
instantes_falta_nutrientes(0) {}

Planta* Cato::clone() const {
    return new Cato(*this); // Usa o construtor de cópia automático do C++
}

void Cato::atualizar(Jardim& jardim, int linha, int coluna, int instante) {
    Posicao* pos = jardim.getPosicao(linha, coluna);
    // 1. Absorver 25% da água do solo
    double aguaNoSolo = pos->getAgua();
    double aguaAbsorvida = aguaNoSolo * Settings::Cacto::absorcao_agua_percentagem / 100.0;
    pos->setAgua(aguaNoSolo - aguaAbsorvida);
    this->agua_acumulada += aguaAbsorvida;
    // 2. Absorver até 5 nutrientes do solo
    double nutrientesNoSolo = pos->getNutrientes();
    double nutrientesAbsorvidos = std::min(double(Settings::Cacto::absorcao_nutrientes), nutrientesNoSolo);
    pos->setNutrientes(nutrientesNoSolo - nutrientesAbsorvidos);
    this->nutrientes_acumulados += nutrientesAbsorvidos;
    // --- LÓGICA DE MORTE
    // 3. Verificar excesso de água
    if (pos->getAgua() > Settings::Cacto::morre_agua_solo_maior) {
        this->instantes_excesso_agua++; // Incrementa contador
    } else {
        this->instantes_excesso_agua = 0; // Reinicia contador
    }
    // 4. Verificar falta de nutrientes
    if (pos->getNutrientes() == 0) {
        this->instantes_falta_nutrientes++; // Incrementa contador
    } else {
        this->instantes_falta_nutrientes = 0; // Reinicia contador
    }
    // 5. Verificar se alguma das condições de morte foi atingida
    if (this->instantes_excesso_agua >= Settings::Cacto::morre_agua_solo_instantes ||
        this->instantes_falta_nutrientes >= Settings::Cacto::morre_nutrientes_solo_instantes)
    {
        std::cout << "[Instante " << instante << "] INFO: Um Cato morreu devido as condicoes do solo." << std::endl;
        // Regra de devolução de recursos
        pos->setNutrientes(pos->getNutrientes() + this->nutrientes_acumulados);

        pos->setPlanta(nullptr); // A planta morre
        return; // Pára a execução
    }

    // --- LÓGICA DE MULTIPLICAÇÃO ---
    // Regra: Nutrientes > 100 E Água > 50
    if (this->nutrientes_acumulados > Settings::Cacto::multiplica_nutrientes_maior &&
        this->agua_acumulada > Settings::Cacto::multiplica_agua_maior)
    {
        // Tentar encontrar uma posição vizinha VAZIA
        // Vizinhos possíveis: (l-1, c), (l+1, c), (l, c-1), (l, c+1)
        int dL[] = {-1, 1, 0, 0};
        int dC[] = {0, 0, -1, 1};

        for (int i = 0; i < 4; ++i) {
            int vizL = linha + dL[i];
            int vizC = coluna + dC[i];

            if (jardim.isPosicaoValida(vizL, vizC)) {
                Posicao* vizinho = jardim.getPosicao(vizL, vizC);
                if (!vizinho->isOcupada()) {
                    // Encontrámos um lugar!
                    Cato* filho = new Cato();

                    // Divide recursos: Metade para o filho, metade fica no pai
                    double aguaParaFilho = this->agua_acumulada / 2.0;
                    double nutrParaFilho = this->nutrientes_acumulados / 2.0;

                    // O filho nasce com estes recursos (temos de criar setters ou amigos,
                    // mas para simplificar podemos assumir acesso protegido ou getters/setters na Planta)
                    // NOTA: Como são protected, o Cato pode aceder aos membros de outro Cato!
                    filho->agua_acumulada = aguaParaFilho;
                    filho->nutrientes_acumulados = nutrParaFilho;

                    this->agua_acumulada -= aguaParaFilho;
                    this->nutrientes_acumulados -= nutrParaFilho;

                    vizinho->setPlanta(filho);
                    std::cout << "INFO: Um Cato multiplicou-se para (" << vizL << "," << vizC << ")!" << std::endl;
                    break; // Multiplica apenas uma vez por turno
                }
            }
        }
    }
}

std::string Cato::getTipo() const {
    return "Cato";
}

char Cato::getChar() const {
    return 'c';
}
