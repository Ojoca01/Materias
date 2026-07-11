#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 200 // define constante o tamanho máximo para strings usadas na struct Discente

/*Implementação com arquivos de Joâo Carlos Cruz Santos e Cauet Mendes
A atividade consistirá na leitura de um arquivo .csv, carregamento dos dados em memória e em seguida salvar os dados num arquivo texto. Segue a descrição de cada etapa.
1. Verificar o cabeçalho do arquivo dis-csv-discentes-de-graduacao-de-2025.csv ok
1.1. Criar uma estrutura para representar um discente. Pode ser através de registros ou criação de uma classe. 
2. Fazer uma função para percorrer as linhas do arquivo .csv e criar uma lista/array de discentes. Cada posição da lista/array deve representar um discente do arquivo .csv
3. Fazer uma função para a impressão de um discente. Fiquem livres para decidir o formato, o importante é que todos os dados do discente sejam apresentados. É necessário apresentar o nome de cada campo e valor referente ao discente
4. Fazer uma função para salvar em arquivo textos os dados dos discentes no formato da função de impressão.
5. Fazer uma função principal para executar os métodos de leitura do .csv e de escrita do arquivo texto.
6. O código deve ser comentado

Estrutura do discente em semelhança ao cabeçalho do arquivo CSV feito com struct para armazenar os dados de cada discente

    matricula,
    nome_discente,
    ano_ingresso,
    periodo_ingresso,
    tipo_discente,
    status_discente,
    nivel_ensino,
    nome_curso,
    modalidade_educacao,
    nome_unidade,
    nome_unidade_gestora  */

    // 1 e 1.1
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

// funcões auxiliares ================================================
void imprimirDiscente(Discente d) {  //imprimi os dados de um discente, apresentando o nome de cada campo e o valor correspondente, é chavadavarias vezes posteiormente
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

void fprintarDiscente(FILE *arquivo, Discente d) {// semelhante a função imprimirDiscente, mas ao invés de imprimir na tela, escreve os dados do discente em um arquivo texto, seguindo o mesmo formato de apresentação dos campos e valores
     fprintf(arquivo, "Matricula: %s\n", d.matricula);
        fprintf(arquivo, "Nome: %s\n", d.nome);
        fprintf(arquivo, "Ano Ingresso: %d\n", d.ano_ingresso);
        fprintf(arquivo, "Periodo Ingresso: %d\n", d.periodo_ingresso);
        fprintf(arquivo, "Tipo: %s\n", d.tipo);
        fprintf(arquivo, "Status: %s\n", d.status);
        fprintf(arquivo, "Nivel: %s\n", d.nivel);
        fprintf(arquivo, "Curso: %s\n", d.curso);
        fprintf(arquivo, "Modalidade: %s\n", d.modalidade);
        fprintf(arquivo, "Unidade: %s\n", d.unidade);
        fprintf(arquivo, "Unidade Gestora: %s\n", d.unidade_gestora);
        fprintf(arquivo, "-----------------------------------\n");

}

void mostrarMenu() { // imprime na tela um menu de opcoes para que o usuario possa interagir com a aplicação, escolhendo as funcoes a serem usadas
    printf("\n\nMenu de Opções:\n");
    printf("1. Imprimir um discente específico\n");
    printf("2. Imprimir toda a lista dos discentes\n");
    printf("3. Salvar em arquivo\n");
    printf("4. Sair\n");
}

void limpar_string(char *str) {
    if (str == NULL) return;

    // 1. Remove \r e \n
    str[strcspn(str, "\r\n")] = '\0';

    // 2. Remove aspas
    char *src = str, *dst = str;
    while (*src) {
        if (*src != '"') {
            *dst++ = *src;
        }
        src++;
    }
    *dst = '\0';

    // 3. Remove espaços no início
    while (*str == ' ') {
        memmove(str, str + 1, strlen(str));
    }

    // 4. Remove espaços no final
    int len = strlen(str);
    while (len > 0 && str[len - 1] == ' ') {
        str[len - 1] = '\0';
        len--;
    }
}

/*strncpy(d_atual->nome, token, TAM - 1);
 d_atual->nome[TAM - 1] = '\0'; opcao para evitar overflow se necessario(nao foi) */

void criartokens(Discente *d_atual, char *linha) {
    char *token = strtok(linha, ","); // função para dividir a linha em tokens usando a vírgula como delimitador 
    if (token) {
        limpar_string(token);
        strcpy(d_atual->matricula, token);}

    token = strtok(NULL, ","); // continua a dividir a linha, passando NULL para continuar de onde parou, e armazenando os dados do discente na estrutura, depois disso basta fazer um para cada campo a ser preenchido
    if (token){ 
        limpar_string(token);
        strcpy(d_atual->nome, token); }// nome
 
    token = strtok(NULL, ","); //ano de ingresso
    if (token) {
         limpar_string(token);
        d_atual->ano_ingresso = atoi(token);}

    token = strtok(NULL, ","); //periodo de ingresso
    if (token) {
        limpar_string(token);
        d_atual->periodo_ingresso = atoi(token);
    } // atoi faz connverao de string para numero inteiro 

    token = strtok(NULL, ",");// tipo de discente
    if (token) {
        limpar_string(token);
        strcpy(d_atual->tipo, token);
    }

    token = strtok(NULL, ",");// status do discente
    if (token) {
        limpar_string(token);
        strcpy(d_atual->status, token);
    }

    token = strtok(NULL, ",");// nivel de ensino
    if (token) {
        limpar_string(token);
        strcpy(d_atual->nivel, token);
    }

    token = strtok(NULL, ",");// nome do curso
    if (token) {
        limpar_string(token);
        strcpy(d_atual->curso, token);
    }

    token = strtok(NULL, ",");// modalidade de educação
    if (token) {
        limpar_string(token);
        strcpy(d_atual->modalidade, token);
    }

    token = strtok(NULL, ",");// nome da unidade
    if (token) {
        limpar_string(token);
        strcpy(d_atual->unidade, token);
    }

    token = strtok(NULL, ",");//  nome da unidade gestora
    if (token) {
        limpar_string(token);
        strcpy(d_atual->unidade_gestora, token);
    }
} 

// 2
Discente* percorerCSV(const char *nomeArquivo, int *total) { // Função para ler CSV com alocação dinâmica (2)
    char linha[1024]; // tamanho padrão para ler linhas do CSV 
    int capacidade = 10; // Capacidade inicial de alunos

    FILE *arquivo = fopen(nomeArquivo, "r"); // abrir o arquivo para leitura( modo "r")
    if (!arquivo) {
        printf("Erro: arquivo não encontrado.\n"); // verificar se o arquivo foi aberto com sucesso
        *total = 0;
        return NULL;
    }
    
    Discente *lista_discentes = malloc(capacidade * sizeof(Discente));
    if (!lista_discentes) {
        printf("Erro de memória.\n"); // verificar se a alocação de memória foi bem-sucedida
        fclose(arquivo);
        *total = 0;
        return NULL;
    }

    if (!fgets(linha, sizeof(linha), arquivo)) {//le a a primeira linha (cabeçalho)se der certo segue senao fecha o arquivo, libera a memoria alocada,zera o total e retorna null para sair da funcao 
    printf("Erro ao ler cabeçalho.\n");
    fclose(arquivo);
    free(lista_discentes);
    *total = 0;
    return NULL;
}
    int count = 0;
    while (fgets(linha, sizeof(linha), arquivo)) {     //em seguida indo para um laco que le cada linha do arquivo, armazena os dados em um array de estruturas do tipo Discente e realoca a memória se necessário para acomodar mais discentes.
        // Se encher, dobra capacidade
        linha[strcspn(linha, "\n")] = 0;
        if (count >= capacidade) {
            capacidade *= 2;
            Discente *temp = realloc(lista_discentes, capacidade * sizeof(Discente));
            if (!temp) {
                printf("Erro ao realocar memória.\n");
                free(lista_discentes);
                fclose(arquivo);
                *total = 0;
                return NULL;
            }

            lista_discentes = temp;
        }
        criartokens(&lista_discentes[count], linha); // função para criar os tokens e armazenar os dados do discente na estrutura
        count++;
    }

    fclose(arquivo);

    *total = count;
    return lista_discentes;
}

// 3
void imprimirDiscente_especifico(Discente *lista_discentes, const char*matricula,int total) { // recebe a lista de discentes, a matrícula do discente a ser impresso e o total de discentes para realizar uma busca linear e encontrar o discente correspondente à matrícula fornecida, caso encontrado, imprime os dados do discente usando a função imprimirDiscente
    Discente *d_atual = NULL;
    int subs = 0; 
    for (int i = 0; i < total; i++) { // funcao de busca linear simples, para encontrar um discennte em especifico pela matricula
        if (strcmp(lista_discentes[i].matricula, matricula) == 0) {
            d_atual = &lista_discentes[i];
            subs=i;
            break;
        }
    }  
    if (!d_atual) {
        printf("Discente com matrícula %s não encontrado.\n", matricula); // caso o discente nao seja encontrado, imprime uma mensagem de erro
        return;
    }
    printf("Discente encontrado de campo[%d]:\n", subs+2); // Imprime o índice do campo encontrado (subs+2 para ajustar ao índice real considerando o cabeçalho)
    imprimirDiscente(*d_atual); // Imprime o discente encontrado

}

// 4 
void salvarEmArquivo(Discente *lista_discentes, int total) { // salva os dados dos discentes em um arquivo texto, criando um arquivo chamado Save_ListadeDiscentes.txt e escrevendo os dados de cada discente usando a função fprintarDiscente, que formata a saída de maneira semelhante à função imprimirDiscente, mas direcionada para um arquivo.

    FILE *arquivo = fopen("Save_ListadeDiscentes.txt", "w"); // abrir o arquivo para escrita (modo "w")
    
    if (!arquivo) {
        printf("Erro ao criar arquivo.\n"); // verificar se o arquivo foi criado com sucesso
        return;
    }
    for (int i = 0; i < total; i++) {
       fprintarDiscente(arquivo, lista_discentes[i]);   
    }
    printf("Dados salvos em Save_ListadeDiscentes.txt com sucesso.\n"); // mensagem de confirmação de que os dados foram salvos com sucesso
    fclose(arquivo);// fechar o arquivo após a operação (escrita)
}



// Função principal
int main() { // a funcao pricipal reune a aplicacao de todas as funcoes criadas, lendo o arquivo CSV, armazenando os dados em um array de estruturas do tipo Discente, e apresentando um menu para o usuário escolher entre imprimir um discente específico, imprimir toda a lista de discentes ou salvar os dados em um arquivo texto. O programa continua a executar até que o usuário escolha sair (opção 4), e ao final libera a memória alocada para a lista de discentes.
    int senha_menu = 0;
    int total = 0;

    Discente *lista_discentes = percorerCSV("dis-csv-discentes-de-graduacao-de-2025_1.csv", &total);
    if (!lista_discentes) {
        return 0; // Se houve erro na leitura do CSV, termina o programa
    }

    
    
    while (senha_menu != 4) {
    mostrarMenu(); // mostra o menu de opções para o usuário
    printf("Escolha uma opção: ");
    scanf("%d", &senha_menu);

    switch (senha_menu){
    
        case 1: {
            char matricula[TAM];
            printf("Digite a matrícula do discente: ");
            scanf("%199s", matricula);
            imprimirDiscente_especifico(lista_discentes, matricula, total); //chama a funcao imprimit discente para um discente específico, passando a lista de discentes, a matrícula fornecida pelo usuário e o total de discentes para realizar a busca e impressão do discente correspondente
            }
        break;

        case 2:{
            printf("Lista de todos os discentes:\n");
            for (int i = 0; i < total; i++) {
            imprimirDiscente(lista_discentes[i]);  // percorre a lista de discentes e imprime os dados de cada discente usando a função imprimirDiscente, apresentando toda a lista de discentes para o usuário
            }
        }   
            break;
    
        case 3:
            salvarEmArquivo(lista_discentes, total); // Chama a função para salvar os discentes em um arquivo texto    
        break;

        case 4:
            printf("Saindo do programa...\n");
        break;
    
    }
}

    // Liberar memória
    free(lista_discentes);

    return 0;


}