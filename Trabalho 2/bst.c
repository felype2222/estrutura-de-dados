#include <stdlib.h>
#include "bst.h"

// ---------------- Inicialização ----------------
void inicializarBST(ArvoreBST *arvore) { // Inicializa a árvore
    arvore->raiz = NULL;
}

// ---------------- Inserção ----------------
NoBST* inserirBST(NoBST *raiz, int chave) { // Insere um nó na árvore
    if (raiz == NULL) { // Caso base: árvore vazia
        NoBST *novo = (NoBST *)malloc(sizeof(NoBST));
        novo->chave = chave;
        novo->esq = novo->dir = NULL;
        return novo;
    }
    if (chave < raiz->chave) // Inserção na subárvore esquerda
        raiz->esq = inserirBST(raiz->esq, chave);
    else if (chave > raiz->chave) // Inserção na subárvore direita
        raiz->dir = inserirBST(raiz->dir, chave);
    return raiz;
}

// ---------------- Busca ----------------
int buscarBST(NoBST *raiz, int chave) { // Busca um nó na árvore
    if (raiz == NULL) return 0; // Não encontrado
    if (chave == raiz->chave) return 1; // Encontrado
    if (chave < raiz->chave) return buscarBST(raiz->esq, chave); // Busca na subárvore esquerda
    else return buscarBST(raiz->dir, chave);
}

// ---------------- Liberação ----------------
void liberarBST(NoBST *raiz) { // Libera a memória da árvore
    if (raiz == NULL) return;
    liberarBST(raiz->esq);
    liberarBST(raiz->dir);
    free(raiz);
}


