/*
ALUNO : JOÃO CARLOS CRUZ SANTOS


*/

//8
#include <stdio.h>
#include <math.h>

void main() {
int n, quad, raiz;

printf("Digite um numero inteiro: ");
scanf("%d", &n);
if (n >= 0) {
raiz = sqrt(n);
printf("Raiz quadrada de %d: %d\n", n, raiz);
}
else {quad = pow(n, 2);
printf("Quadrado de %d: %d\n", n, quad);
}
printf("\nEncerrando programa...\n");

}

//10
#include <stdio.h>

void main(){
int num;
printf("Digite um numero inteiro:");
scanf("%d",&num);
if(num % 2 == 0)
printf("PAR");
else
printf("IMPAR");
printf("\nEncerrando programa...");
}
//11
#include <stdio.h>
#include <math.h>

void main() {
    int n,raiz;

printf("Digite um numero inteiro: ");
scanf("%d", &n);
if (n >= 0) {
 double raiz = sqrt(n);
if (raiz == (int)raiz) {
printf("A raiz quadrada de %d e um numero inteiro.\n", n);}
else {
printf("A raiz quadrada de %d nao e um numero inteiro.\n", n);}}

else {
printf("Nao é possivel calcular a raiz quadrada de um numero negativo.\n");}
printf("\nEncerrando programa...\n");
}

//15
#include <stdio.h>
#include <math.h>

void main() {
int di,de;
printf("Digite o divisor e o dividendo: ");
scanf("%d_%d", &di,&de);
if (de % di==0) {
printf("o quociente desta divisao e um numero inteiro: ");}
else {
printf("o quociente desta divisao nao e inteiro.\n");}

}

//19

#include <stdio.h>
#include <math.h>

void main() {
    int A,B;

printf("Digite o primeiro numero inteiro ");
scanf("%d",&A);
printf("Digite o segundo numero inteiro ");
scanf("%d",&B);

if (A < B) {
printf("A ordem crescente e : %d ,%d .\n ",A ,B);}

else {
printf("A ordem crescente e : %d ,%d.\n ",B ,A);}
}
