#include "heap.h"
#include <stdio.h>

void inicializar(Heap *H) { // Inicializa o heap
    H->n = 0;
}

int buscar(Heap *H, int chave) { // Busca uma chave no heap
    for (int i = 0; i < H->n; i++)
        if (H->T[i].chave == chave)
            return i;
    return -1;
}

void subir(Heap *H, int i) { // Move o elemento na posição i para cima
    Elem x = H->T[i];
    while (i > 0) {
        int pai = (i - 1) / 2;
        if (x.chave <= H->T[pai].chave) break;
        H->T[i] = H->T[pai];
        i = pai;
    }
    H->T[i] = x;
}

void descer(Heap *H, int i) { // Move o elemento na posição i para baixo
    Elem x = H->T[i];
    int n = H->n;
    while (2 * i + 1 < n) {
        int j = 2 * i + 1;
        if (j + 1 < n && H->T[j+1].chave > H->T[j].chave)
            j++;
        if (x.chave >= H->T[j].chave) break;
        H->T[i] = H->T[j];
        i = j;
    }
    H->T[i] = x;
}

void inserir(Heap *H, int chave) { // Insere uma nova chave no heap
    if (H->n == MAX) return;
    H->T[H->n].chave = chave;
    subir(H, H->n);
    H->n++;
}

void construir(Heap *H) { // Constrói o heap a partir de um array
    for (int i = (H->n - 2)/2; i >= 0; i--)
        descer(H, i);
}

void alterarPrioridade(Heap *H, int i, int novaChave) { // Altera a prioridade do elemento na posição i
    int antiga = H->T[i].chave;
    H->T[i].chave = novaChave;
    if (novaChave > antiga)
        subir(H, i);
    else
        descer(H, i);
}

int remover(Heap *H) { // Remove e retorna a chave do elemento no topo do heap
    if (H->n == 0) return -1;
    int max = H->T[0].chave;
    H->T[0] = H->T[H->n - 1];
    H->n--;
    descer(H, 0);
    return max;
}

void imprimir(Heap *H) { // Imprime os elementos do heap
    for (int i = 0; i < H->n; i++)
        printf("%d ", H->T[i].chave);
    printf("\n");
}
