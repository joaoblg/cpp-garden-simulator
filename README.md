# Garden Ecosystem Simulator (C++20 & Advanced OOP)

[![C++20](https://img.shields.io/badge/C%2B%2B-20-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)](https://en.wikipedia.org/wiki/C%2B%2B20)
[![CMake](https://img.shields.io/badge/Build-CMake-064F8C?style=for-the-badge&logo=cmake&logoColor=white)](https://cmake.org/)
[![Paradigm](https://img.shields.io/badge/Paradigm-Object--Oriented_Programming-orange?style=for-the-badge)](#)
[![License](https://img.shields.io/badge/Academic-ISEC_LEI-green?style=for-the-badge)](#)

A fully modular and extensible Garden Simulation engine developed in modern **C++20** for the **Object-Oriented Programming (POO)** course in Computer Engineering at **ISEC (Instituto Superior de Engenharia de Coimbra)**.

The project models a living, grid-based agricultural ecosystem with autonomous plant growth cycles, gardener actions, dynamic soil states, interactive tooling, and an extensible **Command Pattern** architecture.

---

## 🌿 Key Features

* **Grid Simulation & Environment Dynamics:** Configurable terrain dimensions, soil fertility, water retention, and seasonal progression.
* **Polymorphic Plant Hierarchy:** Diverse plant species with unique lifecycle rules, hydration needs, and harvest yields (`Cato`, `Roseira`, `ErvaDaninha`, `FlorDeOrvalho`).
* **Tooling & Inventory Management:** Interactive tools with dynamic wear and tear (`Regador`, `PacoteAdubo`, `TesouraPoda`, `PaDeTransplante`).
* **Interactive Command-Line Interface:** Comprehensive command interpreter supporting actions, simulation steps, inspection, and state persistence.
* **State Persistence:** Ability to save (`grava`), restore (`recupera`), and delete simulation snapshots in memory.

---

## 🏛️ Architecture & Design

The codebase strictly follows SOLID principles and modern C++ idioms:

```
                          ┌───────────────────────────┐
                          │         Simulador         │
                          │   (Engine & Coordinator)  │
                          └─────────────┬─────────────┘
                                        │
           ┌────────────────────────────┼───────────────────────────┐
           ▼                            ▼                           ▼
┌─────────────────────┐      ┌─────────────────────┐      ┌─────────────────────┐
│    Comando (Base)   │      │       Jardim        │      │     Jardineiro      │
│  - ComandoAcoes     │      │  (Grid, Solo, Pos)  │      │ (Inventory & Moves) │
│  - ComandoGestao    │      └──────────┬──────────┘      └─────────────────────┘
│  - ComandoListagem  │                 │
└─────────────────────┘        ┌────────┴────────┐
                               ▼                 ▼
                      ┌─────────────────┐ ┌─────────────────┐
                      │  Planta (Base)  │ │Ferramenta (Base)│
                      └─────────────────┘ └─────────────────┘
```

Detailed technical analysis and specifications are documented in the [`docs/RelatorioPOO.pdf`](docs/RelatorioPOO.pdf).

---

## 🚀 Building & Running

### Prerequisites
* Any C++20 compliant compiler (GCC 11+, Clang 13+, or MSVC 2019+)
* CMake 3.20+

### Build Instructions

```bash
# 1. Clone the repository
git clone https://github.com/joaoblg/cpp-garden-simulator.git
cd cpp-garden-simulator

# 2. Generate build system
mkdir build && cd build
cmake ..

# 3. Compile
cmake --build .

# 4. Run the executable
./POO_trabalhopratico
```

---

## 👨‍💻 Author & Academic Context

* **João Bernardo Graça**

Developed as part of the **Degree in Computer Engineering (LEI)** - *Application Development (DA) branch* at **ISEC (Instituto Superior de Engenharia de Coimbra)**.
