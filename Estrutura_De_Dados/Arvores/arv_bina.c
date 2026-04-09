#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No *esq, *dir;
} No;

No* novoNo(int valor) {
    No* no = (No*) malloc(sizeof(No));
    no->valor = valor;
    no->esq = NULL;
    no->dir = NULL;
    return no;
}

// Inserção por nível (árvore completa)
void inserir(No **raiz, int valor) {
    if (*raiz == NULL) {
        *raiz = novoNo(valor);
        return;
    }

    No* fila[1000];
    int ini = 0, fim = 0;

    fila[fim++] = *raiz;

    while (ini < fim) {
        No* atual = fila[ini++];

        if (atual->esq == NULL) {
            atual->esq = novoNo(valor);
            return;
        } else {
            fila[fim++] = atual->esq;
        }

        if (atual->dir == NULL) {
            atual->dir = novoNo(valor);
            return;
        } else {
            fila[fim++] = atual->dir;
        }
    }
}

int buscar(No* raiz, int valor) {
    if (raiz == NULL) return 0;
    if (raiz->valor == valor) return 1;
    return buscar(raiz->esq, valor) || buscar(raiz->dir, valor);
}

// Percurso em ordem
void emOrdem(No* raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esq);
        printf("%d ", raiz->valor);
        emOrdem(raiz->dir);
    }
}

// Liberação da memória
void liberar(No* raiz) {
    if (raiz != NULL) {
        liberar(raiz->esq);
        liberar(raiz->dir);
        free(raiz);
    }
}

int main() {
    No* raiz = NULL;

    inserir(&raiz, 10);
    inserir(&raiz, 5);
    inserir(&raiz, 15);
    inserir(&raiz, 3);
    inserir(&raiz, 7);

    printf("Em ordem: ");
    emOrdem(raiz);
    printf("\n");

    printf("Buscar 7: %d\n", buscar(raiz, 7));
    printf("Buscar 20: %d\n", buscar(raiz, 20));

    liberar(raiz);
    return 0;
}
