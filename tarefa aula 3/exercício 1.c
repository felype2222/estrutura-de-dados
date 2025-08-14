#include <stdio.h>

void LerMatriz(int linha, int coluna, int matriz[linha][coluna]) {
    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {
            printf("Digite o elemento [%d][%d]: ", i, j);
            scanf("%d", &matriz[i][j]);
        }
    }
}
void ImprimirMatriz(int linha, int coluna, int matriz[linha][coluna]) {
    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

void SomarMatrizes(int linha, int coluna, int matrizA[linha][coluna], int matrizB[linha][coluna], int matrizResultado[linha][coluna]) {
    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {
            matrizResultado[i][j] = matrizA[i][j] + matrizB[i][j];
        }
    }
}

void MultiplicarMatrizes(int linhaA, int colunaA, int matrizA[linhaA][colunaA], int linhaB, int colunaB, int matrizB[linhaB][colunaB], int matrizResultado[linhaA][colunaB]) {
    for (int i = 0; i < linhaA; i++) {
        for (int j = 0; j < colunaB; j++) {
            matrizResultado[i][j] = 0;
            for (int k = 0; k < colunaA; k++) {
                matrizResultado[i][j] += matrizA[i][k] * matrizB[k][j];
            }
        }
    }
}

int main(){

    int linha, coluna, linhaA, colunaA, linhaB, colunaB;

    printf("Digite o numero de linhas e colunas da matriz: ");
    scanf("%d%d", &linha, &coluna);

    int matrizA[linha][coluna];
    int matrizB[linha][coluna];
    int somaAB[linha][coluna];
    int matrizResultado[linha][coluna];

    printf("Digite os elementos da matriz A:\n");
    LerMatriz(linha, coluna, matrizA);

    printf("Digite os elementos da matriz B:\n");
    LerMatriz(linha, coluna, matrizB);

    SomarMatrizes(linha, coluna, matrizA, matrizB, somaAB);

    printf("Resultado da soma:\n");
    ImprimirMatriz(linha, coluna, somaAB);

    printf("Digite os elementos da matriz A para a multiplicação: \n");
    LerMatriz(linha, coluna, matrizA);

    printf("Digite os elementos da matriz B para a multiplicação: \n");
    LerMatriz(linha, coluna, matrizB);

    MultiplicarMatrizes(linha, coluna, matrizA, linha, coluna, matrizB, matrizResultado);

    printf("Resultado da multiplicação:\n");
    ImprimirMatriz(linha, coluna, matrizResultado);

    return 0;
}