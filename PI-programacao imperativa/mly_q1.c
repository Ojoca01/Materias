#include <stdio.h>

int main () {

    // verificação de admissão e entrada 

    int l,c,matriz[10][10];

    printf("Digite o tamanho da matriz");
    printf("\n");
    printf("DE (linhas):");
    scanf("%d",&l);
    printf("\n");
    printf("POR (colunas):");
    scanf("%d",&c);
     
     if ( l<=10  &&   c<=10 && l==c)
    {
       for (int i = 0; i < l; i++)
     {
        for (int j = 0; j < c; j++){
            printf("Matriz [%d][%d]",l,c);
            printf("Digite o elemento [%d][%d]",i,j);
            scanf("%d",&matriz[i][j]);

        }
     }
      // verifica se a diagonal principal é nula

     for (int j = 0; j < c; j++)
     {
        for (int i = 0; i < l; i++){
            
            if (i==j && matriz[i][j]== 0) {
                printf("\n");
                printf("Esta matriz tem a diagonal nula !");
            }
        

        }
     }
  
    // exibição
      for (int i = 0; i < l; i++)
     {
        for (int j = 0; j < c; j++){
            printf("\n");
            printf("Matriz [%d][%d]",i,l);
            printf("\n");

        }
     }

    }

    // senao recusa
     else {
        printf("Erro: não obedece as codições de admissão da matriz!");
        printf("Condições:ser quadrada e ter tamanho menor/igual a 10");

    }

   

}