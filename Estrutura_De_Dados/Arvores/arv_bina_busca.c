#include <stdio.h>
#include <stdlib.h>

typedef struct NoBST {
    int valor;
    struct NoBST *esq, *dir;
} NoBST;

NoBST* novoNoBST(int valor) {
    NoBST* no = (NoBST*) malloc(sizeof(NoBST));
    no->valor = valor;
    no->esq = NULL;
    no->dir = NULL;
    return no;
}

// Inserção
NoBST* inserir(NoBST* raiz, int valor) {
    if (raiz == NULL) return novoNoBST(valor);

    if (valor < raiz->valor)
        raiz->esq = inserir(raiz->esq, valor);
    else if (valor > raiz->valor)
        raiz->dir = inserir(raiz->dir, valor);

    return raiz;
}

// Busca
int buscar(NoBST* raiz, int valor) {
    if (raiz == NULL) return 0;
    if (raiz->valor == valor) return 1;

    return valor < raiz->valor ? buscar(raiz->esq, valor)
                               : buscar(raiz->dir, valor);
}

// Encontrar menor valor da subárvore
int menorValor(NoBST* raiz) {
    while (raiz->esq != NULL)
        raiz = raiz->esq;
    return raiz->valor;
}

// Remoção
NoBST* remover(NoBST* raiz, int valor) {
    if (raiz == NULL) return NULL;

    if (valor < raiz->valor)
        raiz->esq = remover(raiz->esq, valor);
    else if (valor > raiz->valor)
        raiz->dir = remover(raiz->dir, valor);
    else {
        if (raiz->esq == NULL) {
            NoBST* temp = raiz->dir;
            free(raiz);
            return temp;
        }
        else if (raiz->dir == NULL) {
            NoBST* temp = raiz->esq;
            free(raiz);
            return temp;
        }

        raiz->valor = menorValor(raiz->dir);
        raiz->dir = remover(raiz->dir, raiz->valor);
    }
    return raiz;
}

// Em ordem
void emOrdem(NoBST* raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esq);
        printf("%d ", raiz->valor);
        emOrdem(raiz->dir);
    }
}

void liberar(NoBST* raiz) {
    if (raiz != NULL) {
        liberar(raiz->esq);
        liberar(raiz->dir);
        free(raiz);
    }
}

int main() {
    NoBST* raiz = NULL;

    int valores[] = {50, 30, 70, 20, 40, 60, 80};
    for (int i = 0; i < 7; i++)
        raiz = inserir(raiz, valores[i]);

    printf("Em ordem: ");
    emOrdem(raiz);
    printf("\n");

    printf("Buscar 40: %d\n", buscar(raiz, 40));

    raiz = remover(raiz, 50);

    printf("Após remover 50: ");
    emOrdem(raiz);
    printf("\n");

    liberar(raiz);
    return 0;
}
