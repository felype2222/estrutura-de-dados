#include <stdio.h>

int fibonacci(int n) {
    if (n == 1) return 0;
    if (n == 2) return 1; 
    return fibonacci(n - 1) + fibonacci(n - 2); 
}

int main() {
    int i;
    printf("Digite o valor de i (posição na sequência): ");
    scanf("%d", &i);

    printf("O elemento %d da sequência de Fibonacci é: %d\n", i, fibonacci(i));

    return 0;
}
