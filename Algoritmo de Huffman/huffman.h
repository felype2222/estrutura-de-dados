#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdio.h>
#include <stdlib.h>

// Estrutura de nó da árvore de Huffman
typedef struct HuffmanNode {
    char caractere;             // O caractere armazenado (ou '$' para nós internos)
    int freq;                   // Frequência do caractere
    struct HuffmanNode *esq;    // Ponteiro para filho esquerdo
    struct HuffmanNode *dir;    // Ponteiro para filho direito
} HuffmanNode;

// Estrutura para a Heap Mínima (Priority Queue)
typedef struct {
    HuffmanNode **dados;        // Array de ponteiros para nós
    int tamanho;                // Tamanho atual da heap
    int capacidade;             // Capacidade máxima
} MinHeap;

// Funções de criação e manipulação
HuffmanNode *criarNo(char caractere, int freq);
MinHeap *criarHeap(int capacidade);

// Funções da Heap
void inserirHeap(MinHeap *h, HuffmanNode *node);
HuffmanNode *removerMin(MinHeap *h);
MinHeap *construirHeap(char caracteres[], int freq[], int n);

// Funções principais de Huffman
HuffmanNode *construirHuffman(char caracteres[], int freq[], int n);
void imprimirCodigos(HuffmanNode *raiz, int arr[], int topo);
void liberarArvore(HuffmanNode *raiz); // NOVA: Para limpar memória

#endif