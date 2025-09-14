#ifndef FILA_H // Evita inclusão múltipla
#define FILA_H // Evita inclusão múltipla

#define MAX 100 // Define o tamanho máximo da fila

typedef struct { // Define a estrutura da fila
    int itens[MAX];
    int inicio;
    int fim;
    int tamanho;
} Fila;

void inicializar(Fila *f); // Inicializa a fila
int vazia(Fila *f); // Verifica se a fila está vazia
int cheia(Fila *f); // Verifica se a fila está cheia
int enfileirar(Fila *f, int valor); // Adiciona um elemento à fila
int desenfileirar(Fila *f, int *removido); // Remove um elemento da fila
void imprimirFila(Fila *f); // Imprime os elementos da fila 

#endif 