#include <stdio.h>
#define MAX 100

typedef struct {
    int items[MAX];
    int topo;
} Pilha;

void Inicializar(Pilha *p) {
    p->topo = -1;
}

int EstaCheio(Pilha *p) {
    return p->topo == MAX - 1;
}

int EstaVazia(Pilha *p) {
    return p->topo == -1;
}

int Inserir(Pilha *p, int valor) {
    if (EstaCheio(p)) {
        printf("Pilha cheia! Nao eh possivel inserir %d\n", valor);
        return 0;
    }
    p->items[++p->topo] = valor;
    return 1;
}

int Remover(Pilha *p) {
    if (EstaVazia(p)) {
        printf("Pilha vazia! Nao eh possivel remover elemento.\n");
        return -1;
    }
    return p->items[p->topo--];
}

void Imprimir(Pilha *p) {
    if (EstaVazia(p)) {
        printf("Pilha vazia! Nao ha elementos para imprimir.\n");
        return;
    }
    printf("Elementos da pilha: ");
    for (int i = 0; i <= p->topo; i++) {
        printf("%d ", p->items[i]);
    }
    printf("\n");
}

int main(){
    Pilha p;
    Inicializar(&p);

    Inserir(&p, 10);
    Inserir(&p, 20);
    Inserir(&p, 30);

    Imprimir(&p);

    printf("Elemento removido: %d\n", Remover(&p));
    Imprimir(&p);

    return 0;
}