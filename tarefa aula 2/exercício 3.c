#include <stdio.h>
#include <math.h>

struct realType {
    int left;  
    int right;  
};

struct realType criarReal() {
    struct realType num;
    double valor;

    printf("Digite um numero real: ");
    scanf("%lf", &valor);

    num.left = (int)valor;
    num.right = (int)round(fabs((valor - num.left) * 1000)); 

    return num;
}

double converterParaDouble(struct realType num) {
    double parteDecimal = num.right / 1000.0;
    if (num.left < 0) {
        return num.left - parteDecimal;
    } else {
        return num.left + parteDecimal;
    }
}

struct realType add(struct realType a, struct realType b) {
    double resultado = converterParaDouble(a) + converterParaDouble(b);
    struct realType res;
    res.left = (int)resultado;
    res.right = (int)round(fabs((resultado - res.left) * 1000));
    return res;
}

struct realType subtract(struct realType a, struct realType b) {
    double resultado = converterParaDouble(a) - converterParaDouble(b);
    struct realType res;
    res.left = (int)resultado;
    res.right = (int)round(fabs((resultado - res.left) * 1000));
    return res;
}

struct realType multiply(struct realType a, struct realType b) {
    double resultado = converterParaDouble(a) * converterParaDouble(b);
    struct realType res;
    res.left = (int)resultado;
    res.right = (int)round(fabs((resultado - res.left) * 1000));
    return res;
}

void mostrarReal(struct realType num) {
    printf("%d.%03d\n", num.left, num.right);
}

int main() {
    struct realType n1 = criarReal();
    struct realType n2 = criarReal();

    printf("\nPrimeiro numero: ");
    mostrarReal(n1);
    printf("Segundo numero: ");
    mostrarReal(n2);

    struct realType soma = add(n1, n2);
    struct realType sub = subtract(n1, n2);
    struct realType mult = multiply(n1, n2);

    printf("\nSoma: ");
    mostrarReal(soma);
    printf("Subtracao: ");
    mostrarReal(sub);
    printf("Multiplicacao: ");
    mostrarReal(mult);

    return 0;
}
