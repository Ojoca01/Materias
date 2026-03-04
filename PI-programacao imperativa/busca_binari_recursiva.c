// BUSCA BINÁRIA
#include <stdio.h>
#include <stdlib.h>



// ADIÇÃO
int* entrada_de_dados(int *tam) {

    printf("Quantos elementos deseja inserir?\n");
    scanf(" %d", tam);
    int *vetor_int = malloc((*tam) * sizeof(int));
    
    if (!vetor_int) {
        printf("\n\nERRO: memoria nao alocada!");
        return NULL;
    }


    printf("\n=== Insira os dados ===\n");
    for(int j = 0; j < *tam; j++) {
        printf("Elemento [%d]: ", j + 1);
        scanf("%d", &vetor_int[j]);
    }

    return vetor_int;
}

int busca_binaria(int *tam){
    int *vetor=entrada_de_dados(&tam);
    printf("Digite o termo que deseja buscar");
    int elem;
    scanf("%d",&elem);
    int inicio=0,fim=*tam-1,meio=0;
    do
    {
        meio = (fim-inicio) /2;
        if (vetor[meio]<elem)
        {
          inicio=meio;
        }
        else if (vetor[meio]<elem)
        {
            fim=meio;
        }
        
    } while (vetor[meio]!=elem);
    printf("Termo encontrado, indice: %d",meio);
}