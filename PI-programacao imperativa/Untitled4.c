#include <stdio.h>

int main() {
    int a, b, c;

    // Ler os três lados
    printf("Digite o lado 1: ");
    scanf("%d", &a);

    printf("Digite o lado 2: ");
    scanf("%d", &b);

    printf("Digite o lado 3: ");
    scanf("%d", &c);

    // Verificar se é um triângulo válido
    if (a + b > c && a + c > b && b + c > a) {
        // Classificação dos triângulos
        if (a == b && b == c) {
            printf("Triângulo Equilátero\n");
        } else if (a == b || b == c || a == c) {
            printf("Triângulo Isósceles\n");
        } else {
            printf("Triângulo Escaleno\n");
        }
    } else {
        printf("Não é um triângulo válido.\n");
    }

    return 0;
}
