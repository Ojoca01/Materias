
#include<stdio.h>
#include<string.h>
#include <locale.h>
#include <stdlib.h>

/*Para fixar o aprendizado:
• Implemente um programa em C que tenha:
• Uma função chamada dobro que receba um valor e guarde seu dobro em
uma variável local que será exibida na função;
• Uma função chamada contar que registre e exiba quantas vezes ela já foi
chamada no programa;
• Uma variável global que conte quantas chamadas a quaisquer funções foram
feitas;
• Teste as funções implementadas no main( ).*/

int global= 0;
int dobro(int local){
      global++;
      int dobre= local*2;
      printf("dobro:\n %d",dobre);
}

void contar(){
 static local=0;
 local++;
 global++;
 printf( "esta função local foi chamada:%d\n",local);
}

void main (){
setlocale(LC_ALL,"Portuguese");
 dobro(2);
 dobro(8);

 dobro(0);
 contar();
 contar();
 contar();
 printf("esta função global foi chamada:%d \n",global);
return 0 ;
};







