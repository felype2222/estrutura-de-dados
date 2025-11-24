#include "huffman.h"
#include <string.h>

// Função auxiliar para limpar o buffer de entrada (stdin)
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int main() {
    int n = 0;
    int capacidade_atual = 0;
    char *caracteres = NULL;
    int *freq = NULL;
    int opcao;

    printf("=== INICIALIZACAO HUFFMAN ===\n");
    printf("Quantos caracteres iniciais deseja inserir? ");
    if (scanf("%d", &n) != 1) n = 0; 
    limparBuffer();

    if (n > 0) {
        caracteres = (char *)malloc(n * sizeof(char));
        freq = (int *)malloc(n * sizeof(int));
        capacidade_atual = n;

        printf("\nDigite cada caractere e sua frequencia:\n");
        for (int i = 0; i < n; i++) {
            printf("Caractere %d: ", i + 1);
            scanf("%c", &caracteres[i]);
            limparBuffer();
            
            printf("Frequencia de '%c': ", caracteres[i]);
            scanf("%d", &freq[i]);
            limparBuffer();
        }
    }

    // Constrói a árvore inicial
    HuffmanNode *raiz = NULL;
    if (n > 0) {
        raiz = construirHuffman(caracteres, freq, n);
    }

    int arr[100]; // Buffer para armazenar os códigos (0s e 1s)
    int topo = 0;

    do {
        printf("\n===== MENU HUFFMAN =====\n");
        printf("1 - Mostrar codigos de Huffman\n");
        printf("2 - Inserir novo caractere (Recalcular arvore)\n");
        printf("3 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBuffer();

        if (opcao == 1) {
            if (raiz) {
                printf("\n--- Codigos Gerados ---\n");
                imprimirCodigos(raiz, arr, topo);
            } else {
                printf("\nA arvore esta vazia!\n");
            }
        } 
        else if (opcao == 2) {
            char novo;
            int f;
            printf("Novo caractere: ");
            scanf("%c", &novo);
            limparBuffer();
            printf("Frequencia: ");
            scanf("%d", &f);
            limparBuffer();

            // 1. Atualizar arrays usando realloc (MUITO mais seguro e limpo)
            n++;
            char *tempC = realloc(caracteres, n * sizeof(char));
            int *tempF = realloc(freq, n * sizeof(int));

            if (!tempC || !tempF) {
                printf("Erro critico de memoria ao redimensionar!\n");
                // Em caso real, deveria tratar o erro liberando tudo
                break; 
            }

            caracteres = tempC;
            freq = tempF;

            // 2. Inserir os novos dados
            caracteres[n - 1] = novo;
            freq[n - 1] = f;

            // 3. Liberar a árvore antiga antes de criar a nova
            if (raiz) {
                liberarArvore(raiz);
            }

            // 4. Reconstruir a árvore com os novos dados
            raiz = construirHuffman(caracteres, freq, n);
            printf("\nCaractere inserido e arvore reconstruida com sucesso!\n");
        }

    } while (opcao != 3);

    // Limpeza final
    if (raiz) liberarArvore(raiz);
    if (caracteres) free(caracteres);
    if (freq) free(freq);

    printf("Saindo...\n");
    return 0;
}