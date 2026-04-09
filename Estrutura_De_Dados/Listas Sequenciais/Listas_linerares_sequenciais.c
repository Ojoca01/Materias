#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// IMPRESSAO DOS DADOS
void imprimir_vetor(int* vetor_int, int tam) {
    printf("\n\n=== Impressao de vetores ====\n");
    for(int i = 0; i < tam; i++) {
        printf("elemento %d: %d\n", i+1, vetor_int[i]);
    }
}


// CRIAÇÃO DE UMA LISTA VAZIA (retorna ponteiro e define tam por referência)
int* Listas_vazias(int *tam) {
    printf("Quantos elementos deseja inserir?\n");
    scanf(" %d", tam);


    int *vetor_int = malloc((*tam) * sizeof(int));
    if (!vetor_int) {
        printf("\n\nERRO: memoria nao alocada!");
        return NULL;
    }

    return vetor_int;
}


// ADIÇÃO/INSERÇÃO DESORDENADA (primeira criação do vetor)
int* adicao_em_lista_desordenada(int *tam) {
    int *vetor_int = Listas_vazias(tam);

    printf("\n=== Insira os dados ===\n");
    for(int j = 0; j < *tam; j++) {
        printf("Elemento [%d]: ", j + 1);
        scanf("%d", &vetor_int[j]);
    }

    return vetor_int;
}

// REALOCAÇÃO DE TAMANHO DO VETOR + inserção de novo dado
int* realocar_vetor(int *vetor_int, int *tam) {
    int novo_tam;
    printf("\n tamanho atual: %d\n",*tam);
    printf(" Digite um novo tamanho(maior que o anterior) : ");
    scanf(" %d",&novo_tam);

    vetor_int = realloc(vetor_int, novo_tam * sizeof(int));

    if (!vetor_int) {
        printf("Erro ao realocar memoria!\n");
        return vetor_int;
    }

      printf("\n=== Insira os nodos dados ===\n");
      printf(" A partir do indice %d \n",*tam);
    
    for(int j = *tam; j < novo_tam; j++) {
        printf("Elemento [%d]: ", j + 1);
        scanf("%d", &vetor_int[j]);
        
    }
    *tam = novo_tam;
    imprimir_vetor(vetor_int,*tam);
    return vetor_int;
}


// BUSCA SEQUENCIAL LINEAR
int busca_sequencial(int* vetor_int, int tam) {
    int termo_pesquisado;
    int indice = -1;

    printf("\n===PESQUISA SEQUENCIAL===\n");
    printf("Digite o valor a ser buscado: ");
    scanf(" %d", &termo_pesquisado);

    for (int k = 0; k < tam; k++) {
        if (termo_pesquisado == vetor_int[k]) {
            indice = k;
            printf("Termo encontrado no indice: %d\n", indice);
            break;
        }
    }

    if(indice == -1) {
        printf("Termo nao encontrado!\n");
    }

    return indice;
}


// ORDENAÇÃO DECRESCENTE
int* ordenação_de_inteiros_DEcrecente(int* vetor_int, int tam) {
    int aux;
    for(int x=0; x<tam-1; x++){
        for(int y=x+1; y<tam; y++){
            if(vetor_int[x] < vetor_int[y]){
                aux = vetor_int[x];
                vetor_int[x] = vetor_int[y];
                vetor_int[y] = aux;
            }
        }
    }
    imprimir_vetor(vetor_int, tam);
    return vetor_int;
}


// ORDENAÇÃO CRESCENTE
int* ordenação_de_inteiros_crecente(int* vetor_int, int tam) {
    int aux;
    for(int x=0; x<tam-1; x++){
        for(int y=x+1; y<tam; y++){
            if(vetor_int[x] > vetor_int[y]){
                aux = vetor_int[x];
                vetor_int[x] = vetor_int[y];
                vetor_int[y] = aux;
            }
        }
    }
    imprimir_vetor(vetor_int, tam);
    return vetor_int;
}


// INSERÇÃO ORDENADA
int* adicao_em_lista_ordenada(int *tam) {
    int* vetor_int = adicao_em_lista_desordenada(tam);
    ordenação_de_inteiros_crecente(vetor_int, *tam);
    return vetor_int;
}


// REMOÇÃO DESORDENADA
void remocao_em_lista(int* vetor_int, int *tam) {
    int indice;
    printf("Indice para remocao: ");
    scanf(" %d", &indice);

    if (indice < 0 || indice >= *tam) {
        printf("Indice invalido!\n");
        return;
    }

    for (int i = indice; i < *tam - 1; i++)
        vetor_int[i] = vetor_int[i + 1];

    (*tam)--;
    vetor_int = realloc(vetor_int, (*tam) * sizeof(int));

}


// REMOÇÃO ORDENADA
int* remocao_em_lista_ordenada(int* vetor_int, int *tam) {
    remocao_em_lista(vetor_int, tam);
    ordenação_de_inteiros_crecente(vetor_int, *tam);
    return vetor_int;
}


// SUBSTITUIÇÃO DE ELEMENTO
int* substituir_elemento(int* vetor_int, int tam) {
    int indice, elem_aux;

    printf("Digite o indice: ");
    scanf(" %d", &indice);

    if (indice < 0 || indice >= tam) {
        printf("Indice invalido!\n");
        return vetor_int;
    }

    printf("Digite o novo dado: ");
    scanf("%d", &elem_aux);
    vetor_int[indice] = elem_aux;
    return vetor_int;
}

// Busca binária para vetor ordenado
int busca_binaria(int* vetor_int, int tam) {
    int termo_pesquisado;
    int inicio = 0, fim = tam - 1;
    int indice = -1;

 
if(vetor_int == NULL) {
    printf("\nCrie a lista primeiro!\n");
    return -1; 
}


    printf("\n=== BUSCA BINARIA ===\n");
    printf("Digite o valor a ser buscado: ");
    scanf("%d", &termo_pesquisado);

    while (inicio <= fim) {

        int meio = inicio + (fim - inicio) / 2;

        if (vetor_int[meio] == termo_pesquisado) {
            indice = meio;
            break;
        } else if (vetor_int[meio] < termo_pesquisado) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    if (indice != -1)
        printf("Termo encontrado no indice: %d\n", indice);
    else
        printf("Termo nao encontrado!\n");

    return indice;
}
// ===================== MENU PRINCIPAL =====================

int main() {
    char ent_1;
    int ent_2;
    int tam = 0;
    int *vetor_int = NULL;

    do {
        printf("\n========= MENU PRINCIPAL =========\n");
        printf("LISTAS ORDENADAS -> O\nLISTAS DESORDENADAS -> D\nSair -> S\nOpcao ");
        scanf(" %c", &ent_1);
        if(ent_1 == 'O' || ent_1 == 'o') {
            printf("\n\n========= MENU ORDENADO =========\n");
            printf("CRIAR LISTA -> 0\nBUSCA BINARIA -> 1\nREMOVER ITEM -> 2\nSUBSTITUIR ITEM -> 3\n");
            printf("ORDENAR DESC -> 4\nORDENAR CRESC -> 5\nVOLTAR -> 7 \nOpcao: ");
            scanf("%d", &ent_2);

            switch(ent_2) {
                case 0: vetor_int = adicao_em_lista_ordenada(&tam); break;
                case 1: busca_binaria(vetor_int, tam); break;
                case 2: remocao_em_lista_ordenada(vetor_int, &tam); break;
                case 3: substituir_elemento(vetor_int, tam); break;
                case 4: ordenação_de_inteiros_DEcrecente(vetor_int, tam); break;
                case 5: ordenação_de_inteiros_crecente(vetor_int, tam); break;
                case 6:break;
            }

        } else if(ent_1 == 'D' || ent_1 == 'd') {
            printf("\n\n========= MENU DESORDENADO =========\n");
            printf("CRIAR LISTA -> 0\nBUSCAR SEQUENCIAL -> 1\nREMOVER ITEM -> 2\nSUBSTITUIR ITEM -> 3\n");
            printf("REALOCAR ESPACO DA LISTA-> 4\nIMPRIMIR LISTA-> 5\nVOLTAR-> 6\nOpcao: ");
            scanf("%d", &ent_2);

            switch(ent_2) {
                case 0: vetor_int = adicao_em_lista_desordenada(&tam); break;
                case 1: busca_sequencial(vetor_int, tam); break;
                case 2: remocao_em_lista(vetor_int, &tam); break;
                case 3: substituir_elemento(vetor_int, tam); break;
                case 4: vetor_int = realocar_vetor (vetor_int,&tam);break;
                case 5: imprimir_vetor(vetor_int, tam);break;
                case 6: break;
            }
          if(ent_1 != 'S' && ent_1 != 's' &&
        ent_1 != 'D' && ent_1 != 'd' &&
        ent_1 != 'O' && ent_1 != 'o')
            {
        printf("\n ==== entrada fora da tabela,tente novamente ====\n");
        }

    } 
}
    while(ent_1 != 'S' && ent_1 != 's');

    printf("Encerrando o programa....\n");
    getchar();
    free(vetor_int);
    return 0;


}