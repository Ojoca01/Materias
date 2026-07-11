
#include<stdio.h>
#include<string.h>
#include <locale.h>
#include <stdlib.h>
/*1) Faça uma função recursiva que calcule o somatório dos

números de 1 até um inteiro positivo N passado como parâmetro.
Faça um programa que exemplifique o uso da função.

• 2) Faça uma função recursiva que calcule o somatório dos
números de A até B onde A < B e ambos os números são
fornecidos como parâmetro para a função. Considere que A e B
podem ser tanto positivos como negativos.*/


// Função recursiva para somar de 1 até N
int s_1aten(int i, int n) {
    if (i > n) {
        return 0; // Condição de parada
    }
    return i + s_1aten(i + 1, n); // Chamada recursiva
}

// Função recursiva para somar de A até B
int sAmenorqB(int A, int B) {
    if(A>B) return 0;
    return A + sAmenorqB(A + 1, B); // Chamada recursiva
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    int aux,i, n, A, B;

    printf("Digite 1 para soma de 1 até N ou 2 para soma de A até B onde A < B: ");
    scanf("%d", &aux);

    switch (aux) {
        case 1: {
            printf("Escolha um número inteiro N para somar até ele: ");
            scanf("%d", &n);
            printf("O resultado é: %d\n", s_1aten(i, n));
            break;
        }
        case 2: {
            printf("Digite dois inteiros A e B, tal que A < B:\n");
            printf("A:\n");
            scanf("%d", &A);
            printf("B:\n");
            scanf("%d", &B);
            if (A > B) {
                printf("Entrada inválida. A deve ser menor que B.\n");return 0;
            } else {
                printf("O resultado é: %d\n", sAmenorqB(A, B));
            }
            break;
        }
        default:
            printf("Opção inválida.\n");
            break;
    }

    return 0;
}
