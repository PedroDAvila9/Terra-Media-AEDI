#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mundo.h"

void inicializarLocal(Local* local, const char* nome, const char* descricao, const char* tipo) {
    strncpy(local->nome, nome, sizeof(local->nome)-1);
    local->nome[sizeof(local->nome)-1] = '\0';

    strncpy(local->descricao, descricao, sizeof(local->descricao)-1);
    local->descricao[sizeof(local->descricao)-1] = '\0';

    strncpy(local->tipo, tipo, sizeof(local->tipo)-1);
    local->tipo[sizeof(local->tipo)-1] = '\0';

    local->visitado = 0;
    local->numAdjacentes = 0;
    for (int i = 0; i < MAX_ADJACENTES; i++) {
        local->adjacentes[i] = NULL;
    }
    local->proximo = NULL;
}

Local* criarMundo() {
    Local *mundo = NULL;
    Local *novo;

    // Cria o local "Floresta"
    novo = (Local*) malloc(sizeof(Local));
    if (!novo) {
        printf("Erro ao alocar memória para a Floresta.\n");
        exit(1);
    }
    inicializarLocal(novo, "Floresta", "Uma floresta densa e misteriosa.", "Floresta");
    novo->proximo = mundo;
    mundo = novo;

    // Cria o local "Caverna"
    novo = (Local*) malloc(sizeof(Local));
    if (!novo) {
        printf("Erro ao alocar memória para a Caverna.\n");
        exit(1);
    }
    inicializarLocal(novo, "Caverna", "Uma caverna escura, cheia de segredos.", "Caverna");
    novo->proximo = mundo;
    mundo = novo;

    // Cria o local "Vilarejo"
    novo = (Local*) malloc(sizeof(Local));
    if (!novo) {
        printf("Erro ao alocar memória para o Vilarejo.\n");
        exit(1);
    }
    inicializarLocal(novo, "Vilarejo", "Um pequeno vilarejo pacífico.", "Vilarejo");
    novo->proximo = mundo;
    mundo = novo;

    // Cria o local "Castelo"
    novo = (Local*) malloc(sizeof(Local));
    if (!novo) {
        printf("Erro ao alocar memória para o Castelo.\n");
        exit(1);
    }
    inicializarLocal(novo, "Castelo", "Um antigo castelo cheio de mistérios.", "Castelo");
    novo->proximo = mundo;
    mundo = novo;

    return mundo;
}

Local* buscarLocal(Local* mundo, const char* nome) {
    while(mundo) {
        if(strcmp(mundo->nome, nome) == 0)
            return mundo;
        mundo = mundo->proximo;
    }
    return NULL;
}

void liberarMundo(Local* mundo) {
    Local* tmp;
    while(mundo) {
        tmp = mundo;
        mundo = mundo->proximo;
        free(tmp);
    }
}

void exibirLocais(Local* mundo) {
    printf("Locais disponíveis:\n");
    while(mundo) {
        printf("- %s (%s): %s\n", mundo->nome, mundo->tipo, mundo->descricao);
        mundo = mundo->proximo;
    }
}

// Conecta dois locais, adicionando o destino aos adjacentes da origem
void conectarLocais(Local* origem, Local* destino) {
    if (origem->numAdjacentes < MAX_ADJACENTES) {
        origem->adjacentes[origem->numAdjacentes] = destino;
        origem->numAdjacentes++;
    } else {
        printf("Não é possível conectar mais locais a %s\n", origem->nome);
    }
}

// Exibe os locais adjacentes a um determinado local
void exibirAdjacentes(Local* local) {
    if (local->numAdjacentes == 0) {
        printf("Não há locais adjacentes a %s.\n", local->nome);
        return;
    }
    printf("Locais adjacentes a %s:\n", local->nome);
    for (int i = 0; i < local->numAdjacentes; i++) {
        printf("- %s\n", local->adjacentes[i]->nome);
    }
}
