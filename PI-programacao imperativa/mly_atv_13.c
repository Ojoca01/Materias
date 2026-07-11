#include <stdio.h>
#include <stdlib.h>

int main() {
    int n = 5;

    int *vet1 = (int *) malloc(n * sizeof(int));
    int *vet2 = (int *) calloc(n, sizeof(int));

    printf("Conteudo do malloc:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", vet1[i]);  // valores aleatórios (lixo de memória)

    printf("\n\nConteudo do calloc:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", vet2[i]);  // tudo zero

    free(vet1);
    free(vet2);
    return 0;
}
