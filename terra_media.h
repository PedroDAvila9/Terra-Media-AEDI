#ifndef TERRA_MEDIA_H
#define TERRA_MEDIA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "fila.h"
#include "pilha.h"

// Estrutura para representar um item
typedef struct Item {
    char nome[50];
    char descricao[100];
    int valor; // Valor de utilidade do item
    struct Item *esq;
    struct Item *dir;
} Item;

// Estrutura para representar um local na Terra Média
typedef struct Local {
    char nome[50];
    char descricao[200];
    bool tem_anel;
    bool tem_inimigo;
    bool tem_item;
    char nome_item[50];
    char desc_item[100];
    int valor_item;
    int dificuldade;
    struct Local *esq;
    struct Local *dir;
} Local;

// Estrutura para representar Frodo
typedef struct {
    int saude;
    int resistencia;
    int forca;
    Local *local_atual;
    Item *inventario; // arv de itens coletados
    bool tem_anel;
} Frodo;

// Protótipos das funções
Local* criar_mundo();
void iniciar_jornada(Frodo *frodo, Local *mundo);
void explorar_local(Frodo *frodo, FilaBatalha *batalha, PilhaCaminho *caminho);
void inicializar_frodo(Frodo *frodo, Local *mundo);
void batalhar(Frodo *frodo, FilaBatalha *batalha);
void mostrar_status(Frodo *frodo);
Item* inserir_item(Item *raiz, char nome[], char descricao[], int valor);
void liberar_itens(Item *raiz);
void listar_itens(Item *raiz);
Item* buscar_item(Item *raiz, char nome[]);
void liberar_mundo(Local* raiz);
void mostrar_mapa(Frodo *frodo);
bool verificar_vitoria(Frodo *frodo);

#endif