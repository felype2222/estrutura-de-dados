#ifndef BST_H
#define BST_H

typedef struct NoBST { // Define a estrutura do nó da árvore binária de busca
    int chave;
    struct NoBST *esq;
    struct NoBST *dir;
} NoBST;

NoBST* inserirBST(NoBST* raiz, int chave); // Função para inserir um nó na árvore
int buscarBST(NoBST* raiz, int chave); // Função para buscar um nó na árvore
void liberarBST(NoBST* raiz); // Função para liberar a memória da árvore

#endif
