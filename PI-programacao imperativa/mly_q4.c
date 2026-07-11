#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main (){


    int n;
    float *vetor,soma=0;

    printf("\n\nDigie o tamanho do vetor: \n");
    scanf("%d",&n);

    if (n<=0 || vetor==NULL)
    {
    printf("entrada recusada!");        
    return  1;

}
    else{

        vetor =(float*) calloc(n,sizeof(float));

        printf("\nDigite os numeros do vetor alocado\n");
        for (int i = 0; i < n; i++)
        {
           printf("vetor[%d]\n",i+1);
           scanf("%f",&vetor[i]);
        };
    }
    // exibição 
        for (int f = 0; f < n; f++)
        {
            printf(" elemento(%d) :  %.2f \n",f,vetor[f]);
            
            soma+=vetor[f];
            
        }
    // média
    float media=soma/n ; 
        printf("Media : %.2f\n",media);
    // multipos de 6
    printf("Multiplos de 6: \n");
    for(int k=0;k<n;k++){
        if ((int) vetor[k] % 6== 0 ){
        printf("%2.f\n",vetor[k]);
        }


    }
    free(vetor);
    return 0;

};