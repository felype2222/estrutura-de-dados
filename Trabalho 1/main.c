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
    int tamanho; // Declara a variável tamanho

    printf("Digite o tamanho do array: ");
    scanf("%d", &tamanho);

    if (tamanho <=0) { // Valida o tamanho do array
        printf("Tamanho inválido. O tamanho deve ser um número positivo.\n");
        return 1;
    }

    int *array = (int *)malloc(tamanho * sizeof(int)); // Aloca memória para o array
    if (array == NULL) { // Verifica se a alocação foi bem-sucedida
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    printf("Digite os elementos do array:\n");
    for (int i = 0; i < tamanho; i++) { // Lê os elementos do array
        scanf("%d", &array[i]);
    }

    printf("Array original:\n");
    for (int i = 0; i < tamanho; i++) { // Imprime o array original
        printf("%d ", array[i]);
    }

    printf("\n");

    RadixSort(array, tamanho); // Chama a função de ordenação

    printf("Array ordenado:\n");
    for (int i = 0; i < tamanho; i++) { // Imprime o array ordenado
        printf("%d ", array[i]);
    }

    printf("\n");
    free(array); // Libera a memória alocada

    return 0;
}