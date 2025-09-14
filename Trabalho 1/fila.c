#include "fila.h"
#include <stdio.h> 
#include <stdlib.h> 

void inicializar(Fila *f) { // Função para inicializar a fila
    f->inicio = 0; 
    f->fim = -1; 
    f->tamanho = 0; 
}

int vazia(Fila *f) { // Função para verificar se a fila está vazia
    return f->tamanho == 0; 
}

int cheia(Fila *f) { // Função para verificar se a fila está cheia
    return f->tamanho == MAX; 
}

int enfileirar(Fila *f, int valor) { // Função para adicionar um elemento à fila
    if (cheia(f)) {
        return 0; // Fila cheia
    }
    f->fim = (f->fim + 1) % MAX; 
    f->itens[f->fim] = valor; 
    f->tamanho++; 
    return 1; // Sucesso
}

int desenfileirar(Fila *f, int *removido) { // Função para remover um elemento da fila
    if (vazia(f)) {
        return 0; // Fila vazia
    }
    *removido = f->itens[f->inicio]; 
    f->inicio = (f->inicio + 1) % MAX; 
    f->tamanho--; 
    return 1; // Sucesso
}

void imprimirFila(Fila *f) { // Função para imprimir os elementos da fila
    if (vazia(f)) {
        printf("Fila vazia.\n");
        return;
    }
    printf("Elementos na fila: ");
    for (int i = 0; i < f->tamanho; i++) {
        int index = (f->inicio + i) % MAX; 
        printf("%d ", f->itens[index]);
    }
    printf("\n");
}
