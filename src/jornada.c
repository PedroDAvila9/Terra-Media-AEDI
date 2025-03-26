#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jornada.h"
#include "mundo.h"
#include "estrutura.h"
#include "utils.h"

void iniciarJornada(Local* mundo) {
    // Inicializa as estruturas de dados para a jornada
    StackNode* caminho = NULL;    // Pilha para rastrear o caminho percorrido
    Queue eventos;                // Fila para gerenciar eventos
    initQueue(&eventos);
    ListNode* inventario = NULL;  // Lista para inventário (pode ser expandida)

    // Define o local inicial (por exemplo, "Floresta")
    Local* localAtual = buscarLocal(mundo, "Floresta");
    if (!localAtual) {
        printf("Local inicial não encontrado.\n");
        return;
    }
    localAtual->visitado = 1;   // Marca como visitado
    caminho = push(caminho, localAtual->nome);

    // Registra o início da jornada como um evento
    char eventBuffer[100];
    snprintf(eventBuffer, sizeof(eventBuffer), "Frodo iniciou sua jornada em %s.", localAtual->nome);
    enqueue(&eventos, eventBuffer);

    char input[50];
    int opcao;

    while (1) {
        limparTela();
        // Exibe informações do local atual
        printf("Local Atual: %s (%s)\n", localAtual->nome, localAtual->tipo);
        printf("%s\n\n", localAtual->descricao);

        // Se existirem locais adjacentes, exibe-os
        if (localAtual->numAdjacentes > 0) {
            printf("Locais adjacentes:\n");
            for (int i = 0; i < localAtual->numAdjacentes; i++) {
                printf("  %d. %s\n", i + 1, localAtual->adjacentes[i]->nome);
            }
        } else {
            // Se não houver adjacentes, permite escolher entre todos os locais disponíveis
            printf("Nenhum local adjacente.\n");
            printf("Locais disponíveis:\n");
            exibirLocais(mundo);
        }
        printf("\nEscolha uma opção:\n");
        printf("1. Mover para outro local\n");
        printf("2. Ver caminho percorrido\n");
        printf("3. Processar próximo evento\n");
        printf("4. Ver inventário\n");
        printf("0. Sair da jornada\n");
        printf("Opção: ");
        fgets(input, sizeof(input), stdin);
        opcao = atoi(input);

        if (opcao == 1) {
            // Movimentação
            if (localAtual->numAdjacentes > 0) {
                int escolha;
                printf("Digite o número do local para mover: ");
                fgets(input, sizeof(input), stdin);
                escolha = atoi(input);
                if (escolha > 0 && escolha <= localAtual->numAdjacentes) {
                    localAtual = localAtual->adjacentes[escolha - 1];
                } else {
                    printf("Escolha inválida.\n");
                    printf("Pressione Enter para continuar...");
                    fgets(input, sizeof(input), stdin);
                    continue;
                }
            } else {
                printf("Digite o nome do local para mover: ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = '\0';
                Local* novoLocal = buscarLocal(mundo, input);
                if (novoLocal) {
                    localAtual = novoLocal;
                } else {
                    printf("Local não encontrado.\n");
                    printf("Pressione Enter para continuar...");
                    fgets(input, sizeof(input), stdin);
                    continue;
                }
            }
            // Atualiza informações do novo local
            localAtual->visitado = 1;
            caminho = push(caminho, localAtual->nome);
            snprintf(eventBuffer, sizeof(eventBuffer), "Frodo chegou em %s.", localAtual->nome);
            enqueue(&eventos, eventBuffer);
        } else if (opcao == 2) {
            // Exibe o caminho percorrido
            printf("Caminho percorrido:\n");
            printStack(caminho);
            printf("\nPressione Enter para continuar...");
            fgets(input, sizeof(input), stdin);
        } else if (opcao == 3) {
            // Processa o próximo evento
            if (!isQueueEmpty(&eventos)) {
                char* evento = dequeue(&eventos);
                printf("Evento: %s\n", evento);
                free(evento);
            } else {
                printf("Não há eventos pendentes.\n");
            }
            printf("\nPressione Enter para continuar...");
            fgets(input, sizeof(input), stdin);
        } else if (opcao == 4) {
            // Exibe o inventário
            printf("Inventário:\n");
            printInventory(inventario);
            printf("\nPressione Enter para continuar...");
            fgets(input, sizeof(input), stdin);
        } else if (opcao == 0) {
            break;
        } else {
            printf("Opção inválida.\n");
            printf("Pressione Enter para continuar...");
            fgets(input, sizeof(input), stdin);
        }
    }

    // Libera a memória utilizada pelas estruturas
    freeStack(caminho);
    freeQueue(&eventos);
    freeInventory(inventario);
}
