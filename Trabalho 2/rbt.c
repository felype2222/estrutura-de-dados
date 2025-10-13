#include <stdlib.h>
#include "rbt.h"

// Funções auxiliares
static NoRBT* novoNo(int chave) {
    NoRBT* no = (NoRBT*) malloc(sizeof(NoRBT));
    no->chave = chave;
    no->cor = VERMELHO;
    no->esq = no->dir = no->pai = NULL;
    return no;
}

static void rotacaoEsquerda(NoRBT** raiz, NoRBT* x) {
    NoRBT* y = x->dir;
    x->dir = y->esq;
    if (y->esq) y->esq->pai = x;
    y->pai = x->pai;
    if (!x->pai) *raiz = y;
    else if (x == x->pai->esq) x->pai->esq = y;
    else x->pai->dir = y;
    y->esq = x;
    x->pai = y;
}

static void rotacaoDireita(NoRBT** raiz, NoRBT* y) {
    NoRBT* x = y->esq;
    y->esq = x->dir;
    if (x->dir) x->dir->pai = y;
    x->pai = y->pai;
    if (!y->pai) *raiz = x;
    else if (y == y->pai->esq) y->pai->esq = x;
    else y->pai->dir = x;
    x->dir = y;
    y->pai = x;
}

static void corrigirInsercao(NoRBT** raiz, NoRBT* z) {
    while (z->pai && z->pai->cor == VERMELHO) {
        if (z->pai == z->pai->pai->esq) {
            NoRBT* tio = z->pai->pai->dir;
            if (tio && tio->cor == VERMELHO) {
                z->pai->cor = PRETO;
                tio->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                z = z->pai->pai;
            } else {
                if (z == z->pai->dir) {
                    z = z->pai;
                    rotacaoEsquerda(raiz, z);
                }
                z->pai->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                rotacaoDireita(raiz, z->pai->pai);
            }
        } else {
            NoRBT* tio = z->pai->pai->esq;
            if (tio && tio->cor == VERMELHO) {
                z->pai->cor = PRETO;
                tio->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                z = z->pai->pai;
            } else {
                if (z == z->pai->esq) {
                    z = z->pai;
                    rotacaoDireita(raiz, z);
                }
                z->pai->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                rotacaoEsquerda(raiz, z->pai->pai);
            }
        }
    }
    (*raiz)->cor = PRETO;
}

NoRBT* inserirRBT(NoRBT* raiz, int chave) {
    NoRBT* novo = novoNo(chave);
    NoRBT* y = NULL;
    NoRBT* x = raiz;

    while (x != NULL) {
        y = x;
        if (chave < x->chave)
            x = x->esq;
        else if (chave > x->chave)
            x = x->dir;
        else
            return raiz; // chaves iguais
    }

    novo->pai = y;
    if (y == NULL)
        raiz = novo;
    else if (chave < y->chave)
        y->esq = novo;
    else
        y->dir = novo;

    corrigirInsercao(&raiz, novo);
    return raiz;
}

int buscarRBT(NoRBT* raiz, int chave) {
    if (raiz == NULL) return 0;
    if (chave == raiz->chave) return 1;
    if (chave < raiz->chave) return buscarRBT(raiz->esq, chave);
    else return buscarRBT(raiz->dir, chave);
}

void liberarRBT(NoRBT* raiz) {
    if (!raiz) return;
    liberarRBT(raiz->esq);
    liberarRBT(raiz->dir);
    free(raiz);
}

