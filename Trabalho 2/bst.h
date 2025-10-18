#ifndef BST_H
#define BST_H

typedef struct NoBST { // Nó da Árvore Binária de Busca
    int chave;
    struct NoBST *esq;
    struct NoBST *dir;
} NoBST;

typedef struct { // Árvore Binária de Busca
    NoBST *raiz;
} ArvoreBST;

// Protótipos de funções
void inicializarBST(ArvoreBST *arvore); 
NoBST* inserirBST(NoBST *raiz, int chave);
int buscarBST(NoBST *raiz, int chave);
void liberarBST(NoBST *raiz);

#endif
