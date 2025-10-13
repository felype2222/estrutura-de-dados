#include <stdlib.h>
#include "bst.h"

NoBST* inserirBST(NoBST* raiz, int chave) {
    if (raiz == NULL) {
        NoBST* novo = (NoBST*) malloc(sizeof(NoBST));
        novo->chave = chave;
        novo->esq = novo->dir = NULL;
        return novo;
    }
    if (chave < raiz->chave)
        raiz->esq = inserirBST(raiz->esq, chave);
    else if (chave > raiz->chave)
        raiz->dir = inserirBST(raiz->dir, chave);
    return raiz;
}

int buscarBST(NoBST* raiz, int chave) {
    if (raiz == NULL) return 0;
    if (chave == raiz->chave) return 1;
    if (chave < raiz->chave) return buscarBST(raiz->esq, chave);
    else return buscarBST(raiz->dir, chave);
}

void liberarBST(NoBST* raiz) {
    if (raiz == NULL) return;
    liberarBST(raiz->esq);
    liberarBST(raiz->dir);
    free(raiz);
}

