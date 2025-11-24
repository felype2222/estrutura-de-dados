#include "huffman.h"
#include <string.h>

// Aloca memória para um novo nó
HuffmanNode *criarNo(char caractere, int freq) {
    HuffmanNode *novo = (HuffmanNode *)malloc(sizeof(HuffmanNode));
    novo->caractere = caractere;
    novo->freq = freq;
    novo->esq = novo->dir = NULL;
    return novo;
}

// Função auxiliar interna para preencher a Heap inicial
MinHeap *inicializarHeapComDados(char caracteres[], int freq[], int n) {
    MinHeap *h = criarHeap(n);
    for (int i = 0; i < n; i++)
        inserirHeap(h, criarNo(caracteres[i], freq[i]));
    return h;
}

// Constrói a árvore completa a partir dos vetores de dados
HuffmanNode *construirHuffman(char caracteres[], int freq[], int n) {
    MinHeap *h = inicializarHeapComDados(caracteres, freq, n);

    // TRATAMENTO DE CASO BORDA: Apenas 1 tipo de caractere (ex: "aaa")
    // Cria uma raiz artificial para garantir que o caractere tenha um código (bit 0)
    if (h->tamanho == 1) {
        HuffmanNode *unico = removerMin(h);
        HuffmanNode *raizArtificial = criarNo('$', unico->freq);
        raizArtificial->esq = unico;
        raizArtificial->dir = NULL;
        inserirHeap(h, raizArtificial);
    }

    // Loop principal: Combina os dois menores até sobrar apenas a raiz
    while (h->tamanho > 1) {
        HuffmanNode *esq = removerMin(h);
        HuffmanNode *dir = removerMin(h);

        // O novo nó interno tem a soma das frequências
        HuffmanNode *novo = criarNo('$', esq->freq + dir->freq);
        novo->esq = esq;
        novo->dir = dir;

        inserirHeap(h, novo);
    }

    HuffmanNode *raiz = removerMin(h);
    free(h->dados); // Libera a estrutura da heap, mas mantém os nós da árvore
    free(h);
    return raiz;
}

// Imprime a árvore recursivamente (Formatado como tabela)
void imprimirCodigos(HuffmanNode *raiz, int arr[], int topo) {
    if (!raiz) return;

    // Navega para esquerda (bit 0)
    if (raiz->esq) { 
        arr[topo] = 0; 
        imprimirCodigos(raiz->esq, arr, topo + 1); 
    }

    // Navega para direita (bit 1)
    if (raiz->dir) { 
        arr[topo] = 1; 
        imprimirCodigos(raiz->dir, arr, topo + 1); 
    }

    // Se for folha, imprime os dados
    if (!raiz->esq && !raiz->dir) {
        printf("| %-9c | %-5d | ", raiz->caractere, raiz->freq);
        for (int i = 0; i < topo; i++) printf("%d", arr[i]);
        printf("\n");
    }
}

// Libera memória de todos os nós (Pós-ordem)
void liberarArvore(HuffmanNode *raiz) {
    if (!raiz) return;
    liberarArvore(raiz->esq);
    liberarArvore(raiz->dir);
    free(raiz);
}

// Percorre a árvore para gerar strings de bits para cada char (Lookup Table)
void gerarTabelaCodigos(HuffmanNode *raiz, char codigoAtual[], int profundidade, char tabela[256][100]) {
    if (!raiz) return;

    if (!raiz->esq && !raiz->dir) {
        codigoAtual[profundidade] = '\0';
        strcpy(tabela[(unsigned char)raiz->caractere], codigoAtual);
        return;
    }

    if (raiz->esq) {
        codigoAtual[profundidade] = '0';
        gerarTabelaCodigos(raiz->esq, codigoAtual, profundidade + 1, tabela);
    }
    if (raiz->dir) {
        codigoAtual[profundidade] = '1';
        gerarTabelaCodigos(raiz->dir, codigoAtual, profundidade + 1, tabela);
    }
}

// Contabiliza frequência de caracteres numa frase (acumulativo)
void atualizarFrequencias(const char *frase, int freqGlobal[256]) {
    for (int i = 0; frase[i] != '\0'; i++) {
        if (frase[i] != '\n') { // Ignora quebras de linha
            freqGlobal[(unsigned char)frase[i]]++;
        }
    }
}

// Transforma o array global de frequências em vetores para a Heap
void gerarVetoresParaHeap(int freqGlobal[256], char **outChars, int **outFreq, int *outN) {
    int n = 0;
    for (int i = 0; i < 256; i++) {
        if (freqGlobal[i] > 0) n++;
    }

    char *caracteres = (char *)malloc(n * sizeof(char));
    int *freq = (int *)malloc(n * sizeof(int));

    int k = 0;
    for (int i = 0; i < 256; i++) {
        if (freqGlobal[i] > 0) {
            caracteres[k] = (char)i;
            freq[k] = freqGlobal[i];
            k++;
        }
    }
    *outChars = caracteres;
    *outFreq = freq;
    *outN = n;
}

// Converte texto em binário visual
void codificarFrase(const char *frase, char tabela[256][100]) {
    printf("\n>>> RESULTADO CODIFICADO (Binario):\n");
    printf("--------------------------------------------------\n");
    for (int i = 0; frase[i] != '\0'; i++) {
        if (frase[i] == '\n') continue;
        
        unsigned char c = (unsigned char)frase[i];
        
        if (strlen(tabela[c]) > 0) {
            printf("%s ", tabela[c]);
        } else {
            printf("[?] "); // Erro: char não treinado
        }
    }
    printf("\n--------------------------------------------------\n");
}

// Converte binário em texto
void decodificarFrase(HuffmanNode *raiz, const char *binario) {
    HuffmanNode *atual = raiz;
    printf("\n>>> RESULTADO DECODIFICADO (Texto):\n");
    printf("--------------------------------------------------\n");
    
    for (int i = 0; binario[i] != '\0'; i++) {
        if (binario[i] == ' ') continue; // Pula espaços

        // Validação de entrada
        if (binario[i] != '0' && binario[i] != '1') {
            printf("[?]");
            atual = raiz;
            continue;
        }

        // Navegação
        if (binario[i] == '0') {
            if (atual->esq) atual = atual->esq;
            else { printf("[?]"); atual = raiz; continue; }
        } 
        else if (binario[i] == '1') {
            if (atual->dir) atual = atual->dir;
            else { printf("[?]"); atual = raiz; continue; }
        }

        // Achou folha
        if (!atual->esq && !atual->dir) {
            printf("%c", atual->caractere);
            atual = raiz; // Reinicia para próxima letra
        }
    }

    if (atual != raiz) printf("[?]"); // Caminho incompleto
    printf("\n--------------------------------------------------\n");
}

// Relatório estatístico
void calcularTaxaCompressao(char tabela[256][100], int freqGlobal[256]) {
    long bitsOriginal = 0;
    long bitsComprimido = 0;
    long totalChars = 0;

    for (int i = 0; i < 256; i++) {
        if (freqGlobal[i] > 0) {
            totalChars += freqGlobal[i];
            bitsOriginal += freqGlobal[i] * 8; // ASCII padrão = 8 bits
            int tamanhoCodigo = strlen(tabela[i]);
            bitsComprimido += freqGlobal[i] * tamanhoCodigo;
        }
    }

    if (bitsOriginal == 0) return;

    float economia = (1.0f - ((float)bitsComprimido / bitsOriginal)) * 100;

    printf("\n");
    printf("==================================================\n");
    printf("           RELATORIO DE EFICIENCIA               \n");
    printf("==================================================\n");
    printf(" Caracteres Processados  : %ld\n", totalChars);
    printf(" Tamanho Original (8-bit): %ld bits\n", bitsOriginal);
    printf(" Tamanho Huffman         : %ld bits\n", bitsComprimido);
    printf("--------------------------------------------------\n");
    printf(" ECONOMIA REAL           : %.2f%%\n", economia);
    printf("==================================================\n");
}