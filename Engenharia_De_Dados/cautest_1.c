#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 200

// Estrutura do discente
typedef struct {
    char matricula[TAM];
    char nome[TAM];
    int ano_ingresso;
    int periodo_ingresso;
    char tipo[TAM];
    char status[TAM];
    char nivel[TAM];
    char curso[TAM];
    char modalidade[TAM];
    char unidade[TAM];
    char unidade_gestora[TAM];
} Discente;


// Imprimir discente
void imprimirDiscente(Discente d) {
    printf("Matricula: %s\n", d.matricula);
    printf("Nome: %s\n", d.nome);
    printf("Ano Ingresso: %d\n", d.ano_ingresso);
    printf("Periodo Ingresso: %d\n", d.periodo_ingresso);
    printf("Tipo: %s\n", d.tipo);
    printf("Status: %s\n", d.status);
    printf("Nivel: %s\n", d.nivel);
    printf("Curso: %s\n", d.curso);
    printf("Modalidade: %s\n", d.modalidade);
    printf("Unidade: %s\n", d.unidade);
    printf("Unidade Gestora: %s\n", d.unidade_gestora);
    printf("-----------------------------------\n");
}


// Salvar em arquivo
void salvarEmArquivo(Discente *lista, int n) {
    FILE *f = fopen("saida.txt", "w");

    if (!f) {
        printf("Erro ao criar arquivo.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(f, "Matricula: %s\n", lista[i].matricula);
        fprintf(f, "Nome: %s\n", lista[i].nome);
        fprintf(f, "Ano Ingresso: %d\n", lista[i].ano_ingresso);
        fprintf(f, "Periodo Ingresso: %d\n", lista[i].periodo_ingresso);
        fprintf(f, "Tipo: %s\n", lista[i].tipo);
        fprintf(f, "Status: %s\n", lista[i].status);
        fprintf(f, "Nivel: %s\n", lista[i].nivel);
        fprintf(f, "Curso: %s\n", lista[i].curso);
        fprintf(f, "Modalidade: %s\n", lista[i].modalidade);
        fprintf(f, "Unidade: %s\n", lista[i].unidade);
        fprintf(f, "Unidade Gestora: %s\n", lista[i].unidade_gestora);
        fprintf(f, "-----------------------------------\n");
    }

    fclose(f);
}


// Função para ler CSV com alocação dinâmica
Discente* lerCSV(const char *nomeArquivo, int *total) {
    FILE *f = fopen(nomeArquivo, "r");

    if (!f) {
        printf("Erro: arquivo não encontrado.\n");
        *total = 0;
        return NULL;
    }

    char linha[1024];

    // Capacidade inicial
    int capacidade = 10;
    Discente *lista = malloc(capacidade * sizeof(Discente));

    if (!lista) {
        printf("Erro de memória.\n");
        fclose(f);
        *total = 0;
        return NULL;
    }

    int count = 0;

    // Ignorar cabeçalho
    fgets(linha, sizeof(linha), f);

    while (fgets(linha, sizeof(linha), f)) {

        // Se encher, dobra capacidade
        if (count >= capacidade) {
            capacidade *= 2;
            Discente *temp = realloc(lista, capacidade * sizeof(Discente));

            if (!temp) {
                printf("Erro ao realocar memória.\n");
                free(lista);
                fclose(f);
                *total = 0;
                return NULL;
            }

            lista = temp;
        }

        linha[strcspn(linha, "\n")] = 0;

        char *token = strtok(linha, ",");

        if (token) strcpy(lista[count].matricula, token);

        token = strtok(NULL, ",");
        if (token) strcpy(lista[count].nome, token);

        token = strtok(NULL, ",");
        if (token) lista[count].ano_ingresso = atoi(token);

        token = strtok(NULL, ",");
        if (token) lista[count].periodo_ingresso = atoi(token);

        token = strtok(NULL, ",");
        if (token) strcpy(lista[count].tipo, token);

        token = strtok(NULL, ",");
        if (token) strcpy(lista[count].status, token);

        token = strtok(NULL, ",");
        if (token) strcpy(lista[count].nivel, token);

        token = strtok(NULL, ",");
        if (token) strcpy(lista[count].curso, token);

        token = strtok(NULL, ",");
        if (token) strcpy(lista[count].modalidade, token);

        token = strtok(NULL, ",");
        if (token) strcpy(lista[count].unidade, token);

        token = strtok(NULL, ",");
        if (token) strcpy(lista[count].unidade_gestora, token);

        count++;
    }

    fclose(f);

    *total = count;
    return lista;
}


// Função principal
int main() {
    int total = 0;

    Discente *lista = lerCSV("dis-csv-discentes-de-graduacao-de-2025.csv", &total);

    if (!lista) {
        return 1;
    }

    printf("Total de discentes: %d\n\n", total);

    // Imprimir alguns
    for (int i = 0; i < total && i < 5; i++) {
        imprimirDiscente(lista[i]);
    }

    // Salvar em arquivo
    salvarEmArquivo(lista, total);

    // Liberar memória
    free(lista);

    return 0;
}