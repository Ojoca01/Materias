#include<stdio.h>
#include<stdlib.h>
#include<locale.h>

//Exemplo de escrita de arquivo texto.

int main(){
FILE *arq;
char palavra[30];
arq = fopen("arquivo.txt","a");
if (arq == NULL)
  {
    printf("Erro ao tentar abrir o arquivo!");
    exit(1);
  }

printf("Digite a frase a ser gravada no arquivo:");
gets(palavra);
fflush(stdin);
while(strcmp(palavra,"***") != 0){
    fprintf(arq, "\n%s",palavra);
    printf("Digite a frase a ser gravada no arquivo <para sair digite ***>:");
    gets(palavra);
    fflush(stdin);
}
fclose(arq);
}

//Exemplo de programa que lê arquivo texto usando fgets
//Observem que a leitura encerra quando a frase lida for == NULL

int main(){
FILE *arq;
char c, palavra[30];
int vogais;
arq = fopen("arquivo.txt","r");
if(arq==NULL){
    printf("Arquivo nao pode ser aberto");
    exit(1);
}
printf("\nConteudo do arquivo:\n");

//Fazendo a leitura com fgets

while(fgets(palavra, 30, arq) != NULL)
  printf("%s", palavra);

fclose(arq);
}
/*
• 1. Escreva um programa que crie/abra um arquivo texto de nome
“arquivo.txt”
• Vá gravando diversos strings digitados pelo usuário no arquivo;
• A gravação deve encerrar ao ser digitado ***, como valor do string.

• 2. Escreva um programa que abra o arquivo anteriormente criado, leia
as strings guardadas nele e as exiba na tela.
• 3. Faça um programa que leia o arquivo anteriormente criado, mostre
o conteúdo do arquivo na tela e informe quantas vogais há no texto
lido.

• 1) Crie um programa que leia um vetor de 10 inteiros. Abra um
arquivo e armazene o conteúdo do vetor. (obs: lembre de fechar o
arquivo ao final).
• 2) Crie outro programa que abra o arquivo criado anteriormente, faça
a leitura do vetor de inteiros e exiba seu conteúdo.*/
