#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Estrutura para representar um processo
typedef struct process {
    int pid;
    int tempoTotalDeExecucao;
    int tempoDeExecucao;
} Process;

typedef struct queue {
    Process *processes;
    int front, rear, size;
    unsigned capacity;
} Queue;

// Função para criar uma fila circular
Queue *createQueue(unsigned capacity) {
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->processes = (Process *)malloc(capacity * sizeof(Process));
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    return queue;
}

// Função para verificar se a fila está vazia
bool isEmpty(Queue *queue) {
    return (queue->size == 0);
}

// Função para verificar se a fila está cheia
bool isFull(Queue *queue) {
    return (queue->size == queue->capacity);
}

// Função para enfileirar um processo
void enqueue(Queue *queue, Process process) {
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->processes[queue->rear] = process;
    queue->size = queue->size + 1;
}

// Função para desenfileirar um processo
Process dequeue(Queue *queue) {
    Process process = queue->processes[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return process;
}

int main() {
    int N;             // Número de processos
    int janelaDeTempo; // Janela de tempo em milissegundos

    // Leitura da entrada
    scanf("%d", &N);
    scanf("%d", &janelaDeTempo);

    Process processos[N];

    // Leitura dos processos
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &processos[i].pid, &processos[i].tempoTotalDeExecucao);
        processos[i].tempoDeExecucao = processos[i].tempoTotalDeExecucao * 1000; // Converter de segundos para milissegundos
    }

    int current_time = 0;

    // Crie uma fila circular para os processos
    Queue *queue = createQueue(N);

    for (int i = 0; i < N; i++) {
        enqueue(queue, processos[i]);
    }

    while (!isEmpty(queue)) {
        Process current_process = dequeue(queue);

        if (current_process.tempoDeExecucao > 0) {
            if (current_process.tempoDeExecucao <= janelaDeTempo) {
                current_time += current_process.tempoDeExecucao;
                current_process.tempoDeExecucao = 0;
                printf("%d (%d)\n", current_process.pid, current_time);
            } else {
                current_time += janelaDeTempo;
                current_process.tempoDeExecucao -= janelaDeTempo;
            }

            enqueue(queue, current_process);
        }
    }

    return 0;
}