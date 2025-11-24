#include "heap.h"
#include "huffman.h" // Necessário para acessar 'node->freq'

// Cria a estrutura e aloca memória para o array de ponteiros
MinHeap *criarHeap(int capacidade) {
    MinHeap *h = (MinHeap *)malloc(sizeof(MinHeap));
    h->dados = (HuffmanNode **)malloc(capacidade * sizeof(HuffmanNode *));
    h->capacidade = capacidade;
    h->tamanho = 0;
    return h;
}

// Troca dois nós de lugar no array (auxiliar para ordenação)
void trocar(HuffmanNode **a, HuffmanNode **b) {
    HuffmanNode *temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * Função "Min-Heapify" (Descer).
 * Verifica se o pai é maior que os filhos. Se for, troca com o menor filho.
 * Garante que o menor elemento suba para o topo.
 */
void descer(MinHeap *h, int i) {
    int menor = i;
    int esq = 2 * i + 1; // Fórmula para filho esquerdo
    int dir = 2 * i + 2; // Fórmula para filho direito

    // Verifica se filho esquerdo existe e é menor que o pai
    if (esq < h->tamanho && h->dados[esq]->freq < h->dados[menor]->freq)
        menor = esq;

    // Verifica se filho direito existe e é menor que o atual menor
    if (dir < h->tamanho && h->dados[dir]->freq < h->dados[menor]->freq)
        menor = dir;

    // Se o pai não for o menor, troca e continua descendo recursivamente
    if (menor != i) {
        trocar(&h->dados[i], &h->dados[menor]);
        descer(h, menor);
    }
}

/**
 * Insere um elemento no final e o faz "subir" (Bubble Up)
 * até encontrar a posição correta onde o pai seja menor que ele.
 */
void inserirHeap(MinHeap *h, HuffmanNode *node) {
    int i = h->tamanho++;
    h->dados[i] = node;

    // Enquanto não for a raiz e for menor que o pai: sobe
    while (i && h->dados[(i - 1) / 2]->freq > h->dados[i]->freq) {
        trocar(&h->dados[i], &h->dados[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Remove a raiz (menor elemento), coloca o último elemento no lugar e reordena
HuffmanNode *removerMin(MinHeap *h) {
    if (h->tamanho == 0) return NULL;
    
    HuffmanNode *temp = h->dados[0];
    h->dados[0] = h->dados[--h->tamanho]; // Pega o último e põe no topo
    descer(h, 0); // Reorganiza a heap
    return temp;
}