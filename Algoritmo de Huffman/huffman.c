#include "huffman.h"
#include <string.h> // Necessário para manipulação de strings (strcpy, strlen)

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

// Troca dois nós de lugar
void trocar(HuffmanNode **a, HuffmanNode **b) {
    HuffmanNode *temp = *a;
    *a = *b;
    *b = temp;
}

// Mantém a propriedade de heap mínima
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

// Constrói a Árvore de Huffman
HuffmanNode *construirHuffman(char caracteres[], int freq[], int n) {
    MinHeap *h = construirHeap(caracteres, freq, n);

    while (h->tamanho > 1) {
        HuffmanNode *esq = removerMin(h);
        HuffmanNode *dir = removerMin(h);

        HuffmanNode *novo = criarNo('$', esq->freq + dir->freq);
        novo->esq = esq;
        novo->dir = dir;

        inserirHeap(h, novo);
    }

    HuffmanNode *raiz = removerMin(h);
    free(h->dados);
    free(h);
    return raiz;
}

// Imprime os códigos recursivamente (Visualização da árvore)
void imprimirCodigos(HuffmanNode *raiz, int arr[], int topo) {
    if (!raiz) return;

    if (raiz->esq) {
        arr[topo] = 0;
        imprimirCodigos(raiz->esq, arr, topo + 1);
    }

    if (raiz->dir) {
        arr[topo] = 1;
        imprimirCodigos(raiz->dir, arr, topo + 1);
    }

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

// --- IMPLEMENTAÇÃO DAS NOVAS FUNÇÕES ---

// Percorre a árvore e preenche a tabela de códigos
void gerarTabelaCodigos(HuffmanNode *raiz, char codigoAtual[], int profundidade, char tabela[256][100]) {
    if (!raiz) return;

    // Se for nó folha, o caminho atual é o código do caractere
    if (!raiz->esq && !raiz->dir) {
        codigoAtual[profundidade] = '\0'; // Fecha a string
        unsigned char indice = (unsigned char)raiz->caractere;
        strcpy(tabela[indice], codigoAtual); // Copia para a tabela na posição do char ASCII
        return;
    }

    // Se for para a esquerda, adiciona '0'
    if (raiz->esq) {
        codigoAtual[profundidade] = '0';
        gerarTabelaCodigos(raiz->esq, codigoAtual, profundidade + 1, tabela);
    }

    // Se for para a direita, adiciona '1'
    if (raiz->dir) {
        codigoAtual[profundidade] = '1';
        gerarTabelaCodigos(raiz->dir, codigoAtual, profundidade + 1, tabela);
    }
}

// Recebe a frase e imprime a sequência de bits correspondente
void codificarFrase(const char *frase, char tabela[256][100]) {
    printf("\n=== RESULTADO DA CODIFICACAO ===\n");
    printf("Frase Original: \"%s\"\n", frase);
    printf("Binario Gerado: ");
    
    for (int i = 0; frase[i] != '\0'; i++) {
        unsigned char c = (unsigned char)frase[i];
        
        // Verifica se existe um código gerado para este caractere
        if (strlen(tabela[c]) > 0) {
            printf("%s ", tabela[c]); // Adicionei um espaço para facilitar a leitura
        } else {
            // Se o usuário digitou um caractere que não está na árvore
            printf("[?]"); 
        }
    }
    printf("\n");
}