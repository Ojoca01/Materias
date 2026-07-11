#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct{
    int idade;
    float peso;
    char nome[50];

}Atletas;

int main(){
    char entrada;
    int contador=0,soma_peso=0;
    Atletas atletas[50];

    //entrada de dados
    printf("\n\nPara introduzir os dados dos atletas, por favor\n");
    printf("==Digite respectivamente == \n");

    for(int i=0;i<50;i++){

    printf("\nAtleta %d\n", i + 1);

    printf("\nNome : ");
    scanf(" %[^\n]", atletas[i].nome); //  entrada com vetor de strings em c  ->    scanf(" %[^\n]", atletas[i].nome);
    getchar();
    printf("\nIdade :");
    scanf("%d",&atletas[i].idade);
    getchar();
    printf("\nPeso : ");
    scanf("%f",&atletas[i].peso);
    getchar();

    printf("\nDeseja sair? digite 'S'.\nDeseja continuar? digite qualquer outra tecla. ");
    scanf("%c",&entrada);
    

    contador++;

    if(entrada == 'S'){
        printf("\nEncerrando entrada de dados\n....");
        break;
    }
   
    

}
    // impressão da lista 

    for(int o=0;o<contador;o++){
        printf("Atleta (%d)\n",o+1);
        printf("Nome: %s\n", atletas[o].nome);
        printf("Idade: %d\n", atletas[o].idade);
        printf("Peso: %.2f\n", atletas[o].peso);
        printf("\n");
        soma_peso+=atletas[o].peso;


    }

    // media

    float medias_peso= soma_peso / contador;

    printf("Media dos pesos: %.2f\n",medias_peso);
    printf("\n");

    // verificação dos atletas menores de idade
    printf("Menores de idade:\n");
    printf("\n");

    for (int a = 0; a < contador; a++)
    {
        if (atletas[a].idade < 18)
        {
            printf("Atleta %s:%d anos\n",atletas[a].nome,atletas[a].idade);
        }
            
    }
    
    getchar();
    free(atletas);
    return 0;


}