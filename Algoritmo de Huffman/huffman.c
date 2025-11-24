#include "huffman.h"

// Cria um novo nó da árvore
HuffmanNode *criarNo(char caractere, int freq) {
    HuffmanNode *novo = (HuffmanNode *)malloc(sizeof(HuffmanNode));
    if (!novo) {
        fprintf(stderr, "Erro de alocacao de memoria\n");
        exit(1);
    }
    novo->caractere = caractere;
    novo->freq = freq;
    novo->esq = novo->dir = NULL;
    return novo;
}

// Cria a estrutura da Heap
MinHeap *criarHeap(int capacidade) {
    MinHeap *h = (MinHeap *)malloc(sizeof(MinHeap));
    h->dados = (HuffmanNode **)malloc(capacidade * sizeof(HuffmanNode *));
    h->capacidade = capacidade;
    h->tamanho = 0;
    return h;
}

// Troca dois nós de lugar (auxiliar para a heap)
void trocar(HuffmanNode **a, HuffmanNode **b) {
    HuffmanNode *temp = *a;
    *a = *b;
    *b = temp;
}

// Mantém a propriedade de heap mínima (Min-Heapify)
void descer(MinHeap *h, int i) {
    int menor = i;
    int esq = 2 * i + 1;
    int dir = 2 * i + 2;

    if (esq < h->tamanho && h->dados[esq]->freq < h->dados[menor]->freq)
        menor = esq;

    if (dir < h->tamanho && h->dados[dir]->freq < h->dados[menor]->freq)
        menor = dir;

    if (menor != i) {
        trocar(&h->dados[i], &h->dados[menor]);
        descer(h, menor);
    }
}

// Insere um nó na heap
void inserirHeap(MinHeap *h, HuffmanNode *node) {
    int i = h->tamanho++;
    h->dados[i] = node;

    // Subir o nó enquanto for menor que o pai
    while (i && h->dados[(i - 1) / 2]->freq > h->dados[i]->freq) {
        trocar(&h->dados[i], &h->dados[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Remove e retorna o nó com menor frequência
HuffmanNode *removerMin(MinHeap *h) {
    if (h->tamanho == 0) return NULL;
    
    HuffmanNode *temp = h->dados[0];
    h->dados[0] = h->dados[--h->tamanho];
    descer(h, 0);
    return temp;
}

// Constrói a heap inicial
MinHeap *construirHeap(char caracteres[], int freq[], int n) {
    MinHeap *h = criarHeap(n);
    for (int i = 0; i < n; i++)
        inserirHeap(h, criarNo(caracteres[i], freq[i]));
    return h;
}

// Função principal: Constrói a Árvore de Huffman
HuffmanNode *construirHuffman(char caracteres[], int freq[], int n) {
    MinHeap *h = construirHeap(caracteres, freq, n);

    while (h->tamanho > 1) {
        // Extrai os dois menores
        HuffmanNode *esq = removerMin(h);
        HuffmanNode *dir = removerMin(h);

        // Cria um novo nó interno com a soma das frequências
        // '$' é usado como placeholder para nós internos
        HuffmanNode *novo = criarNo('$', esq->freq + dir->freq);
        novo->esq = esq;
        novo->dir = dir;

        inserirHeap(h, novo);
    }

    HuffmanNode *raiz = removerMin(h);
    
    // Limpeza da estrutura da heap (os nós da árvore persistem)
    free(h->dados);
    free(h);
    
    return raiz;
}

// Imprime os códigos recursivamente
void imprimirCodigos(HuffmanNode *raiz, int arr[], int topo) {
    if (!raiz) return;

    // Se for esquerda, adiciona 0
    if (raiz->esq) {
        arr[topo] = 0;
        imprimirCodigos(raiz->esq, arr, topo + 1);
    }

    // Se for direita, adiciona 1
    if (raiz->dir) {
        arr[topo] = 1;
        imprimirCodigos(raiz->dir, arr, topo + 1);
    }

    // Se for folha, imprime o caractere e o código
    if (!raiz->esq && !raiz->dir) {
        printf("['%c']: ", raiz->caractere);
        for (int i = 0; i < topo; i++)
            printf("%d", arr[i]);
        printf("\n");
    }
}

// Libera a memória da árvore recursivamente
void liberarArvore(HuffmanNode *raiz) {
    if (!raiz) return;
    liberarArvore(raiz->esq);
    liberarArvore(raiz->dir);
    free(raiz);
}