/*
 aluno: João Carlos Cruz Santos
 matricula:202400100501

LISTA de EXERCICIO

1) Entrar com valores inteiros para uma matriz A[4 x 4] e para uma matriz B[4x 4]. Gerar e
imprimir a matriz SOMA[4 x .4].

5) Ler valores inteiros para a matriz A[3 x 5] . Gerar e imprimir o vetor SOMA_LINHA, onde cada
elemento é a soma dos elementos de uma linha da matriz A. Faça o trecho que gera o vetor separado
da entrada e da saída.
6) Ler valores inteiros para a matriz A[3 x 5]. Gerar e imprimir o vetor SOMA_COLUNA, onde
cada elemento é a soma dos elementos de uma coluna da matriz A. Faça o trecho que gera o vetor
separado da entrada e da saída.
8)Entrar com valores para uma matriz A3 x 4. Gerar e imprimir uma matriz B que é o triplo da matriz
A.
9)Entrar com valores para uma matriz C2 x 3. Gerar e imprimir a Ct
.
20)Faça um algoritmo que leia os elementos de uma matriz 5 x 5 e imprima a soma dos elementos
que estão abaixo da diagonal secundária.*/

#include <stdio.h>
#include <string.h>
#include <math.h>

// Questão 1 - Soma de Matrizes 4x4
void somaMatrizes() {
    int mat1[4][4], mat2[4][4], soma[4][4];
    printf("digite a sua primeira matriz 4x4:\n");
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            scanf("%d", &mat1[x][y]);
        }
    }
    printf("agora a segunda matriz 4x4:\n");
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            scanf("%d", &mat2[x][y]);
            soma[x][y] = mat1[x][y] + mat2[x][y];
        }
    }
    printf("Soma das matrizes 1 e 2:\n");
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            printf("%8d", soma[x][y]);
        }
        printf("\n");
    }
}

// Questão 5 - Soma das Linhas
void somaLinhas() {
    int mat[3][5], somaLinha[3] = {0};
    printf("Matriz:\n");
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 5; y++) {
            scanf("%d", &mat[x][y]);
            somaLinha[x] += mat[x][y];
        }
    }
    printf("Vetor Soma Linha:\n");
    for (int x = 0; x < 3; x++) {
        printf("%d\n", somaLinha[x]);
    }
}

// Questão 6 - Soma das Colunas
void somaColunas() {
    int mat[3][5], somaColuna[5] = {0};
    printf("digite os elementos da sua matriz:\n");
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 5; y++) {
            scanf("%d", &mat[x][y]);
            somaColuna[y] += mat[x][y];
        }
    }
    printf("Vetor Soma Coluna:\n");
    for (int y = 0; y < 5; y++) {
        printf("%d ", somaColuna[y]);
    }
    printf("\n");
}

// Questão 8 - Triplo da Matriz
void triploMatriz() {
    int mat[3][4];
    printf("digite os elementos da sua matriz:\n");
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 4; y++) {
            scanf("%d", &mat[x][y]);
        }
    }
    printf("o Triplo da matriz eh:\n");
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 4; y++) {
            printf("%8d", mat[x][y] * 3);
        }
        printf("\n");
    }
}

// Questão 9 - Matriz Transpoosta 2x3
void transposta() {
    int mat[2][3], trans[3][2];
    printf("digite os elementos da sua matriz 2x3:\n");
    for (int x = 0; x < 2; x++) {
        for (int y = 0; y < 3; y++) {
            scanf("%d", &mat[x][y]);
            trans[y][x] = mat[x][y];
        }
    }
    printf("a matriz Transposta eh:\n");
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 2; y++) {
            printf("%8d", trans[x][y]);
        }
        printf("\n");
    }
}

// Questão 20 - Soma abaixo da diagonal secundária
void somaDiagonalSecundaria() {
    int mat[5][5], soma = 0;
    printf("digite os elementos da sua Matriz 5x5:\n");
    for (int x = 0; x < 5; x++) {
        for (int y = 0; y < 5; y++) {
            scanf("%d", &mat[x][y]);
            if (x + y > 4) soma += mat[x][y];
        }
    }
    printf("Soma abaixo da diagonal secundária eh: %d\n", soma);
}


