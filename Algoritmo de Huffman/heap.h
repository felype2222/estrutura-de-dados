#ifndef HEAP_H
#define HEAP_H

#include <stdlib.h>
#include <stdio.h>

// Forward declaration (avisa que esta estrutura existe em huffman.h)
struct HuffmanNode; 

/**
 * Estrutura para a Heap Mínima (Fila de Prioridade).
 * Organiza os nós de forma que o nó com MENOR frequência esteja sempre no topo (índice 0).
 */
typedef struct {
    struct HuffmanNode **dados; // Array dinâmico de ponteiros para nós
    int tamanho;                // Quantidade atual de elementos na heap
    int capacidade;             // Tamanho máximo alocado na memória
} MinHeap;

// Inicializa uma heap vazia com capacidade definida
MinHeap *criarHeap(int capacidade);

// Insere um novo nó e reorganiza a heap para manter a ordem
void inserirHeap(MinHeap *h, struct HuffmanNode *node);

// Remove e retorna o nó do topo (o de menor frequência)
struct HuffmanNode *removerMin(MinHeap *h);

// Funções auxiliares internas
void trocar(struct HuffmanNode **a, struct HuffmanNode **b);
void descer(MinHeap *h, int i);

#endif