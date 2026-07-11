#include <stdio.h>
#include <string.h>

char detectarSeparador(char *linha) {
    int virgula = 0;
    int pontoVirgula = 0;

    for (int i = 0; linha[i] != '\0'; i++) {
        if (linha[i] == ',') virgula++;
        if (linha[i] == ';') pontoVirgula++;
    }

    if (pontoVirgula > virgula)
        return ';';
    else
        return ',';
}

int main() {
    FILE *arquivo = fopen("dados.csv", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo\n");
        return 1;
    }

    char linha[200];

    fgets(linha, sizeof(linha), arquivo);

    char separador = detectarSeparador(linha);

    printf("Separador detectado: %c\n", separador);

    fclose(arquivo);
    return 0;
}