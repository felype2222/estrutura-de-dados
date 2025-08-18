#include <stdio.h>
#define MAX 100

typedef struct {
    int itens[MAX];
    int tamanho;
} Lista;

void inicializar(Lista *lista) {
    lista->tamanho = 0;
}

void imprimir(Lista *lista) {
    for (int i = 0; i < lista->tamanho; i++) {
        printf("%d ", lista->itens[i]);
    }
    printf("\n");
}

int inserir(Lista *lista, int valor) {
    if (lista->tamanho == MAX) {
        printf("Lista cheia!\n");
       return 0;
    }
    
    int i = lista->tamanho - 1;
    while (i >= 0 && lista->itens[i] > valor) {
        lista->itens[i + 1] = lista->itens[i];
        i--;
    }
    lista->itens[i + 1] = valor;
    lista->tamanho++;
    return 1;
}

int remover(Lista *lista, int valor) {
    if (lista->tamanho == 0) {
        printf("Lista vazia!\n");
        return 0;
    }

    int i;
    for (i = 0; i < lista->tamanho; i++) {
        if (lista->itens[i] == valor) {
            break;
        }
    }

    if (i == lista->tamanho) {
        printf("Valor não encontrado!\n");
        return 0;
    }

    for (int j = i; j < lista->tamanho - 1; j++) {
        lista->itens[j] = lista->itens[j + 1];
    }
    lista->tamanho--;
    return 1;
}

int main(){
    Lista lista;
    inicializar(&lista);

    inserir(&lista, 5);
    inserir(&lista, 3);
    inserir(&lista, 8);
    imprimir(&lista);

    remover(&lista, 3);
    imprimir(&lista);

    return 0;
}
