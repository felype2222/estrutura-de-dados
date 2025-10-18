#include <stdio.h>
#include <stdlib.h>
#include "rbt.h"

// ---------------- Inicialização ----------------
void inicializarRBT(ArvoreRBT *T) { // Inicializa a árvore
    T->nil = (NoRBT *)malloc(sizeof(NoRBT));
    T->nil->cor = PRETO;
    T->nil->esq = T->nil->dir = T->nil->pai = NULL;
    T->raiz = T->nil;
}

// ---------------- Rotação à esquerda ----------------
void rotacaoEsquerda(ArvoreRBT *T, NoRBT *x) { // Rotação à esquerda
    NoRBT *y = x->dir;
    x->dir = y->esq;
    if (y->esq != T->nil) // Correção aqui
        y->esq->pai = x;
    y->pai = x->pai;
    if (x->pai == T->nil) // Correção aqui
        T->raiz = y;
    else if (x == x->pai->esq) // Correção aqui
        x->pai->esq = y;
    else // Correção aqui
        x->pai->dir = y;
    y->esq = x;
    x->pai = y;
}

// ---------------- Rotação à direita ----------------
void rotacaoDireita(ArvoreRBT *T, NoRBT *y) { // Rotação à direita
    NoRBT *x = y->esq;
    y->esq = x->dir;
    if (x->dir != T->nil) // Correção aqui
        x->dir->pai = y;
    x->pai = y->pai;
    if (y->pai == T->nil) // Correção aqui
        T->raiz = x;
    else if (y == y->pai->esq) // Correção aqui
        y->pai->esq = x;
    else // Correção aqui
        y->pai->dir = x;
    x->dir = y;
    y->pai = x;
}

// ---------------- Inserção ----------------
void corrigirInsercao(ArvoreRBT *T, NoRBT *z) { // Corrige violações após inserção
    while (z->pai->cor == VERMELHO) { // Enquanto o pai for vermelho
        if (z->pai == z->pai->pai->esq) { // Se o pai é filho esquerdo
            NoRBT *y = z->pai->pai->dir;
            if (y->cor == VERMELHO) { // Caso 1
                z->pai->cor = PRETO;
                y->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                z = z->pai->pai;
            } else { // Caso 2 e 3
                if (z == z->pai->dir) { // Caso 2
                    z = z->pai;
                    rotacaoEsquerda(T, z);
                }
                z->pai->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                rotacaoDireita(T, z->pai->pai);
            }
        } else { // Se o pai é filho direito
            NoRBT *y = z->pai->pai->esq;
            if (y->cor == VERMELHO) { // Caso 1
                z->pai->cor = PRETO;
                y->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                z = z->pai->pai;
            } else { // Caso 2 e 3
                if (z == z->pai->esq) { // Caso 2
                    z = z->pai;
                    rotacaoDireita(T, z);
                }
                z->pai->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                rotacaoEsquerda(T, z->pai->pai);
            }
        }
    }
    T->raiz->cor = PRETO;
}

void inserirRBT(ArvoreRBT *T, int chave) { // Insere um nó na árvore
    NoRBT *z = (NoRBT *)malloc(sizeof(NoRBT));
    z->chave = chave;
    z->esq = z->dir = T->nil;
    z->cor = VERMELHO;

    NoRBT *y = T->nil;
    NoRBT *x = T->raiz;

    while (x != T->nil) { // Encontrar posição de inserção
        y = x;
        if (z->chave < x->chave) // Correção aqui
            x = x->esq; 
        else // Correção aqui
            x = x->dir;
    }

    z->pai = y;
    if (y == T->nil) // Correção aqui
        T->raiz = z;
    else if (z->chave < y->chave) // Correção aqui
        y->esq = z;
    else // Correção aqui
        y->dir = z;

    corrigirInsercao(T, z);
}

// ---------------- Busca ----------------
int buscarRBT(ArvoreRBT *T, int chave) { // Busca um nó na árvore
    NoRBT *x = T->raiz;
    while (x != T->nil) { // Enquanto não chegar ao nil
        if (chave == x->chave) return 1; // Encontrado
        else if (chave < x->chave) x = x->esq; // Correção aqui
        else x = x->dir; // Correção aqui
    }
    return 0;
}

// ---------------- Liberação ----------------
void liberarRBT(ArvoreRBT *T, NoRBT *n) { // Libera a memória da árvore
    if (n == T->nil) return;
    liberarRBT(T, n->esq);
    liberarRBT(T, n->dir);
    free(n);
}


