cmake_minimum_required(VERSION 3.30)
project(POO_trabalhopratico)

set(CMAKE_CXX_STANDARD 20)

# Diz ao compilador ONDE procurar os ficheiros .h
#include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(plantas)
include_directories(ferramentas)
include_directories(comandos)
# Adiciona as novas sub-pastas de comandos
include_directories(comandos/ComandoAcoes)
include_directories(comandos/ComandoGestao)
include_directories(comandos/ComandoListagem)

add_executable(POO_trabalhopratico
        # --- Ficheiros Principais ---
        main.cpp
        Simulador.cpp
        Jardim.cpp
        Posicao.cpp
        Jardineiro.cpp


        # --- Hierarquia de Plantas ---
        plantas/Planta.cpp
        plantas/Cato.cpp
        plantas/Roseira.cpp
        plantas/ErvaDaninha.cpp
        plantas/FlorDeOrvalho.cpp

        # --- Hierarquia de Ferramentas ---
        ferramentas/Ferramenta.cpp
        ferramentas/Regador.cpp
        ferramentas/PacoteAdubo.cpp
        ferramentas/TesouraPoda.cpp
        ferramentas/PaDeTransplante.cpp

        # --- Hierarquia de Comandos (com as novas pastas) ---
        # Comandos Gerais e de Simulação
        comandos/ComandoAvanca.cpp
        comandos/ComandoExecuta.cpp
        comandos/ComandoJardim.cpp
        comandos/ComandoMove.cpp

        # Comandos de Ação
        comandos/ComandoAcoes/ComandoColhe.cpp
        comandos/ComandoAcoes/ComandoCompra.cpp
        comandos/ComandoAcoes/ComandoEntra.cpp
        comandos/ComandoAcoes/ComandoLarga.cpp
        comandos/ComandoAcoes/ComandoPega.cpp
        comandos/ComandoAcoes/ComandoPlanta.cpp
        comandos/ComandoAcoes/ComandoSai.cpp

        # Comandos de Gestão
        comandos/ComandoGestao/ComandoGrava.cpp
        comandos/ComandoGestao/ComandoRecupera.cpp
        comandos/ComandoGestao/ComandoApaga.cpp

        # Comandos de Listagem
        comandos/ComandoListagem/ComandoLArea.cpp
        comandos/ComandoListagem/ComandoLFerr.cpp
        comandos/ComandoListagem/ComandoLPlanta.cpp
        comandos/ComandoListagem/ComandoLPlantas.cpp
        comandos/ComandoListagem/ComandoLSolo.cpp
)
