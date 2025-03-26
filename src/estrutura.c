#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estrutura.h"

// Implementação da Pilha
StackNode* push(StackNode* top, const char* location) {
    StackNode* new_node = (StackNode*) malloc(sizeof(StackNode));
    if (!new_node) {
        printf("Erro ao alocar memória para a pilha.\n");
        exit(1);
    }
    strncpy(new_node->location, location, sizeof(new_node->location) - 1);
    new_node->location[sizeof(new_node->location) - 1] = '\0';
    new_node->next = top;
    return new_node;
}

StackNode* pop(StackNode* top) {
    if (!top) {
        return NULL;
    }
    StackNode* temp = top;
    top = top->next;
    free(temp);
    return top;
}

void printStack(StackNode* top) {
    printf("Caminho percorrido:\n");
    while(top) {
        printf("- %s\n", top->location);
        top = top->next;
    }
}

void freeStack(StackNode* top) {
    while(top) {
        top = pop(top);
    }
}

// Implementação da Fila
void initQueue(Queue* q) {
    q->front = q->rear = NULL;
}

void enqueue(Queue* q, const char* event) {
    QueueNode* new_node = (QueueNode*) malloc(sizeof(QueueNode));
    if (!new_node) {
        printf("Erro ao alocar memória para a fila.\n");
        exit(1);
    }
    strncpy(new_node->event, event, sizeof(new_node->event) - 1);
    new_node->event[sizeof(new_node->event) - 1] = '\0';
    new_node->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = new_node;
        return;
    }
    q->rear->next = new_node;
    q->rear = new_node;
}

char* dequeue(Queue* q) {
    if (q->front == NULL) {
        return NULL;
    }
    QueueNode* temp = q->front;
    char* event = (char*) malloc(100 * sizeof(char));
    if (!event) {
        printf("Erro ao alocar memória para o evento.\n");
        exit(1);
    }
    strncpy(event, temp->event, 100);
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
    return event;
}

int isQueueEmpty(Queue* q) {
    return (q->front == NULL);
}

void freeQueue(Queue* q) {
    while(!isQueueEmpty(q)) {
        char* e = dequeue(q);
        free(e);
    }
}

// Implementação da Lista Encadeada (Inventário)
ListNode* addItem(ListNode* head, const char* item) {
    ListNode* new_node = (ListNode*) malloc(sizeof(ListNode));
    if (!new_node) {
        printf("Erro ao alocar memória para o inventário.\n");
        exit(1);
    }
    strncpy(new_node->item, item, sizeof(new_node->item) - 1);
    new_node->item[sizeof(new_node->item) - 1] = '\0';
    new_node->next = head;
    return new_node;
}

void printInventory(ListNode* head) {
    printf("Inventário:\n");
    if (!head) {
        printf("  (vazio)\n");
    }
    while(head) {
        printf("- %s\n", head->item);
        head = head->next;
    }
}

void freeInventory(ListNode* head) {
    ListNode* tmp;
    while(head) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}
