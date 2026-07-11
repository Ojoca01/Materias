    #include <stdio.h>

    int fat(long long int a ){
        
    
    if (a==0 || a==1)
    {
       return 1;
    }
    else
    {
      return a * fat( a-1);  
    }
    
    
}


int main (){
    int num;
    
    printf("\n");
    printf("\n");
    // entrada e verificação dos dados
  
    printf("Digite um numero inteiro positivo: ");
    scanf("%d",&num);
    printf("\n");

    if (num<0 )
    {
        printf("Erro: nao obedece as condições de entrada!");
    }
    else
    {
        
    printf("\n");
    // divisores
    printf("Divisores:");
    printf("\n");
    for (int i = 1; i <= num; i++)
    {
        if (num %  i == 0){
            printf("%d  ",i );
           
        }
    }

    printf("\n");
    //fatorial
    printf("Fatorial de %d: %d\n", num, fat(num));
    
    printf("\n");
    printf("\n");
    //sempre lembrar de retornar zero
    return 0;
        }





}