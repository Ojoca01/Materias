// BUSCA BINÁRIA
#include <stdio.h>
#include <stdlib.h>



// ADIÇÃO
int* entrada_de_dados(int * tam ) {
    printf("Quantos elementos deseja inserir?\n");
    scanf(" %d",tam);

    getchar();
    int *vetor = malloc( (*tam) * sizeof(int));
    if (!vetor) {
        printf("\n\nERRO: memoria nao alocada!");
        return NULL;
    }
    printf("\n=== Insira os dados ===\n");
    for(int j = 0; j < *tam; j++) {
        printf("Elemento [%d]: ", j + 1);
        scanf("%d", &vetor[j]);
    }

    return vetor;
}

int main(){

    int elem,tam=0;
    printf("\n\n");
    int * vetor = entrada_de_dados(&tam);
    printf("Digite o termo que deseja buscar: ");
    scanf("%d",&elem);
    int inicio=0;
    int fim = tam -1;
    int meio = 0;

    fflush(stdin);
    do {
        meio = (fim-inicio) /2;
    
        if ( vetor[meio]<elem)
        {
          inicio=meio;
        }
        else if (vetor[meio]>elem)
        {
            fim=meio;
        }
        
    } while (vetor[meio] != elem);
    
    printf("Termo encontrado, indice: %d",meio+1);
   
    free(vetor);

    return 0;

}