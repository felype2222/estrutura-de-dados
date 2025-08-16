#include <stdio.h>

int fibonacci(int n) {
    if (n == 1)
        return 0;
    if (n == 2)
        return 1;
    
    int f1 = 0, f2 = 1, fn;

    for (int i = 3; i <= n; i++) {
        fn = f1 + f2;
        f1 = f2;
        f2 = fn;
    }
    return fn;
}

int main() {
    int n;
    printf("Digite a posição do termo de Fibonacci que deseja encontrar: ");
    scanf("%d", &n);
    
    printf("O termo de Fibonacci na posição %d é: %d\n", n, fibonacci(n));

    return 0;
}