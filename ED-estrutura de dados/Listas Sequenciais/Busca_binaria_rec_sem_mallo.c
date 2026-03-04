#include <stdio.h>

// Função para preencher o vetor
void entrada_de_dados(int vetor[], int *tam) {

    printf("\n=== Insira os dados (em ordem crescente) ===\n");
    for (int j = 0; j < *tam; j++) {
        printf("Elemento [%d]: ", j + 1);
        scanf("%d", &vetor[j]);
    }
}

// Função de busca binária
int busca_binaria(int vetor[], int tam, int elem) {
    int inicio = 0, fim = tam - 1, meio;

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;

        if (vetor[meio] == elem)
            return meio;
        else if (vetor[meio] < elem)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }

    return -1; // não encontrado
}

// Função principal
int main() {
    int tam;

    printf("Quantos elementos deseja inserir? ");
    scanf("%d", &tam);

    int vetor[tam]; // VLA — vetor com tamanho definido pelo usuário

    entrada_de_dados(vetor, &tam);

    int elem;
    printf("\nDigite o termo que deseja buscar: ");
    scanf("%d", &elem);

    int pos = busca_binaria(vetor, tam, elem);

    if (pos != -1)
        printf("\n Termo encontrado no indice: %d\n", pos);
    else
        printf("\n Termo nao encontrado.\n");

    return 0;
}
