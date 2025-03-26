#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

// Pilha para rastrear o caminho percorrido
typedef struct StackNode {
    char location[50];
    struct StackNode *next;
} StackNode;

StackNode* push(StackNode* top, const char* location);
StackNode* pop(StackNode* top);
void printStack(StackNode* top);
void freeStack(StackNode* top);

// Fila para gerenciamento de eventos
typedef struct QueueNode {
    char event[100];
    struct QueueNode *next;
} QueueNode;

typedef struct {
    QueueNode *front;
    QueueNode *rear;
} Queue;

void initQueue(Queue* q);
void enqueue(Queue* q, const char* event);
char* dequeue(Queue* q);
int isQueueEmpty(Queue* q);
void freeQueue(Queue* q);

// Lista encadeada para gerenciamento de inventário
typedef struct ListNode {
    char item[50];
    struct ListNode *next;
} ListNode;

ListNode* addItem(ListNode* head, const char* item);
void printInventory(ListNode* head);
void freeInventory(ListNode* head);

#endif
