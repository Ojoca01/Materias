#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
/*
// Função para exibir os divisores de um número
int divisores(a) {
    if (a <= 0) {
        printf("Entrada inválida: digite um número positivo e não nulo.\n");
        return; // Sai da função sem continuar
    }

    printf("Os divisores de %d são: ", a);

    for (int i = 1; i <= a; i++) { if (a % i == 0) { printf("%d ", i); // Exibe o divisor
                                                   }
                                 }

    printf("\n");
}

void main() {
    setlocale(LC_ALL, "Portuguese"); // Suporte a caracteres especiais
    int numero;

    // Lendo 5 números do usuário e chamando a função para cada um
    for (int i = 0; i < 5; i++) {
        printf("\nDigite um número inteiro positivo: ");
        scanf("%d", &numero);

        divisores(numero); // Chama a função para exibir os divisores
    }

    return 0;
}

float tipos_de_medias(float notas1, float notas2, float notas3){
 char valor;
 printf("digite A para media aritimetica e P para media ponderada :\n");
 scanf(" %c",&valor);

 switch(valor){

 case 'A':{ float media_aritimetica = (notas1+notas2+notas3)/3;
  printf("media aritimetica:%.2f :\n",media_aritimetica);
  return media_aritimetica ;
 }
 case 'P':{ float media_ponderada =  (notas1*5)+(notas2*3)+(notas3*2)/ 10;
  printf("media ponderada:%.2f :\n",media_ponderada);
  return media_ponderada;
 }
 default: printf("\nOpção inválida. Tente novamente.\n");
                return -1;
        }
 }


void main()
{
 float notas1,notas2,notas3;
 setlocale(LC_ALL,"Portuguese");
printf("digite a 1 nota do aluno:\n");
scanf("%f",&notas1);

printf("digite a 2 nota do aluno:\n");
scanf("%f",&notas2);

printf("digite a 3 nota do aluno:\n");
scanf("%f",&notas3);

 tipos_de_medias(notas1,notas2,notas3);

return 0;
}

void tabuada(int a){
printf("\nTabuada do %d",a);
for(int x=1; x<11; x++)
printf("\n%d X %d = %d",x,a,x*a);
}

void main(){
int n1;
for(int y=1; y<11; y++)
tabuada(y);
}
*/
#include <stdio.h>

void soma_matrizes(int matriz1[3][3], int matriz2[3][3]) {
int somamatriz[3][3];
int i, j;

    // Exibição das matrizes de entrada
printf("\nMatriz 1:\n");
for (i = 0; i < 3; i++) {
for (j = 0; j < 3; j++) {
printf("%d\t", matriz1[i][j]);
}
printf("\n");
}
printf("\nMatriz 2:\n");
for (i = 0; i < 3; i++) {
for (j = 0; j < 3; j++) {
printf("%d\t", matriz2[i][j]);
}
printf("\n");
}

// Soma das matrizes
for (i = 0; i < 3; i++) {
for (j = 0; j < 3; j++) {
somamatriz[i][j] = matriz1[i][j] + matriz2[i][j];
}
}
    // Exibição da matriz resultante
printf("\nSoma das Matrizes:\n");
for (i = 0; i < 3; i++) {
for (j = 0; j < 3; j++) {
printf("%d\t", somamatriz[i][j]);
}
printf("\n");
}
}

int main() {
int matriz1[3][3], matriz2[3][3];
int i, j;

    // Entrada de dados para a primeira matriz
printf("Digite os valores da primeira matriz:\n");
for (i = 0; i < 3; i++) {
for (j = 0; j < 3; j++) {
printf("Elemento [%d][%d]: ", i, j);
scanf("%d", &matriz1[i][j]);
}
}

    // Entrada de dados para a segunda matriz
printf("Digite os valores da segunda matriz:\n");
for (i = 0; i < 3; i++) {
for (j = 0; j < 3; j++) {
printf("Elemento [%d][%d]: ", i, j);
scanf("%d", &matriz2[i][j]);
}
}

    // Soma e exibição das matrizes
soma_matrizes(matriz1, matriz2);

return 0;
}
