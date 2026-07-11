#include<stdio.h>
#include<stdlib.h>
#include<locale.h>


/*3) Peça ao usuário um número N e M. Gere dinamicamente uma matriz
N×M. Usando notação convencional de matriz leia elementos para essa
matriz e a exiba na tela.
*/

int main() {
    int N, M, i, j;
    int **matriz;

    // Entrada do tamanho da matriz
    printf("Digite o numero de linhas (N) e colunas (M): ");
    scanf("%d %d", &N, &M);

    // Alocação dinâmica de memória para as linhas
    matriz = (int **)malloc(N * sizeof(int *));
    if (matriz == NULL) {
        printf("Erro na alocacao de memoria!\n");
        return 1;
    }

    // Alocação dinâmica para cada linha (colunas)
    for (i = 0; i < N; i++) {
        *(matriz + i) = (int *)malloc(M * sizeof(int));
        if (*(matriz + i) == NULL) {
            printf("Erro na alocacao de memoria!\n");
            return 1;
        }
    }

    // Leitura dos elementos da matriz usando aritmética de ponteiros
    printf("Digite os elementos da matriz:\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            scanf("%d", (*(matriz + i) + j));
        }
    }

    // Exibição da matriz usando aritmética de ponteiros
    printf("Matriz:\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            printf("%d ", *(*(matriz + i) + j));
        }
        printf("\n");
    }

    // Liberação da memória alocada
    for (i = 0; i < N; i++) {
        free(*(matriz + i));
    }
    free(matriz);

    return 0;
}

/*
int main() {
    int N, M, i, j;
    int **matriz;

    // Entrada do tamanho da matriz
    printf("Digite o numero de linhas (N) e colunas (M): ");
    scanf("%d %d", &N, &M);

    // Alocação dinâmica de memória para as linhas
    matriz = (int **)malloc(N * sizeof(int *));
    matriz[i] = (int *)malloc(M * sizeof(int));

    if (matriz == NULL) {
        printf("Erro na alocacao de memoria!\n");
        return 1;
    }

    // Alocação dinâmica para cada linha (colunas)
    for (i = 0; i < N; i++) {
        if (matriz[i] == NULL) {
            printf("Erro na alocacao de memoria!\n");
            return 1;
        }
    }

    // Leitura dos elementos da matriz
    printf("Digite os elementos da matriz:\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            printf("elemento(%d,%d): \n\n ",i,j);
            scanf("%d", &matriz[i][j]);
        }
    }

    // Exibição da matriz
    printf("Matriz(%d,%d):\n",N,M);
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {

            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }

    // Liberação da memória alocada
    for (i = 0; i < N; i++) {
        free(matriz[i]);
    }
    free(matriz);

    return 0;
}


/*
Peça ao usuário um número N e M. Gere dinamicamente uma matriz
N×M. Usando aritmética de ponteiros, leia elementos para essa matriz e
a exiba na tela.
int main() {
    int N, *vet, i, soma = 0, count_mult6 = 0;
    float media;

    // Entrada do tamanho do vetor
    printf("Quantos numeros deseja inserir? ");
    scanf("%d", &N);

    // Alocação dinâmica do vetor
    vet = (int*)malloc(N * sizeof(int));
    if (vet == NULL) {
        printf("Erro de alocacao de memoria!\n");
        return 1;
    }

    // Leitura dos números
    printf("Digite %d numeros:\n", N);
    for (i = 0; i < N; i++) {
        scanf("%d", &vet[i]);
        soma += vet[i];
    }

    // Cálculo da média
    media = (float)soma / N;
    printf("Media dos numeros: %.2f\n", media);

    // Exibir múltiplos de 6
    printf("Multiplos de 6 digitados: ");
    for (i = 0; i < N; i++) {
        if (vet[i] % 6 == 0) {
            printf("%d ", vet[i]);
            count_mult6++;
        }
    }
    if (count_mult6 == 0) {
        printf("Nenhum");
    }
    printf("\n");

    // Liberar memória
    free(vet);
    return 0;
}

//memory alocation -> malloc; retorna um ponteiro para uma região de memória
//funcionameno: vet=malloc((sizefof(int))

//realloc

//calloc



/*
int main(){
    setlocale(LC_ALL,"Portuguese");
int *x;

// x=malloc(sizeof(int));
   x=calloc(1,sizeof(int));

 if(x!=0){printf("alocação bem sucedida\n\n");
 printf("%d\n",*x);
*x=50;
 printf("%d",*x);}



 else{printf("alocação mal sucedida");}

return 0;
};

void main(){
 int *A,*B;
 int dobro,triplo,n1,n2;

A=&n1;
B=&n2;
printf("de entrada em dois inteiros:\n");

printf("primeiro:\n");
scanf("%d",A);
printf("segundo:\n");
scanf("%d",B);
dobro= (*A)*2;
triplo=(*B)*3;
printf("dobro:%d\ntriplo:%d\n",dobro,triplo);

}*/

//alocação de vetores com malloc calloc
/*
void main (){
    setlocale(LC_ALL,"Portuguese");
 int tam,*vet;

printf("digite um tamanho para o vetor:\n\n");
scanf("%d",&tam);
vet=(int*) malloc(tam*sizeof(int));

if(vet!=NULL){
        printf(" alocação de vetor bem sucedida\n\n");
}

else{
        printf(" alocação de vetor mal sucedida");
}
printf("digite seu vetor\n");
for(int i=0;i<tam;i++){
    printf("elemento: %d\n",i+1);
    scanf("%d",&vet[i]);
vet=realloc(vet,tam);

free(vet);

}
printf("expor vetor %d\t",vet);
};
*/






