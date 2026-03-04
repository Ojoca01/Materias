/*
Grupo 2 -> Integrantes:
   João Carlos Cruz Santos
   Ian Pedro Oliveira Novais
   Iarlo Breno Damasceno de Sá
   Cauet Mendes França de A.
   Allan Gustavo da Silva Soares
   Edson dos Santos Santana
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ========================= TIPOS / ESTRUTURAS ==========================

// Estrutura que representa uma disciplina cursada por um aluno.
typedef struct Disciplina
{
    char nome[256];
    float nota;
    int presenca;
    char situacao[3];
    int periodo;
    struct Disciplina *prox;
} Disciplina;

// Cabeça da lista de disciplinas (para facilitar operações na sublista)
typedef struct NoCabecaDisciplinas
{
    Disciplina *inicio;
    Disciplina *final;
    int quant;
} NoCabecaDisciplinas;

// Estrutura que representa um aluno na lista principal
typedef struct Aluno
{
    char nome[50];
    int matricula;
    struct Aluno *ant;
    struct Aluno *prox;
    NoCabecaDisciplinas disciplinas;
} Aluno;

// Cabeça da lista principal de alunos
typedef struct NoCabecaAlunos
{
    Aluno *inicio;
    Aluno *final;
    int quant;
} NoCabecaAlunos;

// ========================= FUNÇÕES AUXILIARES ==========================

// Inicializa os campos da cabeça da lista de alunos para evitar lixo de memória
void alocarNoCabeca(NoCabecaAlunos *no)
{
    no->inicio = NULL;
    no->final = NULL;
    no->quant = 0;
}

// Limpa o buffer de entrada até encontrar um '\n'.
void limparBuffer()
{
    while (getchar() != '\n')
        ;
}

// Pausa a execução pedindo para o usuário pressionar Enter
void pausarExecucao()
{
    limparBuffer();
    printf("\nPressione Enter para voltar ao menu principal...");
    getchar();
}

// ========================= CÁLCULO DE SITUAÇÃO ==========================

/*
   Determina a situação automaticamente (quando situcao_informada for NULL ou
   vazia). Possíveis valores usados no projeto: AP (aprovado), RM (reprovado por média),
   RF (reprovado por falta) e TR (trancado).

   Regras aplicadas neste código:
     - Se presenca < 50 => RF
     - Senão, se nota >= 7 => AP
     - Senão => RM
   Se situacao_informada for "TR", usa "TR" diretamente.
*/
void calcularSituacao(char *dest, float nota, int presenca, const char *situacao_informada)
{
    if (situacao_informada != NULL && strcmp(situacao_informada, "TR") == 0)
    {
        strncpy(dest, "TR", 3);
        dest[2] = '\0';
        return;
    }

    if (presenca < 50)
        strncpy(dest, "RF", 3);
    else if (nota >= 7.0f)
        strncpy(dest, "AP", 3);
    else
        strncpy(dest, "RM", 3);

    dest[2] = '\0';
}

// ========================= CRIAÇÃO DE NÓS ================================

// Aloca e inicializa um novo Aluno (não insere na lista, apenas cria o nó)
Aluno *criarAluno(char *nome, int matricula)
{
    Aluno *novo_aluno = (Aluno *)malloc(sizeof(Aluno));
    if (!novo_aluno)
    {
        printf("ERRO ao alocar memoria!!!\n");
        return NULL;
    }

    // Copia segura do nome
    strncpy(novo_aluno->nome, nome, sizeof(novo_aluno->nome) - 1);
    novo_aluno->nome[sizeof(novo_aluno->nome) - 1] = '\0';
    novo_aluno->matricula = matricula;
    novo_aluno->prox = NULL;
    novo_aluno->ant = NULL;

    // Inicializa a sublista de disciplinas do aluno
    novo_aluno->disciplinas.inicio = NULL;
    novo_aluno->disciplinas.final = NULL;
    novo_aluno->disciplinas.quant = 0;

    return novo_aluno;
}

// Aloca e inicializa uma nova Disciplina (não insere na sublista, apenas cria o nó)
Disciplina *criarDisciplina(char *nome, float nota, int presenca, char *situacao, int periodo)
{
    Disciplina *nova_disciplina = (Disciplina *)malloc(sizeof(Disciplina));
    if (!nova_disciplina)
    {
        printf("Erro ao alocar memória para disciplina.\n");
        return NULL;
    }

    // Nome
    strncpy(nova_disciplina->nome, nome, sizeof(nova_disciplina->nome) - 1);
    nova_disciplina->nome[sizeof(nova_disciplina->nome) - 1] = '\0';

    // Dados básicos
    nova_disciplina->nota = nota;
    nova_disciplina->presenca = presenca;
    nova_disciplina->periodo = periodo;

    // --- CALCULA A SITUAÇÃO ---
    // situacao = parâmetro informado (pode ser NULL ou "TR")
    calcularSituacao(nova_disciplina->situacao,nota,presenca,situacao);

    nova_disciplina->prox = NULL;
    return nova_disciplina;
}

// ========================= CADASTROS =========================

// Insere um novo aluno na lista principal em ordem crescente de matrícula.
// Retorna 1 em caso de sucesso, 0 em caso de falha
int cadastrarAluno(NoCabecaAlunos *noCabeca, char *nome, int matricula)
{
    Aluno *novo_aluno = criarAluno(nome, matricula);
    if (!novo_aluno)
        return 0;

    // Se lista vazia, insere como primeiro e último
    if (noCabeca->inicio == NULL)
    {
        noCabeca->inicio = novo_aluno;
        noCabeca->final = novo_aluno;
        noCabeca->quant++;
        return 1;
    }

    Aluno *atual = noCabeca->inicio;

    // Insere no começo caso a matrícula seja menor que a primeira
    if (matricula < atual->matricula)
    {
        novo_aluno->prox = atual;
        atual->ant = novo_aluno;
        noCabeca->inicio = novo_aluno;
        noCabeca->quant++;
        return 1;
    }

    // Percorre até achar a posição correta (ordem crescente por matrícula)
    while (atual->prox != NULL && atual->prox->matricula < matricula)
        atual = atual->prox;

    // Verifica duplicidade de matrícula
    if (atual->matricula == matricula ||
        (atual->prox && atual->prox->matricula == matricula))
    {
        printf("Matricula %d ja existe.\n", matricula);
        free(novo_aluno);
        return 0;
    }

    // Insere o novo nó após o atual
    novo_aluno->prox = atual->prox;
    novo_aluno->ant = atual;

    if (atual->prox)
        atual->prox->ant = novo_aluno;
    else
        noCabeca->final = novo_aluno; // se for no final, atualiza o ponteiro final

    atual->prox = novo_aluno;
    noCabeca->quant++;

    return 1;
}

// Insere uma disciplina na sublista de um aluno identificado pela matrícula.
void inserirDisciplinaDoAluno(Aluno **lista, int matricula, char *nome, float nota, int presenca, char *situacao, int periodo)
{
    Aluno *alunoAtual = *lista;

    // Procura pelo aluno na lista principal
    while (alunoAtual != NULL)
    {
        if (alunoAtual->matricula == matricula)
        {
            // Cria a disciplina e anexa ao final da sublista
            Disciplina *novaDisciplina = criarDisciplina(nome, nota, presenca, situacao, periodo);

            if (alunoAtual->disciplinas.inicio == NULL)
            {
                alunoAtual->disciplinas.inicio = novaDisciplina;
                alunoAtual->disciplinas.final = novaDisciplina;
                alunoAtual->disciplinas.quant++;
            }
            else
            {
                alunoAtual->disciplinas.final->prox = novaDisciplina;
                alunoAtual->disciplinas.final = novaDisciplina;
                alunoAtual->disciplinas.quant++;
            }
            printf("Disciplina %s cadastrada para o aluno %s.\n", nome, alunoAtual->nome);
            return;
        }
        alunoAtual = alunoAtual->prox;
    }

    // Aluno não encontrado
    printf("Aluno com matrícula %d nao encontrado.\n", matricula);
}

// ========================= ATUALIZAÇÃO DE DISCIPLINA ======================

// Atualiza os campos de uma disciplina em uma sublista (procura pelo nome antigo)
void atualizarDisciplinaDoAluno(Disciplina *lista, char *disciplinaParaAlterar, char *nome, float nota, int presenca, char *situacao, int periodo)
{
    Disciplina *disciplinaAtual = lista;
    int encontrado = 0;

    while (disciplinaAtual != NULL)
    {
        if (strcmp(disciplinaAtual->nome, disciplinaParaAlterar) == 0)
        {
            // Atualiza os campos da disciplina encontrada
            disciplinaAtual->nota = nota;
            disciplinaAtual->presenca = presenca;
            strcpy(disciplinaAtual->situacao, situacao);
            // --- CALCULA A SITUAÇÃO ---
            // situacao = parâmetro informado (pode ser NULL ou "TR")
            calcularSituacao(disciplinaAtual->situacao,nota,presenca,situacao);

            strcpy(disciplinaAtual->nome, nome);
            disciplinaAtual->periodo = periodo;

            printf("Disciplina %s atualizada para o aluno\n", disciplinaParaAlterar);
            encontrado = 1;
            return;
        }
        disciplinaAtual = disciplinaAtual->prox;
    }

    if (encontrado == 0)
    {
        printf("Disciplina %s nao encontrada para o aluno\n", disciplinaParaAlterar);
        return;
    }
}

// ========================= BUSCA DE ALUNO ================================

// Procura um aluno pela matrícula na cabeça da lista de alunos e retorna o ponteiro
Aluno *buscarAluno(NoCabecaAlunos *noCabeca, int matricula)
{
    Aluno *alunoAtual = noCabeca->inicio; // começa do inicio
    while (alunoAtual != NULL)
    {
        if (alunoAtual->matricula == matricula)
        {
            printf("Aluno encontrado!!");
            return alunoAtual;
        }
        alunoAtual = alunoAtual->prox;
    }
    printf("Aluno nao encontrado!!");
    return NULL;
}

// ========================= REMOÇÃO DE DISCIPLINAS =========================

// Libera toda a sublista de disciplinas passada como parâmetro
void removerDisciplinas(Disciplina *lista)
{
    Disciplina *disciplinaAtual = lista;
    while (disciplinaAtual != NULL)
    {
        Disciplina *aux = disciplinaAtual;
        disciplinaAtual = disciplinaAtual->prox;
        free(aux);
    }
}

// Remove um aluno (e suas disciplinas) a partir da matrícula
void removerAluno(NoCabecaAlunos *noCabeca, int matricula)
{
    if (noCabeca->inicio == NULL)
    {
        printf("Lista de alunos vazia.\n");
        return;
    }

    Aluno *aluno = buscarAluno(noCabeca, matricula);
    if (aluno == NULL)
    {
        return;
    }
    else
    {
        // Mensagem de debug/impressão mostrando quant de disciplinas, se existir
        if (aluno->disciplinas.inicio)
            printf("QTD disciplinas: %d, Disciplina %s", aluno->disciplinas.quant, aluno->disciplinas.inicio->nome);
        else
            printf("QTD disciplinas: %d", aluno->disciplinas.quant);
    }

    // Se o aluno tem disciplinas, libera a sublista
    if (aluno->disciplinas.inicio != NULL)
        removerDisciplinas(aluno->disciplinas.inicio);

    // Ajusta os ponteiros da lista duplamente encadeada para remover o nó do aluno
    if (aluno->ant != NULL)
        aluno->ant->prox = aluno->prox;
    else
        noCabeca->inicio = aluno->prox; // estava no início

    if (aluno->prox != NULL)
        aluno->prox->ant = aluno->ant; // atualiza ponteiro anterior do próximo
    else
        noCabeca->final = aluno->ant; // atualiza a cauda, caso tenha sido o último

    noCabeca->quant--;
    free(aluno);
    printf("Aluno removido com sucesso.\n");
}

// ========================= EXIBIÇÃO  ===========================

// Lista todos os alunos cadastrados (imprime nome e matrícula)
void listarAlunos(NoCabecaAlunos *noCabeca)
{
    if (noCabeca->inicio == NULL)
    {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }

    Aluno *alunoAtual = noCabeca->inicio;

    printf("\n=== LISTA DE ALUNOS CADASTRADOS ===\n");

    for (int i = 1; i <= noCabeca->quant; i++)
    {
        printf("%d. Nome: %s | Matricula: %d\n",
               i, alunoAtual->nome, alunoAtual->matricula);
        alunoAtual = alunoAtual->prox;
    }

    printf("Total de alunos: %d\n", noCabeca->quant);
}

// Mostra o histórico (disciplinas) de um aluno específico identificado pela matrícula
void exibirHistorico(NoCabecaAlunos *noCabeca, int matricula)
{
    Aluno *aluno = buscarAluno(noCabeca, matricula);

    if (aluno == NULL)
    {
        printf("Aluno com matricula %d nao encontrado.\n", matricula);
        return;
    }

    printf("\n=== HISTORICO DO ALUNO ===\n");
    printf("Nome: %s\n", aluno->nome);
    printf("Matricula: %d\n", aluno->matricula);
    printf("\n--- DISCIPLINAS CURSADAS ---\n");

    Disciplina *disciplinaAtual = aluno->disciplinas.inicio;

    if (disciplinaAtual == NULL)
    {
        printf("Nenhuma disciplina cadastrada para este aluno.\n");
        return;
    }

    int contador = 1;
    while (disciplinaAtual != NULL)
    {
        printf("%d. Disciplina: %s\n", contador, disciplinaAtual->nome);
        printf("   Nota: %.2f\n", disciplinaAtual->nota);
        printf("   Presenca: %d%%\n", disciplinaAtual->presenca);
        printf("   Situacao: %s\n", disciplinaAtual->situacao);
        printf("   Periodo: %d\n\n", disciplinaAtual->periodo);

        disciplinaAtual = disciplinaAtual->prox;
        contador++;
    }

    printf("Total de disciplinas: %d\n", contador - 1);
}

// ========================= MANIPULAÇÃO DE ARQUIVOS =======================

// Carrega dados de arquivo no mesmo formato utilizado por salvarDadosEmArquivo
void carregarDadosDeArquivo(NoCabecaAlunos *lista, const char *path)
{
    FILE *arq = fopen(path, "r");
    if (!arq)
    {
        printf("Arquivo nao encontrado!\n");
        return;
    }

    char linha[512];
    Aluno *ultimoAluno = NULL;

    while (fgets(linha, sizeof(linha), arq))
    {
        linha[strcspn(linha, "\n")] = '\0'; // remove \n

        if (strncmp(linha, "ALUNO:", 6) == 0)
        {
            char nome[50];
            int matricula;
            sscanf(linha + 6, "%[^:]:%d", nome, &matricula);
            cadastrarAluno(lista, nome, matricula);
            ultimoAluno = lista->final; // depende de cadastrarAluno atualizar lista->final
        }
        else if (strncmp(linha, "DISCIPLINA:", 11) == 0 && ultimoAluno != NULL)
        {
            char nome[50], situacao[5];
            float nota;
            int presenca, periodo;

            sscanf(linha + 11, "%[^:]:%f:%d:%[^:]:%d",
                   nome, &nota, &presenca, situacao, &periodo);

            inserirDisciplinaDoAluno(&lista->inicio, ultimoAluno->matricula,
                                     nome, nota, presenca, situacao, periodo);
        }
    }

    fclose(arq);
    printf("Dados carregados com sucesso!\n");
}

// TRATANDO INSERÇÃO PRESERVANDO UNICIDADE

// verifica se disciplina existe
int disciplinaExisteNoArquivo(int matricula, const char *nomeDisc, const char *path)
{
    FILE *arq = fopen(path, "r");
    if (!arq)
        return 0;

    char linha[512];
    int alunoAtual = -1;

    while (fgets(linha, sizeof(linha), arq))
    {
        linha[strcspn(linha, "\n")] = '\0';

        if (strncmp(linha, "ALUNO:", 6) == 0)
        {
            char nome[50];
            sscanf(linha + 6, "%[^:]:%d", nome, &alunoAtual);
        }
        else if (strncmp(linha, "DISCIPLINA:", 11) == 0 && alunoAtual == matricula)
        {
            char nomeD[50];
            sscanf(linha + 11, "%[^:]", nomeD);

            if (strcmp(nomeD, nomeDisc) == 0)
            {
                fclose(arq);
                return 1;
            }
        }
    }

    fclose(arq);
    return 0;
}

/* Salvando
void salvarDadosEmArquivo(NoCabecaAlunos *noCabeca, const char *path)
{
    // acessando o arquivo

    FILE *arq = fopen(path, "w"); // abre em modo escrita
    if (!arq)
    {
        printf("Erro ao abrir o arquivo*\n");
        return;
    }

    // acessando os elementos recebidos
    Aluno *aluno = noCabeca->inicio;
    // verificando se há duplicatas

    while (aluno)
    {
        // antes de gravar, verificamos se o dado já existe

        fprintf(arq, "ALUNO:%s:%d\n", aluno->nome, aluno->matricula);
        Disciplina *disciplina = aluno->disciplinas.inicio;
        while (disciplina)
        {
            fprintf(arq, "DISCIPLINA:%s:%.2f:%d:%s:%d\n",
                    disciplina->nome, disciplina->nota, disciplina->presenca,
                    disciplina->situacao, disciplina->periodo);
            disciplina = disciplina->prox;
        }
        aluno = aluno->prox;
    }

    fclose(arq);
    printf("Dados salvos em %s!\n", path);
}
*/
// Salvando refatorado
void salvarDadosUnicosEmArquivo(Aluno *aluno, const char *path)
{
    int alunoExiste = 0;

    FILE *leitura = fopen(path, "r");
    if (leitura)
    {
        char linha[512];

        while (fgets(linha, sizeof(linha), leitura))
        {
            linha[strcspn(linha, "\n")] = '\0';

            if (strncmp(linha, "ALUNO:", 6) == 0)
            {
                int mat;
                char nome[50];
                sscanf(linha + 6, "%[^:]:%d", nome, &mat);

                if (mat == aluno->matricula)
                {
                    alunoExiste = 1;
                    break;
                }
            }
        }
        fclose(leitura);
    }

    FILE *arq = fopen(path, "a");
    if (!arq)
    {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    if (!alunoExiste)
    {
        fprintf(arq, "ALUNO:%s:%d\n", aluno->nome, aluno->matricula);
    }

    Disciplina *disc = aluno->disciplinas.inicio;

    while (disc)
    {
        if (!disciplinaExisteNoArquivo(aluno->matricula, disc->nome, path))
        {
            fprintf(arq, "DISCIPLINA:%s:%.2f:%d:%s:%d\n",
                    disc->nome,
                    disc->nota,
                    disc->presenca,
                    disc->situacao,
                    disc->periodo);
        }

        disc = disc->prox;
    }

    fclose(arq);
}

// inserindo sem duplicidade
void inserindoSemDuplicidade(NoCabecaAlunos *noCabeca, const char *path)
{
    Aluno *aluno = noCabeca->inicio;

    while (aluno)
    {
        salvarDadosUnicosEmArquivo(aluno, path);
        aluno = aluno->prox;
    }

    printf("\nDados sincronizados com sucesso!\n");
}

// ========================= INTERAÇÃO (MENU) =============================

int mostrarMenuPrincipal()
{
    int opcao;
    printf("\n=== SISTEMA DE GERENCIAMENTO DE HISTORICO DE ALUNOS ===\n");
    printf("1. Cadastrar aluno\n");
    printf("2. Cadastrar disciplina para aluno\n");
    printf("3. Remover aluno\n");
    printf("4. Listar todos os alunos\n");
    printf("5. Exibir historico de aluno\n");
    printf("6. Atualizar disciplina de aluno\n");
    printf("7. Salvar dados em arquivo\n");
    printf("8. Carregar dados de arquivo\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao:\n");
    scanf("%d", &opcao);
    return opcao;
}

// ========================= MENUS AUXILIARES =============================

// Mostra o formulário de cadastro de aluno e chama cadastrarAluno
void mostrarMenuCadastroAluno(NoCabecaAlunos *noCabeca)
{
    char nome[256];
    int matricula;

    limparBuffer(); // limpa antes de usar fgets

    printf("Nome do aluno: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    printf("Matricula: ");
    if (scanf("%d", &matricula) != 1)
    {
        printf("Matricula invalida.\n");
        return;
    }

    if (cadastrarAluno(noCabeca, nome, matricula))
    {
        printf("Aluno cadastrado.\n");
        return;
    }

    printf("Falha ao cadastrar aluno.\n");
}
// função utilizada para adquirir os dados necessários para remover o aluno
void mostrarMenuRemoverAluno(NoCabecaAlunos *noCabeca)
{
    int matricula;

    printf("=== REMOVER ALUNO ===\n");
    printf("Insira a matricula do aluno a ser removido: ");
    scanf("%d", &matricula);

    removerAluno(noCabeca, matricula); // chama a função de remover aluno
}

// função utilizada para adquirir os dados necessários para inserir disciplina em x aluno
void mostrarMenuInserirDisciplina(NoCabecaAlunos *noCabeca)
{
    int presenca, periodo;
    float nota;
    char situacao[10];
    char nome[100];
    int matricula;

    printf("Matricula do aluno para cadastrar disciplina: ");
    if (scanf("%d", &matricula) != 1)
    {
        printf("Entrada invalida para matricula.\n");
        limparBuffer();
        return;
    }
    limparBuffer();

    printf("Nome da disciplina: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    printf("Nota da disciplina: ");
    if (scanf("%f", &nota) != 1)
    {
        printf("Entrada invalida para nota.\n");
        limparBuffer();
        return;
    }
    limparBuffer();

    printf("Presenca (%%): ");
    if (scanf("%d", &presenca) != 1)
    {
        printf("Entrada invalida para presenca.\n");
        limparBuffer();
        return;
    }
    limparBuffer();

    printf("Situacao (AP, RP, etc): ");
    fgets(situacao, sizeof(situacao), stdin);
    situacao[strcspn(situacao, "\n")] = '\0';

    printf("Periodo da disciplina: ");
    if (scanf("%d", &periodo) != 1)
    {
        printf("Entrada invalida para periodo.\n");
        return;
    }
    // após adquirir os dados, chama a função de inserir disciplina
    // Note que é passado &nocabeça->inicio porque a função utiliza de ponteiro para ponteiro.
    inserirDisciplinaDoAluno(&noCabeca->inicio, matricula, nome, nota, presenca, situacao, periodo);
}
// função utilizada para adquirir os dados necessários para exibir o histórido de x aluno
void mostrarMenuExibirHistorico(NoCabecaAlunos *noCabeca)
{
    int matricula;
    printf("Insira a matricula do aluno a ser exibido\n");
    scanf("%d", &matricula);
    exibirHistorico(noCabeca, matricula);
    pausarExecucao();
}
// função utilizada para adquirir os dados necessários para atualizar a disciplina de x aluno
void mostrarMenuAtualizarDisciplinaAluno(NoCabecaAlunos *noCabeca)
{
    // buscar aluno
    int matricula;
    printf("Entre com a matricula do aluno que vai ter a disciplina alterada: ");
    scanf("%d", &matricula);
    // obtemos o nó aqui, logo, partiremos para a sublista daqui, deste aluno
    Aluno *alunoCampoDisciplina = buscarAluno(noCabeca, matricula);
    if (alunoCampoDisciplina == NULL)
        return;
    limparBuffer();
    // logica de implementação do removerDisciplina

    // encontrar discplina
    char disciplinaParaAlterar[256];
    fflush(stdin);
    printf("Busque pelo nome inserido a disciplina a ser alterada: ");
    fgets(disciplinaParaAlterar, sizeof(disciplinaParaAlterar), stdin);
    disciplinaParaAlterar[strcspn(disciplinaParaAlterar, "\n")] = '\0';
    // a cabeça da sublista vai ser o aluno encontrado apontando para a disciplina de início dessa sublista, disciplinas.inicio
    // armazena a head incialmente
    Disciplina *disciplinaAlterar = alunoCampoDisciplina->disciplinas.inicio;

    // obtendo os dados para sobreescrever
    int presenca, periodo;
    float nota;
    char situacao[10];
    char nome[100];

    printf("Novo nome da disciplina: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    printf("Nova nota da disciplina: ");
    if (scanf("%f", &nota) != 1)
    {
        printf("Entrada invalida para nota.\n");
        limparBuffer();
        return;
    }

    printf("Nova presenca (%%): ");
    if (scanf("%d", &presenca) != 1)
    {
        printf("Entrada invalida para presenca.\n");
        limparBuffer();
        return;
    }
    limparBuffer();

    printf("Situacao (AP, RP, etc): ");
    fgets(situacao, sizeof(situacao), stdin);
    situacao[strcspn(situacao, "\n")] = '\0';

    printf("Novo periodo da disciplina: ");
    if (scanf("%d", &periodo) != 1)
    {
        printf("Entrada invalida para periodo.\n");
        limparBuffer();
        return;
    }

    atualizarDisciplinaDoAluno(disciplinaAlterar, disciplinaParaAlterar, nome, nota, presenca, situacao, periodo);
    return;
}
// função utilizada para mostrar o menu e direcionar cada opção para sua respectiva função
void mapearMenu(NoCabecaAlunos *noCabecaAlunos)
{
    int opcao;

    do
    {
        opcao = mostrarMenuPrincipal();
        switch (opcao)
        {

        case 1:
            mostrarMenuCadastroAluno(noCabecaAlunos);
            pausarExecucao();
            break;

        case 2:
            mostrarMenuInserirDisciplina(noCabecaAlunos);
            pausarExecucao();
            break;

        case 3:
            mostrarMenuRemoverAluno(noCabecaAlunos);
            pausarExecucao();
            break;

        case 4:
            listarAlunos(noCabecaAlunos);
            pausarExecucao();
            break;

        case 5:
            mostrarMenuExibirHistorico(noCabecaAlunos);
            break;

        case 6:
            mostrarMenuAtualizarDisciplinaAluno(noCabecaAlunos);
            pausarExecucao();
            break;

        case 7:
            inserindoSemDuplicidade(noCabecaAlunos, "dados.txt");
            break;

        case 8:
            carregarDadosDeArquivo(noCabecaAlunos, "dados.txt");
            break;

        case 0:
            printf("\nEncerrando programa.\n");
            break;

        default:
            printf("\nOpcao invalida!\n");
            pausarExecucao();
            break;
        }
        /* fim loop */

        printf("\n\n\n\n");
    } while (opcao != 0);
}
// main
int main()
{
    NoCabecaAlunos noCabecaAlunos;
    alocarNoCabeca(&noCabecaAlunos);

    mapearMenu(&noCabecaAlunos);
    getchar();
    return 1;
}
