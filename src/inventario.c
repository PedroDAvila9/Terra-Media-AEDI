#include "terra_media.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Insere um item na árvore de inventário
Item* inserir_item(Item *raiz, char nome[], char descricao[], int valor) {
    if (raiz == NULL) {
        Item *novo = (Item*)malloc(sizeof(Item));
        strcpy(novo->nome, nome);
        strcpy(novo->descricao, descricao);
        novo->valor = valor;
        novo->esq = novo->dir = NULL;
        return novo;
    }
    
    int cmp = strcmp(nome, raiz->nome);
    if (cmp < 0) {
        raiz->esq = inserir_item(raiz->esq, nome, descricao, valor);
    } else if (cmp > 0) {
        raiz->dir = inserir_item(raiz->dir, nome, descricao, valor);
    }
    
    return raiz;
}

// Libera a memória da árvore de itens
void liberar_itens(Item *raiz) {
    if (raiz != NULL) {
        liberar_itens(raiz->esq);
        liberar_itens(raiz->dir);
        free(raiz);
    }
}

// Lista todos os itens em ordem alfabética
void listar_itens(Item *raiz) {
    if (raiz != NULL) {
        listar_itens(raiz->esq);
        printf("-> %s: %s (Valor: %d)\n", raiz->nome, raiz->descricao, raiz->valor);
        listar_itens(raiz->dir);
    }
}

// Busca um item no inventário
Item* buscar_item(Item *raiz, char nome[]) {
    if (raiz == NULL) return NULL;
    
    int cmp = strcmp(nome, raiz->nome);
    if (cmp == 0) return raiz;
    if (cmp < 0) return buscar_item(raiz->esq, nome);
    return buscar_item(raiz->dir, nome);
}