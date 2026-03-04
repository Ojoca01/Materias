#include <stdio.h>
/*questao 10
int main() {

    float taxaNatalidadeA = 0.03,taxaNatalidadeB = 0.02;
    int anos = 0,populacaoB = 7000000,populacaoA = 5000000;

    while (populacaoA <= populacaoB) {
        populacaoA += populacaoA * taxaNatalidadeA;
        populacaoB += populacaoB * taxaNatalidadeB;
        anos++;
    }


    printf("A populacao do pais A ultrapassara a populacao do pais B em %d anos.\n", anos);
    printf("Populacao de A: %d, Populacao de B: %d\n", populacaoA, populacaoB);

    ;
}
*/

/*questao 19
#include <stdio.h>

void main() {
    int num, posicao = 1
    ;
    printf("Digite a sequencia de numeros (terminada por 0 e separados por espaçosou virgulas):\n");

    do {
        scanf("%d", &num);
        if (num != 0 && num % posicao == 0) {
            printf("%d ", num);
        }

        posicao++;
    } while (num != 0);


}*/

/*questao  27
#include <stdio.h>

int main() {
    int num, maior, menor;
    int soma = 0, contador = 0;
 float media;
    printf("Digite a sequência de números (terminada por 0):\n");

    maior = -1000000;
    menor = 1000000;

    while (1) {
        scanf("%d", &num);

        if (num == 0) {
            break;
        }

        soma += num;
        contador++;

        if (num > maior) {
            maior = num;
        }

        if (num < menor) {
            menor = num;
        }
    }

    if (contador > 0) {
        float media = (float)soma / contador;
        printf("Maior: %d\n", maior);
        printf("Menor: %d\n", menor);
        printf("Média: %.2f\n", media);
    } else {
        printf("Nenhum número foi inserido.\n");
    }

    return 0;
}*/

/*questao 32

#include <stdio.h>

int ehPrimo(int num) {
    if (num <= 1) {
        return 0; // Não é primo
    }
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return 0; // Não é primo
        }
    }
    return 1; // É primo
}

void main() {
    int num, contadorPrimos = 0;

    printf("Digite os números (número menor ou igual a 0 para terminar):\n");

    while (1) {
        scanf("%d", &num); // Lê o número

        if (num <= 0) { // Encerra se o número for menor ou igual a 0
            break;
        }

        if (ehPrimo(num)) {
            contadorPrimos++; // Conta como primo se o número for primo
        }
    }

    printf("Quantidade de números primos: %d\n", contadorPrimos);
}*/


/*questao 51

#include <stdio.h>
#include <math.h>

void calcularHipotenusa() {
    float cateto1, cateto2, hipotenusa;

    printf("Digite o valor do primeiro cateto: ");
    scanf("%f", &cateto1);
    printf("Digite o valor do segundo cateto: ");
    scanf("%f", &cateto2);

    hipotenusa = sqrt(cateto1 * cateto1 + cateto2 * cateto2);

    printf("A hipotenusa e: %.2f\n", hipotenusa);
}

void calcularMedia() {
    float nota1, nota2, nota3, media;

    printf("Digite a primeira nota: ");
    scanf("%f", &nota1);
    printf("Digite a segunda nota: ");
    scanf("%f", &nota2);
    printf("Digite a terceira nota: ");
    scanf("%f", &nota3);

    media = (nota1 + nota2 + nota3) / 3;

    printf("A media das notas e: %.2f\n", media);
}

void imprimirMenor() {
    int num1, num2, num3;

    printf("Digite o primeiro numero: ");
    scanf("%d", &num1);
    printf("Digite o segundo numero: ");
    scanf("%d", &num2);
    printf("Digite o terceiro numero: ");
    scanf("%d", &num3);

    if (num1 <= num2 && num1 <= num3) {
        printf("O menor numero e: %d\n", num1);}

    else if (num2 <= num1 && num2 <= num3) {
        printf("O menor numero e: %d\n", num2);}

    else {
        printf("O menor numero e: %d\n", num3);}
}


void exibirMenu() {
    printf("\nOPCOES\n");
    printf("1 - Calcula a HIPOTENUSA\n");
    printf("2 - Calcula a MEDIA de 3 numeros\n");
    printf("3 - Imprime o MENOR entre 3 numeros\n");
    printf("4 - Termina o algoritmo\n");
    printf("Escolha uma opcao: \n");
}

void main() {
    int opcao;

    do {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                calcularHipotenusa();
                break;
            case 2:
                calcularMedia();
                break;
            case 3:
                imprimirMenor();
                break;
            case 4:
                printf("obrigado pelo uso, encerrado o programa.....\n");
                break;
            default:
                printf("Opção invalida. Tente novamente.\n");
        }
    } while (opcao != 4);
}/*



