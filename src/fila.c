#include "fila.h"
#include <stdlib.h>

void inicializar_fila(FilaBatalha *f) {
    f->inicio = NULL;
    f->fim = NULL;
}

void enfileirar(FilaBatalha *f, Inimigo inimigo) {
    NoFila *novo = (NoFila*)malloc(sizeof(NoFila));
    novo->inimigo = inimigo;
    novo->prox = NULL;
    
    if (f->fim != NULL) {
        f->fim->prox = novo;
    } else {
        f->inicio = novo;
    }
    f->fim = novo;
}

Inimigo desenfileirar(FilaBatalha *f) {
    if (f->inicio == NULL) {
        Inimigo vazio = {"", 0, 0};
        return vazio;
    }
    
    NoFila *temp = f->inicio;
    Inimigo inimigo = temp->inimigo;
    
    f->inicio = f->inicio->prox;
    if (f->inicio == NULL) {
        f->fim = NULL;
    }
    
    free(temp);
    return inimigo;
}

int fila_vazia(FilaBatalha *f) {
    return (f->inicio == NULL);
}

void liberar_fila(FilaBatalha *f) {
    while (!fila_vazia(f)) {
        desenfileirar(f);
    }
}