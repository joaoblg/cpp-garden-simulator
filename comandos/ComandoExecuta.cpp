#include "ComandoExecuta.h"
#include "../simulador.h"
#include <iostream>
#include <fstream> // Necessário para ler ficheiros

ComandoExecuta::ComandoExecuta(std::stringstream& ss) {
    std::string lixo;
    if (ss >> nomeFicheiro && !(ss >> lixo)) {
        sintaxe_valida = true;
    } else {
        sintaxe_valida = false;
    }
}

void ComandoExecuta::executa(Simulador& simulador) const {
    if (!sintaxe_valida) {
        std::cout << "Sintaxe invalida. Uso: executa <nome-ficheiro>" << std::endl;
        return;
    }

    // 1. Tentar abrir o ficheiro
    std::ifstream ficheiro(nomeFicheiro);

    if (!ficheiro.is_open()) {
        std::cout << "ERRO: Nao foi possivel abrir o ficheiro '" << nomeFicheiro << "'." << std::endl;
        return;
    }

    std::cout << "--- A iniciar execucao do ficheiro: " << nomeFicheiro << " ---" << std::endl;

    // 2. Ler linha a linha
    std::string linha;
    while (std::getline(ficheiro, linha)) {
        if (linha.empty()) continue;

        // --- CORREÇÃO: Se encontrar 'fim', para de ler o ficheiro ---
        if (linha == "fim") {
            std::cout << "Comando 'fim' encontrado. A terminar execucao do ficheiro." << std::endl;
            break;
        }

        std::cout << ">> " << linha << std::endl;
        simulador.executarLinha(linha);
    }

    std::cout << "--- Fim da execucao do ficheiro: " << nomeFicheiro << " ---" << std::endl;
    ficheiro.close();
}