#include <stdio.h>

void hanoi(int n, char origem, char destino, char auxiliar) {
    if (n == 1) {
        printf("Mover disco 1 de %c para %c\n", origem, destino);
        return;
    }
    
    hanoi(n - 1, origem, auxiliar, destino);
    
    printf("Mover disco %d de %c para %c\n", n, origem, destino);
    
    hanoi(n - 1, auxiliar, destino, origem);
}

int main() {
    int discos;
    printf("Digite o numero de discos: ");
    scanf("%d", &discos);

    printf("\nSequencia de movimentos:\n");
    hanoi(discos, 'A', 'C', 'B');

    return 0;
}
