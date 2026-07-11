#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{

    char nome[50];
    int matricula,idade;
    float media;

}Alunos;

// ====== EXIBIÇÃO DA STRUCT ======
/* Observe que o primeiro vetor é passado sem o tamanho entre os colchetes*/

void Exibir_struct(Alunos vetor[], int tam){
for(int x=0; x<tam; x++){
    printf("Nome: %s, Matricula: %d, Media: %5.2f, Idade: %d \n",vetor[x].nome, vetor[x].matricula, vetor[x].media,vetor[x].idade);
}
}

// ====== ORDENANDO ALFABETICAMENTE ======
/* Observe que nessa chamada, apenas para exemplificar o que foi dito em sala, estou usando notação de ponteiro*/

void ordenação_alfabetica(Alunos *vetor, int tam){
Alunos aux;
for(int x=0; x<tam-1; x++)
    for(int y=x+1; y<tam; y++)
        if(strcmp(vetor[x].nome,vetor[y].nome)>0){
            aux = vetor[x];
            vetor[x] = vetor[y];
            vetor[y] = aux;
        }
printf("\nLista em ordem alfabetica:\n");
Exibir_struct(vetor, tam);
}

// ====== ORDENANDO POR NOTA ======

void ordenação_por_nota(Alunos vetor[], int tam){
Alunos aux;
for(int x=0; x<tam-1; x++)
    for(int y=x+1; y<tam; y++)
        if(vetor[x].media < vetor[y].media){
            aux = vetor[x];
            vetor[x] = vetor[y];
            vetor[y] = aux;
        }
printf("\nLista em ordem por nota:\n");

Exibir_struct(vetor, tam);


}

int main(){
    int tam=0,swi;
    char entrada;
    float soma=0;
    Alunos *alunos=(Alunos*)malloc((tam+1) * sizeof(Alunos));

    do
    {

    if (!alunos){
    printf("Erro ! memoria nao alocada\n");
    return 1;}
    
    // entrada padrão com getchar para tirar o espaço das variaveis numericas

        
        printf("\n\nAluno [%d]:\n",tam+1);
        printf("Digite o nome:\n");
        scanf("%s",&alunos[tam].nome);
        printf("Digite a matricula:\n");
        scanf("%d",&alunos[tam].matricula);
        printf("Digite a idade:\n");
        scanf("%d",&alunos[tam].idade); 
        printf("Digite a media:\n");
        scanf("%f",&alunos[tam].media);
    // condição de parada 
        printf("Digite 'p' parar:\n");
        scanf("%c",&entrada);
        getchar();

        int aux=tam;
        tam++;
    //verificação de indice para reset do loop com o contador 'tam' sempre 1 maior que o anterior 
        
        if (tam > aux ){
        alunos = realloc(alunos, (tam) * sizeof(Alunos));
        }


    } while (entrada != 'p');

    //media 
        for (int i = 0; i < tam; i++){
            soma += alunos[i].media;
            }
        
        float media = soma/ tam ; 

        if((tam-1)<=0){
             media= alunos[0].media;
        }
        printf("\n==== Media de todos os %d alunos ====\n ",tam);
        printf("%.2f",media);

// escolhas / menu
 
 do
 {

printf("\n\n======MENU====== \n0->para Sair.\n\n1->para ordem alfabetica \n2->para ordem de nota (decrescente) \n");
scanf("%d",&swi);
getchar();
switch (swi)
{

// ========= ordem alfabetica
   
case 1 :
    ordenação_alfabetica(alunos, tam);

    break;

    // ========= ordem por nota 

case 2:
    ordenação_por_nota(alunos,tam);
    break;


default:
if(swi!=0){printf("Erro: falha na escolha");}
    break;
}

 }
 
 while (swi != 0);

    free(alunos);
    return 0;
}