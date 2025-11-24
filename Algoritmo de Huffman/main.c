#include "huffman.h"
#include <string.h>

// Função auxiliar para limpar o buffer de entrada
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int main() {
    int n = 0;
    char *caracteres = NULL;
    int *freq = NULL;
    int opcao;

    // Variáveis para a nova funcionalidade de codificação
    char tabelaCodigos[256][100]; // Tabela lookup: ASCII -> String de bits
    char bufferCaminho[100];      // Buffer auxiliar para recursão

    printf("=== INICIALIZACAO HUFFMAN ===\n");
    printf("Quantos caracteres iniciais deseja inserir? ");
    if (scanf("%d", &n) != 1) n = 0; 
    limparBuffer();

    if (n > 0) {
        caracteres = (char *)malloc(n * sizeof(char));
        freq = (int *)malloc(n * sizeof(int));

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

    int arr[100]; // Buffer antigo para impressão visual da árvore
    int topo = 0;

    do {
        // Limpa a tabela de códigos para garantir que não haja lixo de memória
        // ou dados antigos se a árvore mudou
        for(int k=0; k<256; k++) tabelaCodigos[k][0] = '\0';
        
        // Se a árvore existe, gera a tabela de lookup atualizada
        if (raiz) {
            gerarTabelaCodigos(raiz, bufferCaminho, 0, tabelaCodigos);
        }

        printf("\n===== MENU HUFFMAN =====\n");
        printf("1 - Mostrar tabela de codigos\n");
        printf("2 - Inserir novo caractere (Recalcular arvore)\n");
        printf("3 - Codificar uma frase\n");
        printf("4 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBuffer();

        if (opcao == 1) {
            if (raiz) {
                printf("\n--- Estrutura da Arvore ---\n");
                imprimirCodigos(raiz, arr, topo);
            } else {
                printf("\nA arvore esta vazia! Insira dados primeiro.\n");
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

            // Realoca memória
            n++;
            char *tempC = realloc(caracteres, n * sizeof(char));
            int *tempF = realloc(freq, n * sizeof(int));

            if (!tempC || !tempF) {
                printf("Erro critico de memoria!\n");
                break; 
            }
            caracteres = tempC;
            freq = tempF;

            caracteres[n - 1] = novo;
            freq[n - 1] = f;

            if (raiz) liberarArvore(raiz);
            raiz = construirHuffman(caracteres, freq, n);
            printf("\nArvore atualizada com sucesso!\n");
        }
        else if (opcao == 3) {
            if (!raiz) {
                printf("\nErro: A arvore esta vazia. Crie-a primeiro.\n");
            } else {
                char frase[1024];
                printf("\nDigite a frase para codificar (use apenas caracteres da arvore): ");
                
                // Lê a frase inteira, incluindo espaços
                if (fgets(frase, sizeof(frase), stdin)) {
                    // Remove a quebra de linha (\n) que o fgets captura
                    frase[strcspn(frase, "\n")] = 0;
                    codificarFrase(frase, tabelaCodigos);
                }
            }
        }

    } while (opcao != 4);

    // Limpeza final
    if (raiz) liberarArvore(raiz);
    if (caracteres) free(caracteres);
    if (freq) free(freq);

    printf("Saindo...\n");
    return 0;
}