#ifndef FILA_H
#define FILA_H

typedef struct Inimigo {
    char nome[50];
    int saude;
    int forca;
} Inimigo;

typedef struct NoFila {
    Inimigo inimigo;
    struct NoFila *prox;
} NoFila;

typedef struct {
    NoFila *inicio;
    NoFila *fim;
} FilaBatalha;

void inicializar_fila(FilaBatalha *f);
void enfileirar(FilaBatalha *f, Inimigo inimigo);
Inimigo desenfileirar(FilaBatalha *f);
int fila_vazia(FilaBatalha *f);
void liberar_fila(FilaBatalha *f);

#endif