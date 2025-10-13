#ifndef RBT_H
#define RBT_H

typedef enum { VERMELHO, PRETO } Cor;

typedef struct NoRBT {
    int chave;
    Cor cor;
    struct NoRBT *esq;
    struct NoRBT *dir;
    struct NoRBT *pai;
} NoRBT;

NoRBT* inserirRBT(NoRBT* raiz, int chave);
int buscarRBT(NoRBT* raiz, int chave);
void liberarRBT(NoRBT* raiz);

#endif

