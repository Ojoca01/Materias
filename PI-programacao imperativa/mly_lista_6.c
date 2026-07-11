#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>

/*Símbolos importantes:

& → operador de endereço (“de onde está essa variável na memória”)

* → operador de indireção (“conteúdo no endereço apontado”)

| Função     | O que faz                          | Memória inicializada?       | Sintaxe                    |
| ---------- | ---------------------------------- | --------------------------- | -------------------------- |
| `malloc()` | Aloca um bloco contínuo de memória | ❌ Não (conteúdo indefinido) | `malloc(n * sizeof(tipo))` |
| `calloc()` | Aloca e zera toda a memória        | ✅ Sim (tudo 0)              | `calloc(n, sizeof(tipo))`  |

*/
int main() {
    int a = 5;
    int *ptr = &a;

    printf("Valor de a: %d\n", a);
    printf("Endereco de a: %p\n", &a);
    printf("Valor de ptr (endereco de a): %p\n", ptr);
    printf("Valor apontado por ptr: %d\n", *ptr);

    *ptr = 20; // altera o valor de 'a' através do ponteiro
    printf("Novo valor de a: %d\n", a);

    return 0;
}