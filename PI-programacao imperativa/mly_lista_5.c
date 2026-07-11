#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
struct Pessoa1 {
    char nome[50];
    int idade;
    float altura;
};

int main1() {
    struct Pessoa1 p1 = {"João", 25, 1.80};

    printf("Nome: %s\n", p1.nome);
    printf("Idade: %d\n", p1.idade);
    printf("Altura: %.2f\n", p1.altura);

    return 0;
}
// opção com typedef
/*
O typedef serve para criar um nome abreviado (apelido) para o tipo struct.

Sem typedef, você precisa escrever struct Pessoa toda vez.
Com typedef, você pode usar só Pessoa.?*/


typedef struct {
    char nome[50];
    int idade;
    float altura;
} Pessoa;

int main2() {
    Pessoa p1;

    strcpy(p1.nome, "Maria");
    p1.idade = 25;
    p1.altura = 1.68;

    printf("Nome: %s\nIdade: %d\nAltura: %.2f\n", p1.nome, p1.idade, p1.altura);

    return 0;
}
