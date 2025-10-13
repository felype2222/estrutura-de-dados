#include <stdlib.h>
#include "bst.h"

NoBST* inserirBST(NoBST* raiz, int chave) { // Inserção na árvore binária de busca
    if (raiz == NULL) { // Se a árvore estiver vazia, cria um novo nó
        NoBST* novo = (NoBST*) malloc(sizeof(NoBST));
        novo->chave = chave;
        novo->esq = novo->dir = NULL;
        return novo;
    }
    if (chave < raiz->chave) // Insere recursivamente na subárvore esquerda ou direita
        raiz->esq = inserirBST(raiz->esq, chave);
    else if (chave > raiz->chave)
        raiz->dir = inserirBST(raiz->dir, chave);
    return raiz;
}

int buscarBST(NoBST* raiz, int chave) { // Busca na árvore binária de busca
    if (raiz == NULL) return 0; // Não encontrou
    if (chave == raiz->chave) return 1; // Encontrou
    if (chave < raiz->chave) return buscarBST(raiz->esq, chave); // Busca recursivamente na subárvore esquerda ou direita
    else return buscarBST(raiz->dir, chave);
}

void liberarBST(NoBST* raiz) { // Libera a memória da árvore binária de busca
    if (raiz == NULL) return; 
    liberarBST(raiz->esq);
    liberarBST(raiz->dir);
    free(raiz);
}

