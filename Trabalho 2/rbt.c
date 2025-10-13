#include <stdlib.h>
#include "rbt.h"

// Funções auxiliares
static NoRBT* novoNo(int chave) { // Cria um novo nó
    NoRBT* no = (NoRBT*) malloc(sizeof(NoRBT)); 
    no->chave = chave; 
    no->cor = VERMELHO; 
    no->esq = no->dir = no->pai = NULL;
    return no;
}

static void rotacaoEsquerda(NoRBT** raiz, NoRBT* x) { // Rotação à esquerda
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

static void rotacaoDireita(NoRBT** raiz, NoRBT* y) { // Rotação à direita
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

static void corrigirInsercao(NoRBT** raiz, NoRBT* z) { // Corrige violações das propriedades da RBT após inserção
    while (z->pai && z->pai->cor == VERMELHO) { // Enquanto o pai for vermelho
        if (z->pai == z->pai->pai->esq) { // Se o pai for filho esquerdo
            NoRBT* tio = z->pai->pai->dir;
            if (tio && tio->cor == VERMELHO) { // Caso 1: tio vermelho
                z->pai->cor = PRETO;
                tio->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                z = z->pai->pai;
            } else { // Caso 2 e 3: tio preto
                if (z == z->pai->dir) { // Caso 2: z é filho direito
                    z = z->pai;
                    rotacaoEsquerda(raiz, z);
                }
                z->pai->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                rotacaoDireita(raiz, z->pai->pai);
            }
        } else { // Se o pai for filho direito
            NoRBT* tio = z->pai->pai->esq;
            if (tio && tio->cor == VERMELHO) {
                z->pai->cor = PRETO;
                tio->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                z = z->pai->pai;
            } else { // Caso 2 e 3: tio preto
                if (z == z->pai->esq) { // Caso 2: z é filho esquerdo
                    z = z->pai;
                    rotacaoDireita(raiz, z);
                }
                z->pai->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                rotacaoEsquerda(raiz, z->pai->pai);
            }
        }
    }
    (*raiz)->cor = PRETO; // A raiz deve ser sempre preta
}

NoRBT* inserirRBT(NoRBT* raiz, int chave) { // Inserção na árvore rubro-negra
    NoRBT* novo = novoNo(chave);
    NoRBT* y = NULL;
    NoRBT* x = raiz;

    while (x != NULL) { // Encontra a posição correta para o novo nó
        y = x;
        if (chave < x->chave) // Evita chaves duplicadas
            x = x->esq;
        else if (chave > x->chave) // Evita chaves duplicadas
            x = x->dir;
        else // Chave já existe, não insere
            return raiz; 
    }

    novo->pai = y;
    if (y == NULL) // A árvore estava vazia
        raiz = novo;
    else if (chave < y->chave) // Insere como filho esquerdo ou direita
        y->esq = novo;
    else // Insere como filho esquerdo ou direita
        y->dir = novo;

    corrigirInsercao(&raiz, novo);
    return raiz; 
}

int buscarRBT(NoRBT* raiz, int chave) { // Busca na árvore rubro-negra
    if (raiz == NULL) return 0; // Não encontrou
    if (chave == raiz->chave) return 1; // Encontrou
    if (chave < raiz->chave) return buscarRBT(raiz->esq, chave); // Busca recursivamente na subárvore esquerda ou direita
    else return buscarRBT(raiz->dir, chave); 
}

void liberarRBT(NoRBT* raiz) { // Libera a memória da árvore rubro-negra
    if (!raiz) return;
    liberarRBT(raiz->esq);
    liberarRBT(raiz->dir);
    free(raiz);
}

