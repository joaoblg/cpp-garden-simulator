#ifndef SETTINGS_SETTINGS_H
#define SETTINGS_SETTINGS_H

class Settings {
    public:
    class Jardim {
    public:
        static const int agua_min = 80;
        static const int agua_max = 100;
        static const int nutrientes_min = 40;
        static const int nutrientes_max = 50;
    };
    class Regador {
    public:
        static const int capacidade = 200;
        static const int dose = 10;
    };
    class Adubo {
    public:
        static const int capacidade = 100;
        static const int dose = 10;
    };
    class Jardineiro {
    public:
        static const int max_movimentos = 10;
        static const int max_entradas_saidas = 1;
        static const int max_plantacoes = 2;
        static const int max_colheitas = 5;
    };
    class Cacto {
        public:
        static const int absorcao_agua_percentagem = 25;
        static const int absorcao_nutrientes = 5;
        static const int morre_agua_solo_maior = 100;
        static const int morre_agua_solo_instantes = 3;
        static const int morre_nutrientes_solo_menor = 1;
        static const int morre_nutrientes_solo_instantes = 3;
        static const int multiplica_nutrientes_maior = 100;
        static const int multiplica_agua_maior = 50;
    };
    class Roseira {
        public:
        static const int inicial_agua = 25;
        static const int inicial_nutrientes = 25;
        static const int perda_agua = 4;
        static const int perda_nutrientes = 4;
        static const int absorcao_agua = 5;
        static const int absorcao_nutrientes = 8;
        static const int morre_agua_menor = 1;
        static const int morre_nutrientes_menor = 1;
        static const int morre_nutrientes_maior = 199;
        static const int multiplica_nutrientes_maior = 100;
        static const int nova_nutrientes = 25;
        static const int nova_agua_percentagem = 50;
        static const int original_nutrientes = 100;
        static const int original_agua_percentagem = 50;
    };
    class ErvaDaninha {
        public:
        static const int inicial_agua = 5;
        static const int inicial_nutrientes = 5;
        static const int absorcao_agua = 1;
        static const int absorcao_nutrientes = 1;
        static const int morre_instantes = 60;
        static const int multiplica_nutrientes_maior = 30;
        static const int multiplica_instantes = 5;
        static const int nova_nutrientes = 5;
        static const int original_nutrientes = 5;
    };
    class FlorDeOrvalho {
    public:
        // Consumo e Produção Base
        static constexpr double ABSORCAO_AGUA = 3.0;
        static constexpr double PRODUCAO_NUTRIENTES = 2.0;

        // Regras de Morte
        static constexpr int TEMPO_VIDA_MAX = 75;
        static constexpr int MAX_INSTANTES_SEM_AGUA = 5;

        // Bónus de Morte (Decompõe-se e aduba o solo)
        static constexpr double BONUS_AGUA_MORTE = 20.0;
        static constexpr double BONUS_NUTRIENTES_MORTE = 50.0;

        // Regras de Regeneração
        static constexpr int LIMITE_SAUDE_PARA_CURA = 50;
        static constexpr double MIN_NUTRIENTES_SOLO_PARA_CURA = 60.0;
        static constexpr double CUSTO_NUTRIENTES_CURA = 10.0;
        static constexpr int GANHO_SAUDE_CURA = 10;
    };
};

#endif //SETTINGS_SETTINGS_H