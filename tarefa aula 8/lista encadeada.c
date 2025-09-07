#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No* prox;
} No;

No* Buscar(No* inicio, int valor) {
    No* atual = inicio;
    while (atual != NULL) {
        if (atual->valor == valor) {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}

void Inserir(No** inicio, int valor) {
    No* novoNo = (No*)malloc(sizeof(No));
    if (!novoNo) {
        printf("Erro ao alocar memoria!\n");
        return;
    }
    novoNo->valor = valor;
    novoNo->prox = *inicio;
    *inicio = novoNo;
}

int Remover(No** inicio, int valor) {
    No* atual = *inicio;
    No* anterior = NULL;

    while (atual != NULL && atual->valor != valor) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        return 0; // Valor nao encontrado
    }

    if (anterior == NULL) {
        *inicio = atual->prox; // Remover o primeiro no
    } else {
        anterior->prox = atual->prox; // Remover no do meio ou final
    }

    free(atual);
    return 1; // Remocao bem-sucedida
}

void Imprimir(No* inicio) {
    No* atual = inicio;
    if (atual == NULL) {
        printf("Lista vazia!\n");
        return;
    }
    printf("Elementos da lista: ");
    while (atual != NULL) {
        printf("%d ", atual->valor);
        atual = atual->prox;
    }
    printf("\n");
}

void LiberarLista(No** inicio) {
    No* atual = *inicio;
    No* proximo;

    while (atual != NULL) {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }

    *inicio = NULL;
}

int main(){
    No* lista = NULL;

    Inserir(&lista, 10);
    Inserir(&lista, 20);
    Inserir(&lista, 30);
    Imprimir(lista);

    No* encontrado = Buscar(lista, 20);
    if (encontrado) {
        printf("Valor %d encontrado na lista.\n", encontrado->valor);
    } else {
        printf("Valor nao encontrado na lista.\n");
    }

    if (Remover(&lista, 20)) {
        printf("Valor 20 removido da lista.\n");
    } else {
        printf("Valor 20 nao encontrado para remocao.\n");
    }
    Imprimir(lista);

    LiberarLista(&lista);
    return 0;
}