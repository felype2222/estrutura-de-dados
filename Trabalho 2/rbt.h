#ifndef RBT_H
#define RBT_H

// Definições de cores
#define VERMELHO 1
#define PRETO 0

typedef struct NoRBT { // Nó da Árvore Rubro-Negra
    int chave;
    int cor; // 1 = vermelho, 0 = preto
    struct NoRBT *pai;
    struct NoRBT *esq;
    struct NoRBT *dir;
} NoRBT;

typedef struct { // Árvore Rubro-Negra
    NoRBT *raiz;
    NoRBT *nil;
} ArvoreRBT;

// Protótipos de funções
void inicializarRBT(ArvoreRBT *T);
void inserirRBT(ArvoreRBT *T, int chave);
int buscarRBT(ArvoreRBT *T, int chave);
void liberarRBT(ArvoreRBT *T, NoRBT *n);

#endif


