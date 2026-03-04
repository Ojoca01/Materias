// arquivo para o estudo efetivo da construção das listas encadeadas em C , pela disciplina de Estrutura de dados
//Tipo de dado que representa um nó da lista encadeada

typedef struct no{
    int dado;
    struct no *proxNo;
}tipoNo;

//Em C, structs podem se autorreferenciar apenas usando o nome da struct, não o nome definido pelo typedef (porque ele ainda não existe naquele ponto da definição).
