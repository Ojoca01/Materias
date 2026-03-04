#include <stdio.h>
#include <math.h>

// questão 3

/*

void main() {
    int numeros[8],i;

    printf("Digite 8 numeros inteiros");

    for(i = 0; i < 8; i++) {
        printf("Numero %d: ", i + 1);
        scanf("%d", &numeros[i]);
    }

//impressão final
    printf("\nMultiplos de 6 :\n");
    for(i = 0; i < 8; i++) {
        if (numeros[i] % 6 == 0) {
            printf("%d ", numeros[i]);
        }
    }

}

*/

// questão 9
/*
void main() {
    int A[10], B[10],i;

    printf("\n Digite 10 numeros inteiros para a primeira lista :\n");

    for(i = 0; i < 10; i++) {
        printf("Elemento A[%d]: ", i+1 );
        scanf("%d", &A[i]);
    }

    for(i = 0; i < 10; i++) {
        B[i] = A[i] * A[i];
    }
//impressão final
    printf("\n Os elementos das listas A e B sao respectivamente \n");
    printf("\n\t A \t B \n");
    for(i = 0; i < 10; i++) {
        printf(" %d:\t| %d|\t|%d |\n", i+1, A[i], B[i]);
    }

}

*/

// questão 12

/*

void main() {
    int A[15], B[15], V[30],i;


    printf("Digite 15 numeros inteiros para a lista A:\n");
    for(i = 0; i < 15; i++) {
        printf("Elemento A[%d]: ", i + 1);
        scanf("%d", &A[i]);
    }

    printf("\nDigite 15 numeros inteiros para a lista B:\n");
    for(i = 0; i < 15; i++) {
        printf("Elemento B[%d]: ", i + 1);
        scanf("%d", &B[i]);
    }

    for(i = 0; i < 15; i++) {
        V[2*i] = A[i];
        V[2*i + 1] = B[i];
    }
//impressão final
    printf("\nLista V intercalada:\n");
    for(i = 0; i < 30; i++) {
        printf("%d ", V[i]);
    }

}

*/
// questão 13


/*

void main() {
    int lista[100],numero, count = 0, i = 0;

    printf("Digite numeros inteiros ate 100 (digite 0 para parar):\n");
    while (1) {
        printf("%d  Numero : ", i + 1);
        scanf("%d", &numero);

        if (numero == 0) {
            break;
        }

        lista[i] = numero;
        i++;

        if (i == 100) {
            printf("Máximo de 100 números atingido!\n");
            break;
        }
    }
//prevençoes e ultimo numero


    if (i > 0) {
        int ultimoNumero = lista[i - 1];  // Último número digitado

        // Contando quantas vezes o último número aparece no vetor
        for (int j = 0; j < i; j++) {
            if (lista[j] == ultimoNumero) {
                count++;
            }
        }

//impressão final
        printf("\nO numero %d apareceu %d vezes.\n", ultimoNumero, count);
               }

    else {
        printf("Nenhum numero foi digitado.\n");
    }

}


*/




















