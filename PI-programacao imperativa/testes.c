
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





