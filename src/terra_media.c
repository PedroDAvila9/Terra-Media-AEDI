#include "terra_media.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**************************************
 * FUNÇÕES PARA CRIAÇÃO DO MUNDO
 **************************************/

Local* criar_local(const char* nome, const char* descricao, bool tem_anel, 
                  bool tem_inimigo, bool tem_item, const char* nome_item, 
                  const char* desc_item, int valor_item, int dificuldade) {
    Local* novo = (Local*)malloc(sizeof(Local));
    strcpy(novo->nome, nome);
    strcpy(novo->descricao, descricao);
    novo->tem_anel = tem_anel;
    novo->tem_inimigo = tem_inimigo;
    novo->tem_item = tem_item;
    if (tem_item) {
        strcpy(novo->nome_item, nome_item);
        strcpy(novo->desc_item, desc_item);
        novo->valor_item = valor_item;
    }
    novo->dificuldade = dificuldade;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

Local* criar_mundo() {
    // Criar todos os locais com seus itens
    Local* vila = criar_local(
        "Vila dos Hobbits", 
        "Um lugar pacífico onde sua jornada começa.", 
        false, false, false, "", "", 0, 1
    );
    
    Local* floresta = criar_local(
        "Floresta de Fangorn", 
        "Uma floresta antiga e misteriosa. Cuidado com os Ents!", 
        false, true, true,
        "POCAO DE CURA", "Restaura 20 pontos de saúde", 20, 4
    );
    
    Local* moria = criar_local(
        "Minas de Moria", 
        "Um reino subterrâneo abandonado. Escuro e perigoso.", 
        false, true, true,
        "ESPADA ELFICA", "Aumenta força em 15 pontos", 15, 7
    );
    
    Local* rohan = criar_local(
        "Rohan", 
        "A terra dos cavaleiros. Pode encontrar aliados aqui.", 
        false, false, false, "", "", 0, 3
    );
    
    Local* gondor = criar_local(
        "Gondor", 
        "O reino dos homens. Um lugar de refúgio.", 
        true, false, true,
        "ARMADURA DE MITHRIL", "Aumenta resistência em 25 pontos", 25, 2
    );
    
    Local* mordor = criar_local(
        "Mordor", 
        "A terra do mal. O destino final de sua jornada.", 
        false, true, false, "", "", 0, 10
    );

    // Montar a estrutura da árvore
    vila->esq = floresta;
    vila->dir = rohan;
    
    floresta->esq = moria;
    floresta->dir = NULL;
    
    moria->esq = NULL;
    moria->dir = mordor;
    
    rohan->esq = gondor;
    rohan->dir = NULL;
    
    gondor->esq = NULL;
    gondor->dir = NULL;
    
    mordor->esq = NULL;
    mordor->dir = NULL;
    
    
    
    return vila;
}

void mostrar_mapa(Frodo *frodo) {
    printf("\n======= MAPA =======\n");
    
    //________________________________________________________
    if (strcmp(frodo->local_atual->nome, "Vila dos Hobbits") == 0)
        printf(" >>> FLORESTA - [VILA] - ROHAN \n");
    else
        printf(" FLORESTA - VILA - ROHAN \n");
    
    //________________________________________________________
    if (strcmp(frodo->local_atual->nome, "Floresta de Fangorn") == 0)
        printf(" >>>  MORIA - [FLORESTA] - X \n");
    else
        printf(" MORIA - FLORESTA - X \n");
    
    //________________________________________________________
    if (strcmp(frodo->local_atual->nome, "Minas de Moria") == 0)
        printf(" >>>  X - [MORIA] - MORDOR \n");
    else
        printf(" X - MORIA - MORDOR \n");
    
    //________________________________________________________
    if (strcmp(frodo->local_atual->nome, "Rohan") == 0)
        printf(" >>>  GONDOR - [ROHAN] - X \n");
    else
        printf(" GONDOR - ROHAN - X \n");
    
    //________________________________________________________
    if (strcmp(frodo->local_atual->nome, "Gondor") == 0)
        printf(" >>>  X - [GONDOR] - X \n");
    else
        printf(" X - GONDOR - X \n");
    
    //________________________________________________________
    if (strcmp(frodo->local_atual->nome, "Mordor") == 0)
        printf(" >>>  X - [MORDOR] - X \n");
    else
        printf(" X - MORDOR - X \n");
}

void liberar_mundo(Local* raiz) {
    if (raiz != NULL) {
        liberar_mundo(raiz->esq);
        liberar_mundo(raiz->dir);
        free(raiz);
    }
}

/**************************************
 * FUNÇÕES PARA GERENCIAMENTO DO FRODO
 **************************************/
void inicializar_frodo(Frodo* frodo, Local* mundo) {
    frodo->saude = 100;
    frodo->resistencia = 80;
    frodo->forca = 50;
    frodo->local_atual = mundo;
    frodo->inventario = NULL;
    frodo->tem_anel = false;  // começa sem o Anel
}

void mostrar_status(Frodo* frodo) {
    printf("\n=== STATUS DE FRODO ===\n");
    printf("VIDA: %d\n", frodo->saude);
    printf("FORCA: %d\n", frodo->forca);
    printf("RESISTENCIA: %d\n", frodo->resistencia);
    printf("LOCAL: %s\n", frodo->local_atual->nome);
    
    printf("\n=== INVENTÁRIO ===\n");
    if (frodo->inventario == NULL) {
        printf("nenhum item, pobre!\n");
    } else {
        listar_itens(frodo->inventario);
    }
}

bool verificar_vitoria(Frodo *frodo) {
    return (strcmp(frodo->local_atual->nome, "Mordor") == 0) && frodo->tem_anel;
}

/**************************************
 * FUNÇÕES PARA EXPLORAÇÃO E BATALHA
 **************************************/

void explorar_local(Frodo* frodo, FilaBatalha* batalha, PilhaCaminho* caminho) {
    printf("\n=== EXPLORANDO %s ===\n", frodo->local_atual->nome);
    printf("%s\n", frodo->local_atual->descricao);
    
    // Verificar se há item no local
    if (frodo->local_atual->tem_item) {
        printf("\n !!! VC ENCONTROU: %s (%s)\n", 
               frodo->local_atual->nome_item,
               frodo->local_atual->desc_item);
        printf("deseja coletar? ([1]-Sim / [2]-Não): ");
        
        int escolha;
        scanf("%d", &escolha);
        
        if (escolha == 1) {
            frodo->inventario = inserir_item(
                frodo->inventario,
                frodo->local_atual->nome_item,
                frodo->local_atual->desc_item,
                frodo->local_atual->valor_item
            );
            printf("%s foi adicionado ao seu inventario!\n", frodo->local_atual->nome_item);
            
            // Marcar item como coletado
            frodo->local_atual->tem_item = false;
        }
    }
    
    // Verificar se há inimigo no local
    if (frodo->local_atual->tem_inimigo) {
        printf("\n\n !!!!!!!! ALERTA: um inimigo aparece!\n");
        
        // Criar inimigo baseado na dificuldade do local
        Inimigo inimigo;
        strcpy(inimigo.nome, "ORC");
        inimigo.saude = frodo->local_atual->dificuldade * 15;
        inimigo.forca = frodo->local_atual->dificuldade * 5;
        
        enfileirar(batalha, inimigo);
        batalhar(frodo, batalha);
    } else {
        printf("\nO local esta seguro. Nenhum inimigo encontrado.\n");
    }
    
    // Verificar se encontrou o Anel
    if (frodo->tem_anel==false && frodo->local_atual->tem_anel) {
        printf("\n {!!!!!} \nPARABENS!! Vc encontrou o ANEL DOS SENHORES DOS ANEIS!\n");
        printf("agr vc deve leva-lo até o MONTE DA PERDICAO para DESTRUIR ELE\n");
        
        frodo->tem_anel = true;
    }
}

void batalhar(Frodo* frodo, FilaBatalha* batalha) {
    while (frodo->saude > 0 && !fila_vazia(batalha)) {
        Inimigo inimigo = desenfileirar(batalha);
        
        printf("\n >> BATALHA CONTRA %s ️<< \n", inimigo.nome);
        printf("VIDA DO INIMIGO: %d | FORCA: %d\n", inimigo.saude, inimigo.forca);
        
        int escolha;
        do {
            printf("\n[1] Atacar\n");
            printf("[2] Defender\n");
            printf("[3] Usar item\n");
            printf("[4] Tentar fugir\n");
            printf("Escolha: ");
            scanf("%d", &escolha);
            
            switch(escolha) {
                case 1: // Atacar
                    printf("\n{!} FRODO ataca o %s!\n", inimigo.nome);
                    inimigo.saude -= frodo->forca;
                    if (inimigo.saude > 0) {
                        printf("{!} %s contra-ataca!\n", inimigo.nome);
                        frodo->saude -= inimigo.forca / 2;
                    }
                    break;
                    
                case 2: // Defender
                    printf("\n{!} FRODO se defende!\n");
                    frodo->resistencia -= 10;
                    if (frodo->resistencia > 0) {
                        printf("{!} vc reduz o dano recebido.\n");
                        frodo->saude -= inimigo.forca / 4;
                    } else {
                        printf("{!} sua RESISTENCIA esta baixa!\n");
                        frodo->saude -= inimigo.forca / 2;
                    }
                    break;
                    
                case 3: // Usar item
                    if (frodo->inventario == NULL) {
                        printf("\n{!} vc N tem itens, POBRE!\n");
                    } else {
                        printf("\n{!} itens disponiveis:\n");
                        listar_itens(frodo->inventario);
                        
                        char item_nome[50];
                        printf("{!} DIGITE o nome do item que deseja usar: ");
                        scanf(" %[^\n]", item_nome);
                        
                        Item* item = buscar_item(frodo->inventario, item_nome);
                        if (item != NULL) {
                            printf("\n{!} usando %s...\n", item->nome);
                            
                            if (strstr(item->nome, "POCAO") != NULL) {
                                frodo->saude += item->valor;
                                printf("{!} VIDA aumentada em %d pontos!\n", item->valor);
                            } else if (strstr(item->nome, "ESPADA") != NULL) {
                                frodo->forca += item->valor;
                                printf("{!} FORCA aumentada em %d pontos!\n", item->valor);
                            } else if (strstr(item->nome, "ARMADURA") != NULL) {
                                frodo->resistencia += item->valor;
                                printf("{!} RESISTENCIA aumentada em %d pontos!\n", item->valor);
                            }
                            
                            printf("{!} item consumido.\n");
                        } else {
                            printf("\n{!} item n encontrado!\n");
                        }
                    }
                    break;
                    
                case 4: // Fugir
                    printf("{!} frodo fugiu!\n");
                    return;

                    break;
                    
                default:
                    printf("\nERRO FATAL: opcao invalida!\n");
            }
            
            // mostrar os status 
            mostrar_status(frodo);
            if (inimigo.saude > 0) {
                printf("\n%s: vida %d\n", inimigo.nome, inimigo.saude);
            }
            
        } while (escolha != 4 && inimigo.saude > 0 && frodo->saude > 0);
        
        if (inimigo.saude <= 0) {
            printf("\n\n>>>>>> %s foi derrotado!\n\n", inimigo.nome);
        }
    }
}