#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bst.h"
#include "rbt.h"

int gerarChave() { // Gera uma chave aleatória entre 0 e 99999
    return rand() % 100000;
}

int main() { // Função principal para comparar desempenho entre BST e RBT
    FILE *arquivo = fopen("resultados.txt", "w"); // Abre arquivo para salvar resultados
    if (!arquivo) {
        printf("Erro ao criar arquivo de saída.\n");
        return 1;
    }

    srand(time(NULL)); // Inicializa gerador de números aleatórios
    fprintf(arquivo, "Total de nos\tTempo BST (ms)\tTempo Rubro-Negra (ms)\n"); // Cabeçalho do arquivo

    for (int n = 10000; n <= 100000; n += 10000) { // Testa para diferentes tamanhos de árvore
        NoBST* raizBST = NULL;
        NoRBT* raizRBT = NULL;

        for (int i = 0; i < n; i++) { // Insere n nós em ambas as árvores
            int chave = gerarChave();
            raizBST = inserirBST(raizBST, chave);
            raizRBT = inserirRBT(raizRBT, chave);
        }

        clock_t inicioBST = clock(); // Mede tempo de busca na BST
        for (int i = 0; i < n; i++) {
            int chave = gerarChave();
            buscarBST(raizBST, chave);
        }
        clock_t fimBST = clock(); // Mede tempo de busca na RBT
        double tempoBST = ((double)(fimBST - inicioBST) / CLOCKS_PER_SEC) * 1000.0;

        clock_t inicioRBT = clock(); // Mede tempo de busca na RBT
        for (int i = 0; i < n; i++) {
            int chave = gerarChave();
            buscarRBT(raizRBT, chave);
        }
        clock_t fimRBT = clock(); // Finaliza medição de tempo
        double tempoRBT = ((double)(fimRBT - inicioRBT) / CLOCKS_PER_SEC) * 1000.0;

        fprintf(arquivo, "%d\t%.2f\t%.2f\n", n, tempoBST, tempoRBT); // Salva resultados no arquivo
        printf("n=%d -> BST: %.2f ms | RBT: %.2f ms\n", n, tempoBST, tempoRBT); // Mostra resultados no console

        liberarBST(raizBST);
        liberarRBT(raizRBT);
    }

    fclose(arquivo); // Fecha o arquivo
    printf("\nResultados salvos em 'resultados.txt'.\n"); 

    return 0;
}


