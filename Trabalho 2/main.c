#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bst.h"
#include "rbt.h"

int gerarChave() { // Gera uma chave aleatória
    return rand() % 100000;
}

int main() {
    FILE *arquivo = fopen("resultados.txt", "w"); // Abre o arquivo para escrita
    if (!arquivo) {
        printf("Erro ao criar arquivo.\n");
        return 1;
    }

    srand(time(NULL)); // Inicializa a semente do gerador de números aleatórios
    fprintf(arquivo, "Total de nos\tTempo BST (ms)\tTempo RBT (ms)\n");

    for (int n = 10000; n <= 100000; n += 10000) { // Testa de 10.000 a 100.000 nós
        // Inicializa árvores
        ArvoreBST arvBST;
        inicializarBST(&arvBST);

        ArvoreRBT arvRBT;
        inicializarRBT(&arvRBT);

        for (int i = 0; i < n; i++) { // Insere n nós com chaves aleatórias
            int chave = gerarChave();
            arvBST.raiz = inserirBST(arvBST.raiz, chave);
            inserirRBT(&arvRBT, chave);
        }

        // medir tempo de busca BST
        clock_t iniBST = clock();
        for (int i = 0; i < n; i++) {
            buscarBST(arvBST.raiz, gerarChave());
        }
        clock_t fimBST = clock();
        double tempoBST = ((double)(fimBST - iniBST) / CLOCKS_PER_SEC) * 1000.0;

        // medir tempo de busca RBT
        clock_t iniRBT = clock();
        for (int i = 0; i < n; i++) {
            buscarRBT(&arvRBT, gerarChave());
        }
        clock_t fimRBT = clock();
        double tempoRBT = ((double)(fimRBT - iniRBT) / CLOCKS_PER_SEC) * 1000.0;

        fprintf(arquivo, "%d\t%.2f\t%.2f\n", n, tempoBST, tempoRBT); // Salva resultados no arquivo
        printf("n=%d -> BST: %.2f ms | RBT: %.2f ms\n", n, tempoBST, tempoRBT); // Exibe resultados no console

        // Libera memória
        liberarBST(arvBST.raiz);
        liberarRBT(&arvRBT, arvRBT.raiz);
        free(arvRBT.nil);
    }

    fclose(arquivo); // Fecha o arquivo
    printf("\nResultados salvos em 'resultados.txt'.\n"); 
    return 0;
}



