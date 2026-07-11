# Section de Código
.section .text

# Função scanf fornecida pelo professor (lê da UART para a RAM)
scanf:
    scanf_loop:
        # Lê caractere da UART
        lb t0, 0(a0)
        # Salva o caractere na memória buffer
        sb t0, 0(a1)
        # Incrementa o ponteiro da memória
        addi a1, a1, 1
        # Verifica se há mais dados no Line Status Register (LSR)
        lb t0, 5(a0)
        andi t0, t0, 1
        # Se houver dados (bit 0 == 1), continua lendo
        bne t0, zero, scanf_loop
    # Finaliza a string com caractere nulo '\0'
    sb zero, 0(a1)
    ret

# Função para converter string da RAM em inteiro
# Argumentos: a0 = ponteiro da string
# Retornos: a0 = número convertido, a1 = ponteiro atualizado pós-número
parse_int:
    li t1, 0          # Resultado acumulado = 0
    li t2, 0          # Flag de número negativo = 0

parse_skip:
    lb t3, 0(a0)
    beqz t3, parse_done_empty
    addi a0, a0, 1

    # Pula delimitadores comuns (Espaço, Nova Linha, Carriage Return, Tab)
    li t4, 32
    beq t3, t4, parse_skip
    li t4, 10
    beq t3, t4, parse_skip
    li t4, 13
    beq t3, t4, parse_skip
    li t4, 9
    beq t3, t4, parse_skip

    # Verifica se o número é negativo
    li t4, 45         # ASCII do '-'
    bne t3, t4, parse_convert
    li t2, 1          # Ativa flag de negativo
    lb t3, 0(a0)
    addi a0, a0, 1

parse_convert:
    li t4, 48         # ASCII '0'
    blt t3, t4, parse_finish
    li t4, 57         # ASCII '9'
    bgt t3, t4, parse_finish

    # t1 = t1 * 10 + (t3 - 48)
    li t4, 10
    mul t1, t1, t4
    addi t3, t3, -48
    add t1, t1, t3

    lb t3, 0(a0)
    addi a0, a0, 1
    j parse_convert

parse_finish:
    addi a0, a0, -1   # Ajusta o ponteiro para o caractere delimitador
    beqz t2, parse_ok_sign
    sub t1, zero, t1  # Inverte o sinal se negativo
parse_ok_sign:
    mv a1, a0
    mv a0, t1
    ret

parse_done_empty:
    mv a1, a0
    li a0, 0
    ret

# Função de ordenação Bubble Sort (Menor para o Maior)
# Argumentos: a0 = Quantidade N, a1 = Endereço do array
sort_array:
    li t0, 0          # i = 0
sa_outer:
    addi t1, a0, -1   # t1 = N - 1
    bge t0, t1, sa_done

    li t2, 0          # j = 0
sa_inner:
    sub t3, a0, t0    # t3 = N - i
    addi t3, t3, -1   # t3 = N - i - 1
    bge t2, t3, sa_next_outer

    slli t4, t2, 2    # j * 4
    add t4, a1, t4    # Endereço de array[j]

    lw t5, 0(t4)      # t5 = array[j]
    lw t6, 4(t4)      # t6 = array[j+1]

    # Se o elemento da direita for maior ou igual ao da esquerda,
    # eles já estão na ordem crescente correta, então pula a troca.
    bge t6, t5, sa_no_swap

    # Realiza a troca (Swap) se o da esquerda for maior que o da direita
    sw t6, 0(t4)
    sw t5, 4(t4)

sa_no_swap:
    addi t2, t2, 1    # j++
    j sa_inner

sa_next_outer:
    addi t0, t0, 1    # i++
    j sa_outer
sa_done:
    ret

# Função para imprimir um inteiro na UART
# Argumentos: a0 = Inteiro, a1 = Endereço Base da UART
print_int:
    li t0, 10
    la t1, digits_buf
    li t2, 0          # Contador de dígitos

    bnez a0, pi_nonzero
    li t3, 48         # Imprime '0' diretamente
    sb t3, 0(a1)
    ret

pi_nonzero:
    bgez a0, pi_loop
    li t3, 45         # Imprime sinal '-'
    sb t3, 0(a1)
    sub a0, zero, a0

pi_loop:
    rem t3, a0, t0
    addi t3, t3, 48   # Converte para caractere ASCII
    add t4, t1, t2
    sb t3, 0(t4)      # Armazena temporariamente no buffer de dígitos
    addi t2, t2, 1
    div a0, a0, t0
    bnez a0, pi_loop

pi_output:
    addi t2, t2, -1
    bltz t2, pi_done
    add t4, t1, t2
    lb t3, 0(t4)
    sb t3, 0(a1)      # Escreve na UART
    j pi_output
pi_done:
    ret

# Função Principal
.global main
main:
    # Prólogo: Salva o contexto na Pilha (Stack)
    addi sp, sp, -32
    sw ra, 28(sp)
    sw s0, 24(sp)
    sw s1, 20(sp)
    sw s2, 16(sp)
    sw s3, 12(sp)
    sw s4, 8(sp)

    # 1. Copia toda a entrada da UART para a RAM
    li s0, 0x10000000  # s0 = Endereço Base da UART
    mv a0, s0
    la a1, input_str
    call scanf

    # 2. Processa o primeiro número (Quantidade N)
    la a0, input_str
    call parse_int
    mv s1, a0          # s1 = N (Quantidade total)
    mv s2, a1          # s2 = Ponteiro atualizado da string na RAM

    # Se N <= 0, encerra imediatamente
    blez s1, main_end

    # 3. Lê os N números subsequentes para o vetor
    la s3, num_buffer  # s3 = Endereço do vetor de números
    li s4, 0           # s4 = Índice do loop (i = 0)

read_numbers_loop:
    bge s4, s1, read_numbers_done
    mv a0, s2
    call parse_int
    mv s2, a1          # Atualiza o ponteiro de leitura da string

    slli t0, s4, 2
    add t0, s3, t0
    sw a0, 0(t0)       # Salva no vetor: num_buffer[i] = valor

    addi s4, s4, 1
    j read_numbers_loop

read_numbers_done:
    # 4. Executa a ordenação crescente
    mv a0, s1          # a0 = N
    mv a1, s3          # a1 = &num_buffer
    call sort_array

    # 5. Imprime os números ordenados separados por vírgula
    li s4, 0           # Revezamento do índice (i = 0)

print_numbers_loop:
    bge s4, s1, print_newline_and_end

    slli t0, s4, 2
    add t0, s3, t0
    lw a0, 0(t0)       # Carrega num_buffer[i]
    mv a1, s0          # Endereço da UART
    call print_int

    # Adiciona vírgula se não for o último elemento (i < N - 1)
    addi t0, s1, -1
    bge s4, t0, skip_comma

    li t1, 44          # ASCII da vírgula ','
    sb t1, 0(s0)

skip_comma:
    addi s4, s4, 1
    j print_numbers_loop

print_newline_and_end:
    li t1, 10          # ASCII de quebra de linha '\n'
    sb t1, 0(s0)

main_end:
    # Epílogo: Restaura registradores salvos na pilha
    # BUG CORRIGIDO: era 'sw' (escrita), deve ser 'lw' (leitura/restauração)
    lw ra, 28(sp)
    lw s0, 24(sp)
    lw s1, 20(sp)
    lw s2, 16(sp)
    lw s3, 12(sp)
    lw s4, 8(sp)
    addi sp, sp, 32

    # Interrupção de parada limpa para o simulador do Poxim-V
    ebreak

# =============================================================================
# Section de Dados e Alocação de Memória
# BUG CORRIGIDO: buffers movidos de .data (ROM) para .bss (RAM gravável).
# No Poxim-V, .data é somente-leitura após a carga. A função scanf precisa
# escrever em input_str, e sort_array/print_int precisam escrever em
# num_buffer e digits_buf — portanto todos devem estar em .bss.
# =============================================================================
.section .bss

input_str:
    .zero 4000         # Espaço para armazenar a string bruta lida da UART

num_buffer:
    .zero 2000         # Espaço para armazenar até 500 inteiros (4 bytes cada)

digits_buf:
    .zero 16           # Buffer temporário para inversão de dígitos no print


