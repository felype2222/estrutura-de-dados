#ifndef BST_H
#define BST_H

typedef struct NoBST {
    int chave;
    struct NoBST *esq;
    struct NoBST *dir;
} NoBST;

NoBST* inserirBST(NoBST* raiz, int chave);
int buscarBST(NoBST* raiz, int chave);
void liberarBST(NoBST* raiz);

#endif
