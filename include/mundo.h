#ifndef MUNDO_H
#define MUNDO_H

#define MAX_ADJACENTES 4

// Estrutura para representar um local
typedef struct Local {
    char nome[50];
    char descricao[200];
    char tipo[30];       // Exemplo: "Floresta", "Caverna", "Castelo", "Vilarejo"
    int visitado;        // Flag para indicar se o local já foi visitado
    struct Local* adjacentes[MAX_ADJACENTES]; // Array de ponteiros para locais adjacentes (para formar um grafo)
    int numAdjacentes;   // Número de locais conectados
    //Adicionar outros atributos (como inimigos, tesouros, NPCs) podem ser adicionados aqui
    struct Local* proximo; // Usado para manter a lista encadeada de todos os locais
} Local;

// Funções para gerenciar o mundo
Local* criarMundo();
Local* buscarLocal(Local* mundo, const char* nome);
void liberarMundo(Local* mundo);
void exibirLocais(Local* mundo);

// Funções para manipulação de conexões entre locais
void conectarLocais(Local* origem, Local* destino);
void exibirAdjacentes(Local* local);

#endif
