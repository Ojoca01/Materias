#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
/* 

======== ponteiros ========
é uma variável que armazena o endereço de memória de outro valor,
permitindo manipulação direta da memória do computador

PONTO PRINCIPAL- desreferenciação de ponteiros '*'

| Símbolo  | Significado                     | Exemplo     |
| -------- | ------------------------------- | ----------- |
| `linha`  | endereço guardado no ponteiro   | `0x7ffe...` |
| `*linha` | valor armazenado nesse endereço | `10`        |
obs:. desreferenciação e variável '*'
obs:. endereço de memoria 
Um endereço de memória é um número que indica uma posição específica na memória
do computador onde um dado está armazenado.
 Fisicamente-
O processador coloca o endereço da célula que quer acessar nos barramentos de endereço.
A memória seleciona a célula correspondente.
O valor armazenado na célula é lido ou escrito via barramento de dados.
É como enviar uma carta para um endereço: o endereço não é a carta em si,
é apenas o “número da caixa” onde a carta está guardada.

======== strucs ========
Estruturas de Dados Heterogêneas;
As structs são usadas para agrupar variáveis de diferentes tipos sob um mesmo 
nome — como se fosse um “registro” ou “objeto”.



======== alocação dinamica ========

é um processo onde a memória é reservada para variáveis durante a execução de um programa,
e não na compilação, permitindo que o tamanho de estruturas de dados seja determinado em tempo real e 
que a memória seja ajustada conforme a necessidade, basicamente uma aritimetica de pronteiros
que pré programada para entender o tamanho da variável que vai ter que guardar apenas no 
momento que a estiver guardando.

| Função      | Descrição                                                     |
| ----------- | ------------------------------------------------------------- |
| `malloc()`  | Aloca um bloco de memória e retorna um ponteiro para o início |
| `calloc()`  | Aloca memória inicializada com zeros                          |
| `realloc()` | Redimensiona um bloco de memória previamente alocado          |
| `free()`    | Libera a memória alocada dinamicamente                        |

Em geral tanto malloc quanto calloc fazem a mesma coisa mas o calloc é mt mais incisivo ,visto que não permite 
a entrada do lixo de memória.
Obs;. sempre preferir o calloc.

======== alocação dinamica ========
reestruturação com realloc;

======== alocação com vetores ========


======== Entrada de dados com alocação dinamica  ========

======== Saída de dados com alocação dinamica  ========

======== Operações Lógicas de dados com alocação dinamica  ========

======== atribuições funcionais de dados com alocação dinamica  ========

======== Operações Aritiméticas de dados com alocação dinamica  ========


*/