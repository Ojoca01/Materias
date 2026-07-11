#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int idade;
    float peso;
    char nome[50];
} Atleta;

int main() {
    Atleta *atletas = NULL; // ponteiro inicial vazio
    int contador = 0;
    char entrada;
    float soma_peso = 0;

    printf("\n=== Cadastro de Atletas ===\n");

    while (1) {
        contador++;
        atletas = realloc(atletas, contador * sizeof(Atleta));

        if (atletas == NULL) {
            printf("Erro ao alocar memória!\n");
            return 1;
        }

        printf("\nAtleta %d\n", contador);

        printf("Nome : ");
        scanf(" %[^\n]", atletas[contador - 1].nome);

        printf("Idade : ");
        scanf("%d", &atletas[contador - 1].idade);

        printf("Peso : ");
        scanf("%f", &atletas[contador - 1].peso);

        soma_peso += atletas[contador - 1].peso;

        printf("\nDeseja sair? digite 'S'.\nDeseja continuar? digite qualquer outra tecla: ");
        scanf(" %c", &entrada);

        if (entrada == 'S' || entrada == 's') {
            printf("\nEncerrando entrada de dados...\n");
            break;
        }
    }

    // Exibição da lista
    printf("\n=== Lista de Atletas Cadastrados ===\n");
    for (int i = 0; i < contador; i++) {
        printf("Atleta %d\n", i + 1);
        printf("Nome : %s\n", atletas[i].nome);
        printf("Idade: %d\n", atletas[i].idade);
        printf("Peso : %.2f\n\n", atletas[i].peso);
    }

    // Média dos pesos
    float media_peso = soma_peso / contador;
    printf("Média dos pesos: %.2f\n", media_peso);

    // Atletas menores de idade
    printf("\n=== Atletas menores de idade ===\n");
    int tem_menor = 0;
    for (int i = 0; i < contador; i++) {
        if (atletas[i].idade < 18) {
            printf("%s (%d anos)\n", atletas[i].nome, atletas[i].idade);
            tem_menor = 1;
        }
    }
    if (!tem_menor) {
        printf("Nenhum atleta menor de idade.\n");
    }

    // Libera memória
    free(atletas);
    return 0;
}
