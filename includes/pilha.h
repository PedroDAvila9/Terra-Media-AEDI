#ifndef PILHA_H
#define PILHA_H

typedef struct Local Local; 

typedef struct NoPilha {
    Local *local;
    struct NoPilha *prox;
} NoPilha;

typedef struct {
    NoPilha *topo;
} PilhaCaminho;

void inicializar_pilha(PilhaCaminho *p);
void empilhar(PilhaCaminho *p, Local *local);
Local* desempilhar(PilhaCaminho *p);
int pilha_vazia(PilhaCaminho *p);
void liberar_pilha(PilhaCaminho *p);

#endif