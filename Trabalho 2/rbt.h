#ifndef RBT_H
#define RBT_H

typedef enum { VERMELHO, PRETO } Cor; // Define as cores dos nós

typedef struct NoRBT { // Define a estrutura do nó da árvore rubro-negra
    int chave;
    Cor cor;
    struct NoRBT *esq;
    struct NoRBT *dir;
    struct NoRBT *pai;
} NoRBT;

NoRBT* inserirRBT(NoRBT* raiz, int chave); // Função para inserir um nó na árvore
int buscarRBT(NoRBT* raiz, int chave); // Função para buscar um nó na árvore
void liberarRBT(NoRBT* raiz); // Função para liberar a memória da árvore

#endif

