#include <stdio.h>
#include "heap.h"

int main() { // Programa de teste para o Max Heap
    Heap H;
    inicializar(&H);

    inserir(&H, 40);
    inserir(&H, 10);
    inserir(&H, 60);
    inserir(&H, 30);

    printf("Heap atual: ");
    imprimir(&H);

    printf("Removendo maior elemento: %d\n", remover(&H));
    imprimir(&H);

    printf("Alterando prioridade do índice 1 para 90...\n");
    alterarPrioridade(&H, 1, 90);
    imprimir(&H);

    return 0;
}
