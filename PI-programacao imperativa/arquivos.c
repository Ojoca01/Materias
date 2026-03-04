#include<stdio.h>
#include<stdlib.h>
#include<locale.h>



//Exemplo de leitura de arquivo binário

int main(void)
{
  int valor [10];

  //ponteiro para o arquivo
  FILE *ptrArq;

  //abertura do arquivo
  ptrArq = fopen("binario.bin","rb");

  //testando se o arquivo foi aberto com sucesso
    if (ptrArq != NULL)
     printf ("\n\nArquivo binario.bin foi aberto com sucesso\n\n");
  else
  {
    printf ("\n\nERRO: O arquivo binario.bin não foi aberto e criado\n");
    system ("pause");
    exit (1);
  }

  //retorna o conteúdo contido em uma ocorrência do tamanho da variável valor.
  fread(valor,sizeof(valor),1,ptrArq);


  printf("\nVetor de inteiros lido: ");

  for(int i = 0; i < 10; i++)
  {
    printf("\n%d",valor[i]);
  }

  //fechando o arquivo
  fclose(ptrArq);

  printf("\n");
  system("pause");
  return(0);
}

//Exemplo de escrita de arquivo binário
/*
int main(void)

{
setlocale(LC_ALL,"Portuguese");
  int valor [10];
  FILE *ptarq;

  for(int x=0; x<10; x++){
    printf("\nDigite um número: ");
    scanf("%d",&valor[x]);
  }

  ptarq = fopen ("binario.bin", "wb"); //Se não abriu, cria.

  if (ptarq!=NULL)
   printf ("n\nArquivo binario.bin foi aberto com sucesso\n");
  else
  {
   printf ("\n\nErro: O arquivo binario.bin não foi aberto\n");
   system ("pause");
   exit (0);
  }

  //Gravando os dados no arquivo usando a função fwrite
  fwrite (valor, sizeof(valor), 1, ptarq);

  //Fechando o arquivo
  fclose (ptarq);

  system ("pause");//pausa na tela, só funciona para Windows
  return(0);*/

