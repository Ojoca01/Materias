#include <stdio.h>
#include <stdlib.h>

// ================= Funções de Vetor =================

// Criação da lista vazia
int* Listas_vazias(int *tam) {
    printf("Quantos elementos deseja inserir inicialmente? ");
    scanf("%d", tam);

    int *vetor_int = malloc(*tam * sizeof(int));
    if (!vetor_int) {
        printf("\nErro ao alocar memoria!\n");
        return NULL;
    }

    return vetor_int;
}

// Inserção inicial em lista desordenada
int* adicao_em_lista_desordenada(int *tam) {
    int *vetor_int = Listas_vazias(tam);
    if (!vetor_int) return NULL;

    printf("\n=== Insira os dados ===\n");
    for (int j = 0; j < *tam; j++) {
        printf("Elemento [%d]: ", j + 1);
        scanf("%d", &vetor_int[j]);
    }

    return vetor_int;
}

// Realocação e inserção de novo dado
int* realocar_vetor(int *vetor_int, int *tam, int novo_dado) {
    int novo_tam = *tam + 1;
    int *temp = realloc(vetor_int, novo_tam * sizeof(int));
    if (!temp) {
        printf("Erro ao realocar memoria!\n");
        return vetor_int;
    }

    vetor_int = temp;
    vetor_int[*tam] = novo_dado;
    *tam = novo_tam;
    return vetor_int;
}

// Ordenação crescente (para busca binária)
int* ordenação_de_inteiros_crecente(int* vetor_int, int tam) {
    int aux;
    for(int x = 0; x < tam - 1; x++){
        for(int y = x + 1; y < tam; y++){
            if(vetor_int[x] > vetor_int[y]){
                aux = vetor_int[x];
                vetor_int[x] = vetor_int[y];
                vetor_int[y] = aux;
            }
        }
    }
    return vetor_int;
}

// Impressão do vetor
void mostrar_vetor(int *vetor, int tam) {
    printf("\nVetor: ");
    for(int i = 0; i < tam; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

// ================= Funções de Busca =================

// Busca sequencial para vetor desordenado
int busca_sequencial(int* vetor_int, int tam) {
    int termo_pesquisado;
    int indice = -1;

    printf("\n=== BUSCA SEQUENCIAL ===\n");
    printf("Digite o valor a ser buscado: ");
    scanf("%d", &termo_pesquisado);

    for (int k = 0; k < tam; k++) {
        if (vetor_int[k] == termo_pesquisado) {
            indice = k;
            break;
        }
    }

    if (indice != -1)
        printf("Termo encontrado no indice: %d\n", indice);
    else
        printf("Termo nao encontrado!\n");

    return indice;
}

// Busca binária para vetor ordenado
int busca_binaria(int* vetor_int, int tam) {
    int termo_pesquisado;
    int inicio = 0, fim = tam - 1;
    int indice = -1;

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

// ==================== Menu Principal ====================

int main() {
    int *vetor_int = NULL;
    int tam = 0;
    char ent_1;
    int ent_2;

    do {
        printf("\n\n========= MENU PRINCIPAL =========\n");
        printf("LISTAS ORDENADAS -> O\nLISTAS DESORDENADAS -> D\nSair -> S\nOpcao: ");
        scanf(" %c", &ent_1);

        if(ent_1 == 'O' || ent_1 == 'o') {
            printf("\n========= MENU ORDENADO =========\n");
            printf("CRIAR LISTA -> 0\nBUSCAR ITEM -> 1\nINSERIR NOVO ITEM -> 2\nMOSTRAR LISTA -> 3\n");
            printf("VOLTAR -> 4\nOpcao: ");
            scanf("%d", &ent_2);

            switch(ent_2) {
                case 0:
                    vetor_int = adicao_em_lista_desordenada(&tam);
                    ordenação_de_inteiros_crecente(vetor_int, tam);
                    break;
                case 1:
                    busca_binaria(vetor_int, tam);
                    break;
                case 2:
                    int novo;
                    printf("Digite o novo valor a inserir: ");
                    scanf("%d", &novo);
                    vetor_int = realocar_vetor(vetor_int, &tam, novo);
                    ordenação_de_inteiros_crecente(vetor_int, tam);
                    break;
                case 3:
                    mostrar_vetor(vetor_int, tam);
                    break;
                case 4:
                    break;
            }

        } else if(ent_1 == 'D' || ent_1 == 'd') {
            printf("\n========= MENU DESORDENADO =========\n");
            printf("CRIAR LISTA -> 0\nBUSCAR ITEM -> 1\nINSERIR NOVO ITEM -> 2\nMOSTRAR LISTA -> 3\nVOLTAR -> 4\nOpcao: ");
            scanf("%d", &ent_2);

            switch(ent_2) {
                case 0:
                    vetor_int = adicao_em_lista_desordenada(&tam);
                    break;
                case 1:
                    busca_sequencial(vetor_int, tam);
                    break;
                case 2:
                    int novo;
                    printf("Digite o novo valor a inserir: ");
                    scanf("%d", &novo);
                    vetor_int = realocar_vetor(vetor_int, &tam, novo);
                    break;
                case 3:
                    mostrar_vetor(vetor_int, tam);
                    break;
                case 4:
                    break;
            }
        }

    } while(ent_1 != 'S' && ent_1 != 's');

    free(vetor_int);
    printf("Programa encerrado.\n");
    return 0;
}
