#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bst.h"
#include "rbt.h"

int gerarChave() {
    return rand() % 100000;
}

int main() {
	int i, n;
    FILE *arquivo = fopen("resultados.txt", "w");
    if (!arquivo) {
        printf("Erro ao criar arquivo de saída.\n");
        return 1;
    }

    srand(time(NULL));
    fprintf(arquivo, "Total de nos\tTempo BST (ms)\tTempo Rubro-Negra (ms)\n");

    for (n = 1000; n <= 10000; n += 1000) {
        NoBST* raizBST = NULL;
        NoRBT* raizRBT = NULL;

        for (i = 0; i < n; i++) {
            int chave = gerarChave();
            raizBST = inserirBST(raizBST, chave);
            raizRBT = inserirRBT(raizRBT, chave);
        }

        clock_t inicioBST = clock();
        for (i = 0; i < n; i++) {
            int chave = gerarChave();
            buscarBST(raizBST, chave);
        }
        clock_t fimBST = clock();
        double tempoBST = ((double)(fimBST - inicioBST) / CLOCKS_PER_SEC) * 1000.0;

        clock_t inicioRBT = clock();
        for (i = 0; i < n; i++) {
            int chave = gerarChave();
            buscarRBT(raizRBT, chave);
        }
        clock_t fimRBT = clock();
        double tempoRBT = ((double)(fimRBT - inicioRBT) / CLOCKS_PER_SEC) * 1000.0;

        fprintf(arquivo, "%d\t%.2f\t%.2f\n", n, tempoBST, tempoRBT);
        printf("n=%d -> BST: %.2f ms | RBT: %.2f ms\n", n, tempoBST, tempoRBT);

        liberarBST(raizBST);
        liberarRBT(raizRBT);
    }

    fclose(arquivo);
    printf("\nResultados salvos em 'resultados.txt'.\n");

    return 0;
}

