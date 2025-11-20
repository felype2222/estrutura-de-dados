#ifndef HEAP_H
#define HEAP_H

#define MAX 100 // Tamanho máximo do heap

typedef struct { // Elemento do heap
    int chave;
} Elem;

typedef struct { // Estrutura do heap
    Elem T[MAX];
    int n; 
} Heap;

void inicializar(Heap *H); // Inicializa o heap
int buscar(Heap *H, int chave); // Busca uma chave no heap
void subir(Heap *H, int i); // Move o elemento na posição i para cima
void descer(Heap *H, int i); // Move o elemento na posição i para baixo
void inserir(Heap *H, int chave); // Insere uma nova chave no heap
void construir(Heap *H); // Constrói o heap a partir de um array
void alterarPrioridade(Heap *H, int i, int novaChave); // Altera a prioridade do elemento na posição i
int remover(Heap *H); // Remove e retorna a chave do elemento no topo do heap
void imprimir(Heap *H); // Imprime os elementos do heap

#endif
