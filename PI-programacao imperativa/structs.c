#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>

/*
// Definição da estrutura Aluno
typedef struct {
    char nome[30];
    int matricula;
    float nota1;
    float nota2;
    float nota3;
} Aluno;

// Função para calcular a média do aluno
float calcular_media(Aluno aluno) {
    return (aluno.nota1 + aluno.nota2 + aluno.nota3) / 3;
}

int main() {
    setlocale(LC_ALL, "Portuguese"); // Suporte a caracteres especiais
    Aluno aluno;

    // Leitura dos dados do aluno
    printf("Digite o nome do aluno: ");
    fgets(aluno.nome, 30, stdin);
    aluno.nome[strcspn(aluno.nome, "\n")] = 0; // Remover nova linha

    printf("Digite a matrícula do aluno: ");
    scanf("%d", &aluno.matricula);

    printf("Digite a primeira nota do aluno: ");
    scanf("%f", &aluno.nota1);

    printf("Digite a segunda nota do aluno: ");
    scanf("%f", &aluno.nota2);

    printf("Digite a terceira nota do aluno: ");
    scanf("%f", &aluno.nota3);

    // Cálculo da média
    float media = calcular_media(aluno);

    // Exibição dos dados
    printf("\nDados do aluno:\n");
    printf("Nome: %s\n", aluno.nome);
    printf("Matrícula: %d\n", aluno.matricula);
    printf("Notas: %.2f, %.2f, %.2f\n", aluno.nota1, aluno.nota2, aluno.nota3);
    printf("Média: %.2f\n", media);

    // Verificação de aprovação
    if (media >= 6.0) {
        printf("Status: Aprovado\n");
    } else {
        printf("Status: Reprovado\n");
    }

    return 0;
} */



// Definindo a estrutura para armazenar dados dos atletas
/*
typedef struct {
    char nome[50];
    int idade;
    float peso;
} Atleta;

int main() {
    setlocale(LC_ALL, "Portuguese"); // Suporte a caracteres especiais
    Atleta atletas[50];  // Declaração do array de atletas
    int n, i, menordeidade = 0;
    float soma_pesos = 0.0;

    // Entrada de dados
    printf("Digite o número de atletas (máximo 50): ");
    scanf("%d", &n);
    getchar(); // Para consumir o '\n' deixado pelo scanf

    for (i = 0; i < n; i++) {
        printf("\nAtleta %d\n", i + 1);
        printf("Nome: ");
        fgets(atletas[i].nome, sizeof(atletas[i].nome), stdin);
        atletas[i].nome[strcspn(atletas[i].nome, "\n")] = '\0'; // Remover o '\n' extra
        printf("Idade: ");
        scanf("%d", &atletas[i].idade);
        printf("Peso: ");
        scanf("%f", &atletas[i].peso);
        getchar(); // Para consumir o '\n' deixado pelo scanf

        soma_pesos += atletas[i].peso;

        if (atletas[i].idade < 18) {
            menordeidade++;
        }
    }

    // Função da ordem alfabética
    int compararAtletas(const void *a, const void *b) {
        Atleta *atleta1 = (Atleta *)a;
        Atleta *atleta2 = (Atleta *)b;
        return strcmp(atleta1->nome, atleta2->nome);
    }

    // Ordenação dos atletas em ordem alfabética
    qsort(atletas, n, sizeof(Atleta), compararAtletas);

    // Exibição dos dados
    printf("\nListagem dos Atletas em Ordem Alfabética:\n");
    for (i = 0; i < n; i++) {
        printf("Nome: %s, Idade: %d, Peso: %.2f\n", atletas[i].nome, atletas[i].idade, atletas[i].peso);
    }

    // Exibir a média dos pesos e quantos atletas são menores de idade
    printf("\nMédia dos Pesos: %.2f\n", soma_pesos / n);
    printf("Quantidade de Atletas Menores de Idade: %d\n", menordeidade);

    return 0;
}*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#define MAX_CANDIDATOS 100

typedef struct {
    char nome[30];
    int matricula;
    float pontuacao;
} Candidato;

// Função para comparar nomes alfabeticamente
int ordenar_candidatos(const void *a, const void *b) {
    Candidato *candidato1 = (Candidato *)a;
    Candidato *candidato2 = (Candidato *)b;
    return strcmp(candidato1->nome, candidato2->nome);
}

// Função para comparar pontuações (ordem decrescente)
int ordenar_pontuacao(const void *a, const void *b) {
    Candidato *candidato1 = (Candidato *)a;
    Candidato *candidato2 = (Candidato *)b;

    if (candidato2->pontuacao > candidato1->pontuacao) return 1;
    if (candidato2->pontuacao < candidato1->pontuacao) return -1;
    return 0;
}

void main() {
    setlocale(LC_ALL, "Portuguese"); // Suporte a caracteres especiais
    Candidato candidato[MAX_CANDIDATOS]; // Declaração do array de candidatos
    int n, i, valor;

    // Entrada de dados
    printf("Digite o número de candidatos (máximo 100): ");
    scanf("%d", &n);
    getchar(); // Para consumir o '\n' deixado pelo scanf

    for (i = 0; i < n; i++) {
        printf("\nCandidato %d\n", i + 1);
        printf("Nome: ");
        fgets(candidato[i].nome, sizeof(candidato[i].nome), stdin);
        candidato[i].nome[strcspn(candidato[i].nome, "\n")] = '\0'; // Remover o '\n' extra

        printf("Matrícula: ");
        scanf("%d", &candidato[i].matricula);

        printf("Pontuação: ");
        scanf("%f", &candidato[i].pontuacao);
        getchar(); // Para consumir o '\n' deixado pelo scanf
    }

    // Menu para escolha da ordenação
    do {
        printf("\nDigite 1 para ordenar alfabeticamente ou 2 para ordenar por pontuação: ");
        scanf("%d", &valor);
        getchar();

        switch (valor) {
            case 1:
                qsort(candidato, n, sizeof(Candidato), ordenar_candidatos);
                printf("\nListagem dos Candidatos em Ordem Alfabética:\n");
                break;

            case 2:
                qsort(candidato, n, sizeof(Candidato), ordenar_pontuacao);
                printf("\nListagem dos Candidatos por Pontuação:\n");
                break;

            default:
                printf("\nOpção inválida. Tente novamente.\n");
                continue;
        }

        // Exibição da listagem
        for (i = 0; i < n; i++) {
            printf("Nome: %s, Matrícula: %d, Pontuação: %.2f\n",
                candidato[i].nome, candidato[i].matricula, candidato[i].pontuacao);
        }

        printf("\nDeseja ver outra listagem? (1 - Sim, 0 - Sair): ");
        scanf("%d", &valor);
        getchar();

    } while (valor == 1);

    return 0;
}


