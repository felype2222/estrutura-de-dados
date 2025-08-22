#include <stdio.h>
#define MAX 100

typedef struct {
    int items[MAX];
    int frente;
    int tras;
    int tamanho;
} Fila;

void Inicializar(Fila *f) {
    f->frente = 0;
    f->tras = -1;
    f->tamanho = 0;
}

int EstaCheio(Fila *f) {
    return f->tamanho == MAX;
}

int EstaVazia(Fila *f) {
    return f->tamanho == 0;
}

int Inserir(Fila *f, int valor) {
    if (EstaCheio(f)) {
        printf("Fila cheia! Nao eh possivel inserir %d\n", valor);
        return 0;
    }
    f->tras = (f->tras + 1) % MAX;
    f->items[f->tras] = valor;
    f->tamanho++;
    return 1;
}

int Remover(Fila *f) {
    if (EstaVazia(f)) {
        printf("Fila vazia! Nao eh possivel remover elemento.\n");
        return -1;
    }
    int valor = f->items[f->frente];
    f->frente = (f->frente + 1) % MAX;
    f->tamanho--;
    return valor;
}

void Imprimir(Fila *f) {
    if (EstaVazia(f)) {
        printf("Fila vazia! Nao ha elementos para imprimir.\n");
        return;
    }
    printf("Elementos da fila: ");
    for (int i = 0; i < f->tamanho; i++) {
        printf("%d ", f->items[(f->frente + i) % MAX]);
    }
    printf("\n");
}

int main(){
    Fila f;
    Inicializar(&f);

    Inserir(&f, 10);
    Inserir(&f, 20);
    Inserir(&f, 30);

    Imprimir(&f);

    printf("Elemento removido: %d\n", Remover(&f));
    Imprimir(&f);

    return 0;
}
