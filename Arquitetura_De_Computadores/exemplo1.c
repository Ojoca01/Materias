// Bibliotecas padronizadas
# include <stdio .h>
# include <stdint .h>
// Função principal
int main () {
// Declaração das variáveis
int32_t s = -1;
uint32_t u = -1;
// Operações de deslocamento para direita
uint32_t rs = s >> 31;
uint32_t ru = u >> 31;
// Impressão dos resultados
1printf ("r >> 31 = %08x, u >> 31 = %08x\n", rs , ru);
// Retornando 0 ( sucesso )
return 0;
}