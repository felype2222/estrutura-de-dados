#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

// ordenação por distribuição usando filas sequenciais

int obterDigito(int numero, int posicao) { // Função para obter o dígito na posição especificada
    for (int i = 0; i < posicao; i++) {
        numero /= 10;
    }
    return numero % 10;
}

void RadixSort(int *array, int tamanho) { // Função para ordenar o array usando Radix Sort
    Fila filas[10]; // Cria 10 filas para os dígitos de 0 a 9
    for (int i = 0; i < 10; i++) {
        inicializar(&filas[i]); // Inicializa cada fila
    }

    int maxNumero = array[0];
    for (int i = 1; i < tamanho; i++) { // Encontra o maior número no array
        if (array[i] > maxNumero) {
            maxNumero = array[i];
        }
    }

    for(int posicao = 0; maxNumero > 0; posicao++) { // Para cada posição de dígito
        for (int i = 0; i < tamanho; i++) {
            int digito = obterDigito(array[i], posicao); // Obtém o dígito na posição atual
            enfileirar(&filas[digito], array[i]); // Enfileira o número na fila correspondente ao dígito
        }

        int index = 0;
        for (int i = 0; i < 10; i++) { // Desenfileira os números das filas e os coloca de volta no array
            while (!vazia(&filas[i])) {
                int numero;
                desenfileirar(&filas[i], &numero);
                array[index++] = numero;
            }
        }
        maxNumero /= 10; // Move para a próxima posição de dígito
    }
}

int main() {
    int array[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int tamanho = sizeof(array) / sizeof(array[0]);

    printf("Array original:\n");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    RadixSort(array, tamanho); // Chama a função de ordenação

    printf("Array ordenado:\n");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}