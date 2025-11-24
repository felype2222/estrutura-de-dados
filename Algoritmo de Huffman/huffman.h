#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "heap.h"

/**
 * Nó da Árvore de Huffman.
 * Pode ser um nó folha (tem caractere) ou nó interno (tem caractere '$' e filhos).
 */
typedef struct HuffmanNode {
    char caractere;             // O caractere (apenas para folhas)
    int freq;                   // Frequência acumulada
    struct HuffmanNode *esq;    // Filho Esquerdo (Bit 0)
    struct HuffmanNode *dir;    // Filho Direito (Bit 1)
} HuffmanNode;

// --- GESTÃO DA ÁRVORE ---
HuffmanNode *criarNo(char caractere, int freq);
HuffmanNode *construirHuffman(char caracteres[], int freq[], int n);
void liberarArvore(HuffmanNode *raiz);

// --- VISUALIZAÇÃO E TABELAS ---
void imprimirCodigos(HuffmanNode *raiz, int arr[], int topo);
void gerarTabelaCodigos(HuffmanNode *raiz, char codigoAtual[], int profundidade, char tabela[256][100]);

// --- LÓGICA DE DADOS ---
void atualizarFrequencias(const char *frase, int freqGlobal[256]);
void gerarVetoresParaHeap(int freqGlobal[256], char **outChars, int **outFreq, int *outN);

// --- CODIFICAÇÃO E DECODIFICAÇÃO ---
void codificarFrase(const char *frase, char tabela[256][100]);
void decodificarFrase(HuffmanNode *raiz, const char *binario);

// --- ESTATÍSTICAS ---
void calcularTaxaCompressao(char tabela[256][100], int freqGlobal[256]);

#endif