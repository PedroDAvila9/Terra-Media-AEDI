#include "pilha.h"
#include <stdlib.h>

void inicializar_pilha(PilhaCaminho *p) {
    p->topo = NULL;
}

void empilhar(PilhaCaminho *p, Local *local) {
    NoPilha *novo = (NoPilha*)malloc(sizeof(NoPilha));
    novo->local = local;
    novo->prox = p->topo;
    p->topo = novo;
}

Local* desempilhar(PilhaCaminho *p) {
    if (p->topo == NULL) {
        return NULL;
    }
    
    NoPilha *temp = p->topo;
    Local *local = temp->local;
    p->topo = p->topo->prox;
    free(temp);
    return local;
}

int pilha_vazia(PilhaCaminho *p) {
    return (p->topo == NULL);
}

void liberar_pilha(PilhaCaminho *p) {
    while (!pilha_vazia(p)) {
        desempilhar(p);
    }
}