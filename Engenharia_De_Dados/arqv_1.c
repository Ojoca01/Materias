#include <stdio.h>

int main() {
    FILE *arquivo = fopen("dados.csv", "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo\n");
        return 1;
    }

    fprintf(arquivo, "Nome; Idade; Nota\n");
    fprintf(arquivo, "Joao; 20; 8.5\n");
    fprintf(arquivo, "Maria; 22; 9.0\n");


    fclose(arquivo);


    printf("Arquivo CSV criado com sucesso!\n");

    return 0;
}