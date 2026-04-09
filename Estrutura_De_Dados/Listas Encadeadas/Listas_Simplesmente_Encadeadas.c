 /* Tarefa : Enviar código disponibilizado com o acréscimo das implementações de: remoção do inicio,
 remoção do fim, destruição da lista e pesquisa de informação na lista.*/

/* ======== 
CODIGO DISPONIBILIZADO ok 
ADIÇÕES ok
Correção de erros ok
Otimização  ok
menu novo da versao final ok
comentar ok */

#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int dado;
    struct no *proxNo;
}tipoNo;

/*Tipo de dado que representa uma lista encadeada*/
typedef struct listaGerenciada{
    tipoNo *inicio;
    tipoNo *fim;
    int quant;
}tipoLista;

/*Função de inicialização da lista encadeada - Deve ser chamada antes de usar a lista*/
void inicializa(tipoLista *lista){
    lista->fim = NULL;
    lista->inicio = NULL;
    lista->quant = 0;
}
 
/*Função para inserção de nó em lista vazia*/
int insereListaVazia(tipoLista *listaEnc, int valor){
    tipoNo *novoNo = (tipoNo*) malloc(sizeof(tipoNo));
    if(novoNo == NULL)
        return 0;
    novoNo->dado = valor;
    novoNo->proxNo = NULL;
    listaEnc->inicio = novoNo;
    listaEnc->fim = novoNo;
    listaEnc->quant++;
    return 1;
}

/*Função que faz a inserção de um nó na frente de uma lista simplesmente encadeada*/
int insereNaFrente(tipoLista *listaEnc, int valor){
    tipoNo *novoNo;
    if(listaEnc->inicio==NULL)
        return insereListaVazia(listaEnc, valor);
    else{
        novoNo = (tipoNo*)malloc(sizeof(tipoNo));
        if(novoNo==NULL)
            return 0;
        novoNo->dado=valor;
        novoNo->proxNo=listaEnc->inicio;
        listaEnc->inicio=novoNo;
        listaEnc->quant++;
        return 1;
    }
}

// função que adiciona um elemento no fim da lista
int insereNoFim(tipoLista *listaEnc, int valor){
    tipoNo *novoNo;
    if(listaEnc->inicio == NULL)
        return insereListaVazia(listaEnc, valor);
    else{
        novoNo = (tipoNo*) malloc(sizeof(tipoNo));
        if(novoNo == NULL)
            return 0;
        novoNo->dado=valor;
        novoNo->proxNo=NULL;
        listaEnc->fim->proxNo = novoNo;
        listaEnc->fim = novoNo;
        listaEnc->quant++;
        return 1;
    }
}

/*Função de exibição da lista simplesmente encadeada*/
int exibeLista(tipoLista *listaEnc){
    tipoNo *atual;  //Variável que será usada para percorrer a lista
    if(listaEnc->inicio == NULL)
        return 0;
    atual = listaEnc->inicio;
    printf("\nLista encadeada: ");
    while(atual !=NULL){
        printf("%8d",atual->dado);
        atual = atual->proxNo;
    }
    return 1;
}

/* ======== NOVAS FUNÇÕES IMPLEMENTADAS ======== */

// Remove o primeiro elemento da lista
int removedoinicio(tipoLista *lista, int aux){
    tipoNo *temp;
    if(lista->inicio == NULL){
        printf("\nLista vazia, nada a remover.\n");
        return 0;
    }

    temp = lista->inicio;              // guarda o nó a ser removido
    aux = temp->dado;                  // valor removido (pode ser exibido, se quiser)
    lista->inicio = temp->proxNo;      // move o início para o próximo nó
    free(temp);                        // libera memória
    lista->quant--;

    if(lista->inicio == NULL)          // se a lista ficou vazia, ajusta o fim
        lista->fim = NULL;

    printf("\nElemento removido do início com sucesso!\n");
    return 1;
}

// Remove o último elemento da lista
int removedofinal(tipoLista *lista, int aux){
    tipoNo *atual, *anterior;

    if(lista->inicio == NULL){
        printf("\nLista vazia, nada a remover.\n");
        return 0;
    }

    // Se houver apenas um nó
    if(lista->inicio == lista->fim){
        aux = lista->inicio->dado;
        free(lista->inicio);
        lista->inicio = NULL;
        lista->fim = NULL;
        lista->quant = 0;
        printf("\nElemento removido do fim com sucesso!\n");
        return 1;
    }

    // Percorre até o penúltimo nó
    anterior = NULL;
    atual = lista->inicio;
    while(atual->proxNo != NULL){
        anterior = atual;
        atual = atual->proxNo;
    }

    aux = atual->dado;
    anterior->proxNo = NULL;
    lista->fim = anterior;
    free(atual);
    lista->quant--;
    printf("\nElemento removido do fim com sucesso!\n");
    return 1;
}

// Busca um elemento na lista
int BuscaEncadeada(tipoLista *lista, int aux){
    tipoNo *atual;
    if(lista->inicio == NULL){
        printf("\nLista vazia, não há elementos para buscar.\n");
        return 0;
    }

    atual = lista->inicio; 

    while(atual != NULL){
        if(atual->dado == aux){
            printf("\nElemento %d encontrado na lista!\n", aux);
            return 1;
        }
        atual = atual->proxNo;
    }

    printf("\nElemento %d não encontrado na lista.\n", aux);
    return 0;
}

// Função para liberar toda a memória usada pela lista
int destruirLista(tipoLista *lista){
    tipoNo *atual = lista->inicio;
    tipoNo *prox;

    while(atual != NULL){
        prox = atual->proxNo;
        free(atual);
        atual = prox;
    }

    lista->inicio = NULL;
    lista->fim = NULL;
    lista->quant = 0;

    printf("\nLista destruída e memória liberada!\n");
    return 1;
}

int main(){
    tipoLista lista;
    int opcao, aux;
    inicializa(&lista);
    do{
        printf("\n\n      Menu Lista Encadeada");
        printf("\n1 - Insere um elemento na lista vazia");
        printf("\n2 - Insere elemento no inicio da lista");
        printf("\n3 - Insere elemento no fim da lista");
        printf("\n4 - remove elemento no inicio da lista");
        printf("\n5 - remove elemento no fim da lista");
        printf("\n6 - busca elemento na lista ");
        printf("\n9 - Exibe a lista");
        printf("\n0 - Encerra o programa");
        printf("\n\nDigite sua opcao:");
        scanf("%d",&opcao);
        switch(opcao){
        case 1:printf("\nDigite o elemento que deseja inserir:");
            scanf("%d",&aux);
            insereListaVazia(&lista,aux);
            break;
        case 2:printf("\nDigite o elemento que deseja inserir:");
            scanf("%d",&aux);
            insereNaFrente(&lista,aux);
            break;
        case 3 : printf("\nDigite o elemento que deseja inserir: ");
            scanf("%d",&aux);
            if(insereNoFim(&lista,aux))
                printf("\nElemento inserido com sucesso");
            break;
        case 4 :
            if(removedoinicio(&lista,aux))
                printf("\nRemoção concluída com sucesso!");
            break;
        case 5 :
            if(removedofinal(&lista,aux))
                printf("\nRemoção concluída com sucesso!");
            break;
        case 6 : printf("\nDigite o elemento que deseja buscar: ");
            scanf("%d",&aux);
            BuscaEncadeada(&lista,aux);
            break;
        case 9: if(!exibeLista(&lista))
                    printf("\nLista vazia!\n");
            break;
        case 0: printf("\nEncerrando programa.");
                destruirLista(&lista);
            break;
        default: printf("\nOpcao invalida!");
        }
     printf("\n\n\n\n");
    }while(opcao != 0);

    getchar();
    return 1;
}
