#include "huffman.h"
#include <string.h>

// Limpa o buffer do teclado para evitar erros de leitura com scanf/fgets
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

// Pequena função para pausar a tela antes de voltar ao menu
void pausarTela() {
    printf("\nPressione [ENTER] para continuar...");
    limparBuffer();
    // Um getchar extra pode ser necessario dependendo de como o buffer parou, 
    // mas o limparBuffer geralmente resolve.
}

// Exibe o menu formatado
void mostrarMenu() {
    printf("\n");
    printf("==================================================\n");
    printf("           COMPRESSOR HUFFMAN - v2.0             \n");
    printf("==================================================\n");
    printf(" [1] TREINAR IA (Inserir dados no banco)\n");
    printf(" [2] CODIFICAR  (Texto -> Binario)\n");
    printf(" [3] DECODIFICAR (Binario -> Texto)\n");
    printf("--------------------------------------------------\n");
    printf(" [4] ESTATISTICAS (Tabela e Taxa de Compressao)\n");
    printf(" [5] RESETAR TUDO (Limpar Memoria)\n");
    printf(" [6] SAIR\n");
    printf("==================================================\n");
    printf(" Escolha uma opcao: ");
}

int main() {
    // Variáveis de Estado
    int frequenciasGlobais[256] = {0}; // Banco de dados persistente
    HuffmanNode *raiz = NULL;          // Ponteiro para a árvore
    
    // Variáveis Auxiliares
    int n = 0;
    char *caracteres = NULL;
    int *freq = NULL;
    char tabelaCodigos[256][100];
    char bufferCaminho[100];
    int opcao;

    do {
        mostrarMenu();
        if (scanf("%d", &opcao) != 1) {
            opcao = 0; // Evita loop infinito se digitar letra
            limparBuffer();
        } else {
            limparBuffer();
        }

        switch(opcao) {
            case 1: { // TREINAR
                char frase[1024];
                printf("\n>>> DIGITE A FRASE PARA TREINAMENTO:\n> ");
                if (fgets(frase, sizeof(frase), stdin)) {
                    frase[strcspn(frase, "\n")] = 0;

                    // Limpeza preventiva da árvore antiga para reconstrução
                    if (raiz) { liberarArvore(raiz); raiz = NULL; }
                    if (caracteres) { free(caracteres); caracteres = NULL; }
                    if (freq) { free(freq); freq = NULL; }

                    // Processamento
                    atualizarFrequencias(frase, frequenciasGlobais);
                    gerarVetoresParaHeap(frequenciasGlobais, &caracteres, &freq, &n);
                    raiz = construirHuffman(caracteres, freq, n);

                    // Gerar tabela atualizada
                    for(int k=0; k<256; k++) tabelaCodigos[k][0] = '\0';
                    gerarTabelaCodigos(raiz, bufferCaminho, 0, tabelaCodigos);

                    printf("\n[SUCESSO] Dados computados!\n");
                    codificarFrase(frase, tabelaCodigos);
                    calcularTaxaCompressao(tabelaCodigos, frequenciasGlobais);
                }
                pausarTela();
                break;
            }
            case 2: { // CODIFICAR
                if (!raiz) {
                    printf("\n[ERRO] O sistema ainda nao foi treinado. Use a Opcao 1.\n");
                } else {
                    char frase[1024];
                    printf("\n>>> DIGITE O TEXTO PARA CODIFICAR:\n> ");
                    if (fgets(frase, sizeof(frase), stdin)) {
                        frase[strcspn(frase, "\n")] = 0;
                        codificarFrase(frase, tabelaCodigos);
                    }
                }
                pausarTela();
                break;
            }
            case 3: { // DECODIFICAR
                if (!raiz) {
                    printf("\n[ERRO] Arvore vazia.\n");
                } else {
                    char binario[2048];
                    printf("\n>>> DIGITE O CODIGO BINARIO (ex: 10 0 11):\n> ");
                    if (fgets(binario, sizeof(binario), stdin)) {
                        binario[strcspn(binario, "\n")] = 0;
                        decodificarFrase(raiz, binario);
                    }
                }
                pausarTela();
                break;
            }
            case 4: { // ESTATÍSTICAS
                if (raiz) {
                    int arr[100];
                    printf("\n=== TABELA DE CODIGOS ===\n");
                    printf("| Caractere | Freq  | Codigo Huffman\n");
                    printf("|-----------|-------|----------------\n");
                    imprimirCodigos(raiz, arr, 0);
                    calcularTaxaCompressao(tabelaCodigos, frequenciasGlobais);
                } else {
                    printf("\n[INFO] Nenhum dado processado ainda.\n");
                }
                pausarTela();
                break;
            }
            case 5: { // RESET
                for(int i=0; i<256; i++) frequenciasGlobais[i] = 0;
                if (raiz) { liberarArvore(raiz); raiz = NULL; }
                if (caracteres) { free(caracteres); caracteres = NULL; }
                if (freq) { free(freq); freq = NULL; }
                printf("\n[INFO] Memoria resetada com sucesso!\n");
                pausarTela();
                break;
            }
            case 6:
                printf("\nEncerrando sistema...\n");
                break;
            default:
                printf("\n[ERRO] Opcao invalida!\n");
                pausarTela();
        }

    } while (opcao != 6);

    // Limpeza final de memória ao sair do programa
    if (raiz) liberarArvore(raiz);
    if (caracteres) free(caracteres);
    if (freq) free(freq);
    
    return 0;
}