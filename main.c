#include "terra_media.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void mostrar_titulo() {
    printf("\n========================================\n");
    printf("- SUPER SENHORES DOS ANÉIS -\n");
    printf("- trabalho de AED 1 por pedro d'avila e pedro goncalves -\n");
    printf("========================================\n");
}

void adicionar_espacamento() {
    printf("\n\n");
}

void mostrar_menu_principal() {
    printf("\n==== MENU PRINCIPAL:\n");
    printf("[1] EXPLORAR local atual\n");
    printf("[2] MOVER pra ESQUERDA ( <- ) \n");
    printf("[3] MOVER pra DIREITA ( -> ) \n");
    printf("[4] VOLTAR pro local anterior\n");
    printf("[5] STATUS de Frodo \n");
    printf("[6] Inventario\n");
    printf("[0] finalizar programa\n");
    printf("\n INSIRA SUA ESCOLHA: ");
}

void mostrar_menu_inventario() {
    printf("\n==== INVENTARIO:\n");
    printf("[1] listar todos os itens\n");
    printf("[2] usar um item\n");
    printf("[3] voltar\n");
    printf("\n INSIRA SUA ESCOLHA: ");
}

void processar_inventario(Frodo* frodo) {
    int escolha;
    do {
        mostrar_menu_inventario();
        scanf("%d", &escolha);
        
        switch(escolha) {
            case 1:
                adicionar_espacamento();
                printf("\n=== SEUS ITENS ===\n");
                if (frodo->inventario == NULL) {
                    printf("vc nn possui itens ainda!\n");
                } else {
                    listar_itens(frodo->inventario);
                }
                break;
                
            case 2:
                adicionar_espacamento();
                if (frodo->inventario == NULL) {
                    printf("\nseu inventário esta vazio!\n");
                } else {
                    printf("\n=== USAR ITEM ===\n");
                    listar_itens(frodo->inventario);
                    
                    char nome_item[50];
                    printf("digite o nome do item que deseja usar: ");
                    scanf(" %[^\n]", nome_item);
                    
                    Item* item = buscar_item(frodo->inventario, nome_item);
                    if (item != NULL) {
                        printf("\nUsando %s...\n", item->nome);
                        
                        // Aplicar efeitos do item
                        if (strstr(item->nome, "pocao") != NULL) {
                            frodo->saude += item->valor;
                            printf("+%d pontos de saude!\n", item->valor);
                        } 
                        else if (strstr(item->nome, "espada") != NULL) {
                            frodo->forca += item->valor;
                            printf("+%d pontos de forca!\n", item->valor);
                        } 
                        else if (strstr(item->nome, "armadura") != NULL) {
                            frodo->resistencia += item->valor;
                            printf("+%d pontos de resistencia!\n", item->valor);
                        }
                        printf("item usado com sucesso!\n");
                    } else {
                        printf("\nitem não encontrado no inventário!\n");
                    }
                }
                break;
                
            case 3:
                adicionar_espacamento();
                printf("\nretornando ao menu principal...\n");
                break;
                
            default:
                printf("\nERRO FATAL! tente novamente.\n");
        }
    } while (escolha != 3);
}

int main() {
    
    // Inicialização do mundo e do personagem
    Local* mundo = criar_mundo();
    Frodo frodo;
    inicializar_frodo(&frodo, mundo);
    
    // Inicialização das estruturas de dados
    FilaBatalha fila_batalha;
    inicializar_fila(&fila_batalha);
    
    PilhaCaminho pilha_caminho;
    inicializar_pilha(&pilha_caminho);
    
    // Introdução do jogo
    mostrar_titulo();
    printf("\nFRODO, meu bom rapaz, vc deve levar o ANEL (que esta em gondor) ate o MONTE DA PERDICAO (que fica em mordor) para destrui-lo!\n");
    printf("sua jornada começa na %s. BOA SORTE!\n", frodo.local_atual->nome);
    
    // Loop principal do jogo
    int etapa = 0;
    int escolha;
    do {
        
        
        printf("______________________________________________________\n");
        // 
        if (frodo.tem_anel) {
            printf("{MISSAO ATUAL}: VC TEM O ANEL, va ate o MONTE DA PERDICAO (mordor)!");
        } else {
            printf("{MISSAO ATUAL}: vc NN possui o anel ainda, encontre-o!");
        }
        printf("\n{ETAPAS PERCORRIDAS}: %d", etapa);
        printf("\n______________________________________________________\n");
        
        
        mostrar_mapa(&frodo);
        
        if (verificar_vitoria(&frodo)) {
            adicionar_espacamento();
            printf("\n { !!! } CHEGOU A HORA. APERTE 1 PARA QUEBRAR O ANEL. { !!! } ");
        }
        else {
            adicionar_espacamento();
            mostrar_menu_principal();
        }
        
        scanf("%d", &escolha);
        
        etapa++;
        adicionar_espacamento();
        
        switch(escolha) {
            case 1:
                // no caso do fim do jogo, quebre o anel.
                if(verificar_vitoria(&frodo)) {
                    printf("\n {!!} FRODO ENTAO DESTROI O ANEL E VENCE.");
                    printf("\n parabens!");
                    escolha = 0;
                    break;
                }
                else {
                    // explore normalmente.
                    explorar_local(&frodo, &fila_batalha, &pilha_caminho);
                }
                
                break;
                
            case 2:
                if (frodo.local_atual->esq != NULL) {
                    empilhar(&pilha_caminho, frodo.local_atual);
                    frodo.local_atual = frodo.local_atual->esq;
                    printf("\n { ! } VC SE MOVEU PARA: %s\n", frodo.local_atual->nome);
                } else {
                    printf("\n { ! } N TEM CAMINHO PRA ESQUERDA! \n");
                }
                break;
                
            case 3:
                if (frodo.local_atual->dir != NULL) {
                    empilhar(&pilha_caminho, frodo.local_atual);
                    frodo.local_atual = frodo.local_atual->dir;
                    printf("\n { ! } VC SE MOVEU PARA: %s\n", frodo.local_atual->nome);
                } else {
                    printf("\n { ! } N TEM CAMINHO PRA DIREITA! \n");
                }
                break;
                
            case 4:
                if (!pilha_vazia(&pilha_caminho)) {
                    Local* anterior = desempilhar(&pilha_caminho);
                    frodo.local_atual = anterior;
                    printf("\n { ! } VC VOLTOU PARA: %s\n", frodo.local_atual->nome);
                } else {
                    printf("\n { ! } N HÁ LUGARES PRA VOLTAR!\n");
                }
                break;
                
            case 5: 
                mostrar_status(&frodo);
                break;
                
            case 6:
                processar_inventario(&frodo);
                break;

            case 0:
                printf("\n { ! } ENCERRANDO jogo...\n");
                break;
                
            default:
                printf("\n { ! } ERRO FATAL: opcao nao encontrada, tente novamente.\n");
        }

        // MORRER
        if (frodo.saude <= 0) {
            printf("\n {!!} FRODO FOI DERROTADO! A jornada termina aqui...\n");
            escolha = 0;
        }
        
    } while (escolha != 0);
    
    // limpar memoria ao final do jogo
    liberar_fila(&fila_batalha);
    liberar_pilha(&pilha_caminho);
    liberar_itens(frodo.inventario);
    liberar_mundo(mundo);
    
    printf("\n\n\nOBRIGADO por JOGAR!! Jogo feito por Pedro D'Avila e Pedro Goncalves!\n");
    return 0;
}