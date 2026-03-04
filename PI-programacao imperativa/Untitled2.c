#include <stdio.h>

int main() {
    int num, formado;

    // Ler o número de 4 casas
    printf("Digite um número inteiro de 4 casas: ");
    scanf("%d", &num);

    // Verificar se o número está no intervalo de 1000 a 9999
    if (num < 1000 || num > 9999) {
        printf("Número inválido! Digite um número de 4 casas.\n");
        return 0;
    }

    // Extrair o número formado pelas unidades de milhar e centenas
    // Unidade de milhar: num / 1000
    // Centena: (num / 100) % 10
    formado = (num / 1000) * 10 + (num / 100) % 10;

    // Verificar se o número formado é múltiplo de 4
    if (formado % 4 == 0) {
        printf("O número formado pelas casas das unidades de milhar e centenas (%d) é múltiplo de 4.\n", formado);
    } else {
        printf("O número formado pelas casas das unidades de milhar e centenas (%d) não é múltiplo de 4.\n", formado);
    }

    return 0;
}
