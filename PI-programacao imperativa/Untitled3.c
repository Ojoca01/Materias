#include <stdio.h>

int main() {
    char nome[50], sexo;
    int idade;

    // Ler nome, sexo e idade
    printf("Digite o nome: ");
    fgets(nome, sizeof(nome), stdin);

    printf("Digite o sexo (f ou m): ");
    scanf(" %c", &sexo);

    printf("Digite a idade: ");
    scanf("%d", &idade);

    // Verificar as condições
    if ((sexo == 'f' || sexo == 'F') && idade < 25) {
        printf("%sACEITA\n", nome);
    } else {
        printf("%sNÃO ACEITA\n", nome);
    }

    return 0;
}
