#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define RAM_BASE 0x80000000
#define RAM_SIZE (32 * 1024)

#define CLINT_BASE 0x02000000
#define CLINT_SIZE 0x00010000
#define CLINT_MTIMECMP 0x02004000
#define CLINT_MTIME 0x0200BFF8

#define UART_BASE 0x10000000
#define UART_SIZE 0x100

#define PLIC_BASE 0x0C000000
#define PLIC_SIZE 0x04000000

// CSR Addresses
#define CSR_MSTATUS 0x300
#define CSR_MIE     0x304
#define CSR_MTVEC   0x305
#define CSR_MEPC    0x341
#define CSR_MCAUSE  0x342
#define CSR_MTVAL   0x343
#define CSR_MIP     0x344

uint8_t ram[RAM_SIZE];
uint32_t x[32] = {0};
uint32_t csr[4096] = {0};
uint32_t pc;
uint64_t mtime = 0;
uint64_t mtimecmp = 0;

// Variáveis para o delay de hardware
uint8_t msip_delay = 0;
uint8_t msip_val = 0;
uint8_t uart_delay = 0;
const char rx_string[] = "Poxim-V serially says: ";
int rx_index = 0;
FILE* f_saida = NULL;

const char* regs[32] = { "zero", "ra", "sp", "gp", "tp", "t0", "t1", "t2", "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5", "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7", "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6" };

// Variáveis globais de Decode/Execute
uint8_t run = 1;
uint32_t instruction;
uint8_t opcode, rd, funct3, rs1, rs2, funct7;
int32_t imm_i, imm_j, imm_s, imm_b;
uint32_t imm_u;
uint32_t next_pc;

const char* get_csr_name(uint32_t addr) {
    switch(addr) {
        case CSR_MSTATUS: return "mstatus";
        case CSR_MIE: return "mie";
        case CSR_MTVEC: return "mtvec";
        case CSR_MEPC: return "mepc";
        case CSR_MCAUSE: return "mcause";
        case CSR_MTVAL: return "mtval";
        case CSR_MIP: return "mip";
        default: return "unknown_csr";
    }
}

const char* get_cause_name(uint32_t cause) {
    switch(cause) {
        case 1: return "instruction_fault";
        case 2: return "illegal_instruction";
        case 3: return "machine_software";
        case 5: return "load_fault";
        case 7: return "store_fault";
        case 11: return "environment_call";
        case 0x80000003: return "software";
        case 0x80000007: return "timer";
        case 0x8000000b: return "external";
        default: return "unknown";
    }
}

void trap(uint32_t cause, uint32_t epc, uint32_t tval, int is_interrupt) {
    csr[CSR_MEPC] = epc;
    csr[CSR_MCAUSE] = cause;
    csr[CSR_MTVAL] = tval;
    
    uint32_t mstatus_val = csr[CSR_MSTATUS];
    uint32_t mie = (mstatus_val >> 3) & 1;
    mstatus_val = (mstatus_val & ~(1 << 7)) | (mie << 7);
    mstatus_val &= ~(1 << 3);

    mstatus_val &= ~(3 << 11); 
    mstatus_val |= (3 << 11);  

    csr[CSR_MSTATUS] = mstatus_val;

    uint32_t base = csr[CSR_MTVEC] & ~3;
    uint32_t mode = csr[CSR_MTVEC] & 3;
    if (is_interrupt && mode == 1) {
        pc = base + 4 * (cause & 0x7FFFFFFF);
    } else {
        pc = base;
    }

    if (f_saida) {
        if (is_interrupt) {
            fprintf(f_saida, ">interrupt:%-26s cause=0x%08x,epc=0x%08x,tval=0x%08x\n", get_cause_name(cause), cause, epc, tval);
        } else {
            fprintf(f_saida, ">exception:%-26s cause=0x%08x,epc=0x%08x,tval=0x%08x\n", get_cause_name(cause), cause, epc, tval);
        }
    }
}

int mem_write(uint32_t addr, int size, uint32_t val) {
    if (addr >= RAM_BASE && addr + size <= RAM_BASE + RAM_SIZE) {
        for (int i = 0; i < size; i++) {
            ram[addr - RAM_BASE + i] = (val >> (8 * i)) & 0xFF;
        }
        return 1;
    } else if (addr >= UART_BASE && addr < UART_BASE + UART_SIZE) {
        if (addr == UART_BASE + 0) {
            uart_delay = 2; // CORREÇÃO: Atraso correto de 2 ciclos
        }
        return 1;
    } else if (addr >= CLINT_BASE && addr < CLINT_BASE + CLINT_SIZE) {
        if (addr == CLINT_BASE) {
            msip_val = val & 1;
            msip_delay = 1;
        } else if (addr >= CLINT_MTIMECMP && addr < CLINT_MTIMECMP + 8) {
            if (size == 4) {
                if (addr == CLINT_MTIMECMP) {
                    mtimecmp = (mtimecmp & 0xFFFFFFFF00000000ULL) | val;
                } else {
                    mtimecmp = (mtimecmp & 0x00000000FFFFFFFFULL) | ((uint64_t)val << 32);
                }
            }
        }
        return 1;
    } else if (addr >= PLIC_BASE && addr < PLIC_BASE + PLIC_SIZE) {
        if (addr == 0x0C200004 && size == 4) {
            csr[CSR_MIP] &= ~0x800; // Limpa interrupção PLIC
        }
        return 1;
    }
    return 0;
}

int mem_read(uint32_t addr, int size, uint32_t* val) {
    if (addr >= RAM_BASE && addr + size <= RAM_BASE + RAM_SIZE) {
        uint32_t temp = 0;
        for (int i = 0; i < size; i++) {
            temp |= (ram[addr - RAM_BASE + i] << (8 * i));
        }
        *val = temp;
        return 1;
    } else if (addr >= UART_BASE && addr < UART_BASE + UART_SIZE) {
        if (addr == UART_BASE + 5) { 
            if (rx_index < 23) {
                *val = 0x61; 
            } else {
                *val = 0x60; 
            }
        } else if (addr == UART_BASE + 0) { 
            if (rx_index < 23) {
                *val = rx_string[rx_index++];
            } else {
                *val = 0;
            }
        } else if (addr == UART_BASE + 2) { 
            // CORREÇÃO: IIR responde corretamente à pendência de interrupção
            if (csr[CSR_MIP] & 0x800) {
                *val = 4;
            } else {
                *val = 1;
            }
        } else {
            *val = 0;
        }
        return 1;
    } else if (addr >= CLINT_BASE && addr < CLINT_BASE + CLINT_SIZE) {
        if (addr >= CLINT_MTIME && addr < CLINT_MTIME + 8) {
            int offset = addr - CLINT_MTIME;
            *val = (mtime >> (8 * offset)) & 0xFFFFFFFF;
        } else if (addr >= CLINT_MTIMECMP && addr < CLINT_MTIMECMP + 8) {
            int offset = addr - CLINT_MTIMECMP;
            *val = (mtimecmp >> (8 * offset)) & 0xFFFFFFFF;
        } else {
            *val = 0;
        }
        return 1;
    } else if (addr >= PLIC_BASE && addr < PLIC_BASE + PLIC_SIZE) {
        if (addr == 0x0C200004) {
            *val = 10; 
        } else {
            *val = 0;
        }
        return 1;
    }
    return 0;
}

int carregar_hex(const char* nome_arquivo) {
    FILE* input = fopen(nome_arquivo, "r");
    if (!input) {
        return 0;
    }

    char buffer[256];
    uint32_t addr_atual = RAM_BASE;

    while (fscanf(input, "%s", buffer) != EOF) {
        if (buffer[0] == '@') {
            addr_atual = strtoul(&buffer[1], NULL, 16);
        } else {
            if (addr_atual >= RAM_BASE && addr_atual < RAM_BASE + RAM_SIZE) {
                ram[addr_atual - RAM_BASE] = (uint8_t)strtoul(buffer, NULL, 16);
            }
            addr_atual++;
        }
    }
    fclose(input);
    return 1;
}

void decode() {
    opcode = instruction & 0b1111111;
    rd = (instruction >> 7) & 0b11111;
    funct3 = (instruction >> 12) & 0b111;
    rs1 = (instruction >> 15) & 0b11111;
    rs2 = (instruction >> 20) & 0b11111;
    funct7 = instruction >> 25;

    imm_i = ((int32_t)instruction) >> 20; 
    imm_u = instruction & 0xFFFFF000; 
    imm_j = (((int32_t)instruction >> 31) << 20) | (((instruction >> 12) & 0xFF) << 12) | (((instruction >> 20) & 0x1)  << 11) | (((instruction >> 21) & 0x3FF) << 1);
    imm_s = ((((int32_t)instruction) >> 25) << 5) | ((instruction >> 7) & 0x1F);
    imm_b = (((int32_t)instruction >> 31) << 12) | (((instruction >> 7) & 0x1) << 11) | (((instruction >> 25) & 0x3F) << 5) | (((instruction >> 8) & 0xF) << 1);
}

int execute() {
    char mnem[16] = "";
    char ops[32] = "";
    char eq[128] = "";
    uint32_t res = 0;
    next_pc = pc + 4;
    int illegal = 0;

    switch(opcode) {
        case 0x33: // R-Type
            sprintf(ops, "%s,%s,%s", regs[rd], regs[rs1], regs[rs2]);
            if(funct3 == 0 && funct7 == 0) { 
                strcpy(mnem, "add"); res = x[rs1] + x[rs2]; 
                sprintf(eq, "%s=0x%08x+0x%08x=0x%08x", regs[rd], x[rs1], x[rs2], res);
            } else if(funct3 == 0 && funct7 == 0x20) { 
                strcpy(mnem, "sub"); res = x[rs1] - x[rs2]; 
                sprintf(eq, "%s=0x%08x-0x%08x=0x%08x", regs[rd], x[rs1], x[rs2], res); 
            } else if(funct3 == 0 && funct7 == 0x01) { 
                strcpy(mnem, "mul"); res = x[rs1] * x[rs2]; 
                sprintf(eq, "%s=0x%08x*0x%08x=0x%08x", regs[rd], x[rs1], x[rs2], res); 
            } else if (funct3 == 1 && funct7 == 0) { 
                strcpy(mnem, "sll"); uint32_t shamt = x[rs2] & 0x1F; res = x[rs1] << shamt; 
                sprintf(eq, "%s=0x%08x<<%u=0x%08x", regs[rd], x[rs1], shamt, res); 
            } else if (funct3 == 1 && funct7 == 0x01) { 
                strcpy(mnem, "mulh"); int64_t m = (int64_t)(int32_t)x[rs1] * (int32_t)x[rs2]; res = m >> 32;
                sprintf(eq, "%s=0x%08x*0x%08x=0x%08x", regs[rd], x[rs1], x[rs2], res); 
            } else if (funct3 == 2 && funct7 == 0) { 
                strcpy(mnem, "slt"); res = ((int32_t)x[rs1] < (int32_t)x[rs2]) ? 1 : 0; 
                sprintf(eq, "%s=(0x%08x<0x%08x)=%u", regs[rd], x[rs1], x[rs2], res); 
            } else if (funct3 == 2 && funct7 == 0x01) { 
                strcpy(mnem, "mulhsu"); int64_t m = (int64_t)(int32_t)x[rs1] * (uint64_t)x[rs2]; res = m >> 32; 
                sprintf(eq, "%s=0x%08x*0x%08x=0x%08x", regs[rd], x[rs1], x[rs2], res);
            } else if (funct3 == 3 && funct7 == 0) { 
                strcpy(mnem, "sltu"); res = (x[rs1] < x[rs2]) ? 1 : 0; 
                sprintf(eq, "%s=(0x%08x<0x%08x)=%u", regs[rd], x[rs1], x[rs2], res); 
            } else if (funct3 == 3 && funct7 == 0x01) { 
                strcpy(mnem, "mulhu"); uint64_t m = (uint64_t)x[rs1] * (uint64_t)x[rs2]; res = m >> 32; 
                sprintf(eq, "%s=0x%08x*0x%08x=0x%08x", regs[rd], x[rs1], x[rs2], res); 
            } else if (funct3 == 4 && funct7 == 0) { 
                strcpy(mnem, "xor"); res = x[rs1] ^ x[rs2]; 
                sprintf(eq, "%s=0x%08x^0x%08x=0x%08x", regs[rd], x[rs1], x[rs2], res);
            } else if (funct3 == 4 && funct7 == 0x01) {
                strcpy(mnem, "div"); int32_t a = x[rs1], b = x[rs2];
                if (b == 0) res = 0xFFFFFFFF; else if (a == 0x80000000 && b == -1) res = a; else res = a / b;
                sprintf(eq, "%s=0x%08x/0x%08x=0x%08x", regs[rd], x[rs1], x[rs2], res);
            } else if (funct3 == 5 && funct7 == 0) { 
                strcpy(mnem, "srl"); uint32_t shamt = x[rs2] & 0x1F; res = x[rs1] >> shamt;
                sprintf(eq, "%s=0x%08x>>%u=0x%08x", regs[rd], x[rs1], shamt, res);
            } else if (funct3 == 5 && funct7 == 0x20) { 
                strcpy(mnem, "sra"); uint32_t shamt = x[rs2] & 0x1F; res = (int32_t)x[rs1] >> shamt; 
                sprintf(eq, "%s=0x%08x>>>%u=0x%08x", regs[rd], x[rs1], shamt, res);
            } else if (funct3 == 5 && funct7 == 0x01) { 
                strcpy(mnem, "divu"); if (x[rs2] == 0) res = 0xFFFFFFFF; else res = x[rs1] / x[rs2]; 
                sprintf(eq, "%s=0x%08x/0x%08x=0x%08x", regs[rd], x[rs1], x[rs2], res); 
            } else if (funct3 == 6 && funct7 == 0) { 
                strcpy(mnem, "or"); res = x[rs1] | x[rs2]; 
                sprintf(eq, "%s=0x%08x|0x%08x=0x%08x", regs[rd], x[rs1], x[rs2], res); 
            } else if (funct3 == 6 && funct7 == 0x01) {
                strcpy(mnem, "rem"); int32_t a = x[rs1], b = x[rs2];
                if (b == 0) res = a; else if (a == 0x80000000 && b == -1) res = 0; else res = a % b;
                sprintf(eq, "%s=0x%08x%%0x%08x=0x%08x", regs[rd], x[rs1], x[rs2], res);
            } else if (funct3 == 7 && funct7 == 0) { 
                strcpy(mnem, "and"); res = x[rs1] & x[rs2]; 
                sprintf(eq, "%s=0x%08x&0x%08x=0x%08x", regs[rd], x[rs1], x[rs2], res);
            } else if (funct3 == 7 && funct7 == 0x01) { 
                strcpy(mnem, "remu"); if (x[rs2] == 0) res = x[rs1]; else res = x[rs1] % x[rs2]; 
                sprintf(eq, "%s=0x%08x%%0x%08x=0x%08x", regs[rd], x[rs1], x[rs2], res);
            } else illegal = 1;
            if (!illegal && rd != 0) x[rd] = res;
            break;

        case 0x13: // I-Type ALU
            if(funct3 == 0) {
                strcpy(mnem, "addi"); sprintf(ops, "%s,%s,0x%03x", regs[rd], regs[rs1], imm_i & 0xFFF);
                res = x[rs1] + imm_i; sprintf(eq, "%s=0x%08x+0x%08x=0x%08x", regs[rd], x[rs1], imm_i, res);
            } else if(funct3 == 1) {
                strcpy(mnem, "slli"); uint32_t shamt = imm_i & 0x1F; 
                sprintf(ops, "%s,%s,%u", regs[rd], regs[rs1], shamt); 
                res = x[rs1] << shamt; sprintf(eq, "%s=0x%08x<<%u=0x%08x", regs[rd], x[rs1], shamt, res);
            } else if(funct3 == 2) {
                strcpy(mnem, "slti"); sprintf(ops, "%s,%s,0x%03x", regs[rd], regs[rs1], imm_i & 0xFFF);
                res = ((int32_t)x[rs1] < imm_i) ? 1 : 0; sprintf(eq, "%s=(0x%08x<0x%08x)=%u", regs[rd], x[rs1], imm_i, res);
            } else if(funct3 == 3) {
                strcpy(mnem, "sltiu"); sprintf(ops, "%s,%s,0x%03x", regs[rd], regs[rs1], imm_i & 0xFFF);
                res = (x[rs1] < (uint32_t)imm_i) ? 1 : 0; sprintf(eq, "%s=(0x%08x<0x%08x)=%u", regs[rd], x[rs1], imm_i, res);
            } else if(funct3 == 4) {
                strcpy(mnem, "xori"); sprintf(ops, "%s,%s,0x%03x", regs[rd], regs[rs1], imm_i & 0xFFF);
                res = x[rs1] ^ imm_i; sprintf(eq, "%s=0x%08x^0x%08x=0x%08x", regs[rd], x[rs1], imm_i, res);
            } else if(funct3 == 5) {
                uint32_t shamt = imm_i & 0x1F; 
                sprintf(ops, "%s,%s,%u", regs[rd], regs[rs1], shamt); 
                if (funct7 == 0) { 
                    strcpy(mnem, "srli"); res = x[rs1] >> shamt; sprintf(eq, "%s=0x%08x>>%u=0x%08x", regs[rd], x[rs1], shamt, res);
                } else if (funct7 == 0x20) { 
                    strcpy(mnem, "srai"); res = (int32_t)x[rs1] >> shamt; sprintf(eq, "%s=0x%08x>>>%u=0x%08x", regs[rd], x[rs1], shamt, res);
                } else illegal = 1;
            }
            else if(funct3 == 6) {
                strcpy(mnem, "ori"); sprintf(ops, "%s,%s,0x%03x", regs[rd], regs[rs1], imm_i & 0xFFF);
                res = x[rs1] | imm_i; sprintf(eq, "%s=0x%08x|0x%08x=0x%08x", regs[rd], x[rs1], imm_i, res);
            } else if(funct3 == 7) {
                strcpy(mnem, "andi"); sprintf(ops, "%s,%s,0x%03x", regs[rd], regs[rs1], imm_i & 0xFFF);
                res = x[rs1] & imm_i; sprintf(eq, "%s=0x%08x&0x%08x=0x%08x", regs[rd], x[rs1], imm_i, res);
            }
            if (!illegal && rd != 0) x[rd] = res;
            break;

        case 0x03: { // Load
            uint32_t addr = x[rs1] + imm_i;
            sprintf(ops, "%s,0x%03x(%s)", regs[rd], imm_i & 0xFFF, regs[rs1]);
            uint32_t loaded;
            
            if (funct3 == 0) { 
                strcpy(mnem, "lb"); 
                if (!mem_read(addr, 1, &loaded)) illegal = 2;
                else res = (int32_t)(int8_t)loaded;
            } else if (funct3 == 1) { 
                strcpy(mnem, "lh"); 
                if (!mem_read(addr, 2, &loaded)) illegal = 2;
                else res = (int32_t)(int16_t)loaded;
            } else if (funct3 == 2) { 
                strcpy(mnem, "lw"); 
                if (!mem_read(addr, 4, &loaded)) illegal = 2;
                else res = loaded;
            } else if (funct3 == 4) { 
                strcpy(mnem, "lbu"); 
                if (!mem_read(addr, 1, &loaded)) illegal = 2;
                else res = loaded;
            } else if (funct3 == 5) { 
                strcpy(mnem, "lhu"); 
                if (!mem_read(addr, 2, &loaded)) illegal = 2;
                else res = loaded;
            } else { illegal = 1; }

            if (illegal == 2) { trap(5, pc, addr, 0); return 0; }
            if (!illegal) {
                sprintf(eq, "%s=mem[0x%08x]=0x%08x", regs[rd], addr, res);
                if (rd != 0) x[rd] = res;
            }
            break;
        }

        case 0x23: { // Store
            uint32_t addr_s = x[rs1] + imm_s;
            sprintf(ops, "%s,0x%03x(%s)", regs[rs2], (imm_s & 0xFFF), regs[rs1]);
            
            if (funct3 == 0) { 
                strcpy(mnem, "sb"); 
                if (!mem_write(addr_s, 1, x[rs2])) illegal = 3;
                sprintf(eq, "mem[0x%08x]=0x%02x", addr_s, (uint8_t)x[rs2]); 
            } else if (funct3 == 1) { 
                strcpy(mnem, "sh"); 
                if (!mem_write(addr_s, 2, x[rs2])) illegal = 3;
                sprintf(eq, "mem[0x%08x]=0x%04x", addr_s, (uint16_t)x[rs2]); 
            } else if (funct3 == 2) { 
                strcpy(mnem, "sw"); 
                if (!mem_write(addr_s, 4, x[rs2])) illegal = 3;
                sprintf(eq, "mem[0x%08x]=0x%08x", addr_s, x[rs2]);
            } else { illegal = 1; }
            
            if (illegal == 3) { trap(7, pc, addr_s, 0); return 0; }
            break;
        }

        case 0x63: { // B-Type
            sprintf(ops, "%s,%s,0x%03x", regs[rs1], regs[rs2], (imm_b >> 1) & 0xFFF);
            uint8_t cond = 0;
            if(funct3 == 0) { 
                strcpy(mnem, "beq"); cond = (x[rs1] == x[rs2]); 
                sprintf(eq, "(0x%08x==0x%08x)=%u->pc=0x%08x", x[rs1], x[rs2], cond, cond ? pc + imm_b : pc + 4);
            } else if(funct3 == 1) { 
                strcpy(mnem, "bne"); cond = (x[rs1] != x[rs2]); 
                sprintf(eq, "(0x%08x!=0x%08x)=%u->pc=0x%08x", x[rs1], x[rs2], cond, cond ? pc + imm_b : pc + 4);
            } else if(funct3 == 4) { 
                strcpy(mnem, "blt"); cond = ((int32_t)x[rs1] < (int32_t)x[rs2]) ? 1 : 0;
                sprintf(eq, "(0x%08x<0x%08x)=%u->pc=0x%08x", x[rs1], x[rs2], cond, cond ? pc + imm_b : pc + 4);
            } else if(funct3 == 5) { 
                strcpy(mnem, "bge"); cond = ((int32_t)x[rs1] >= (int32_t)x[rs2]); 
                sprintf(eq, "(0x%08x>=0x%08x)=%u->pc=0x%08x", x[rs1], x[rs2], cond, cond ? pc + imm_b : pc + 4);
            } else if(funct3 == 6) { 
                strcpy(mnem, "bltu"); cond = (x[rs1] < x[rs2]); 
                sprintf(eq, "(0x%08x<0x%08x)=%u->pc=0x%08x", x[rs1], x[rs2], cond, cond ? pc + imm_b : pc + 4);
            } else if(funct3 == 7) { 
                strcpy(mnem, "bgeu"); cond = (x[rs1] >= x[rs2]); 
                sprintf(eq, "(0x%08x>=0x%08x)=%u->pc=0x%08x", x[rs1], x[rs2], cond, cond ? pc + imm_b : pc + 4);
            } else { illegal = 1; }
            if (cond) next_pc = pc + imm_b;
            break;
        }

        case 0b1101111: { // jal
            uint32_t return_addr = pc + 4;
            uint32_t addr_alvo = pc + imm_j;
            strcpy(mnem, "jal");
            sprintf(ops, "%s,0x%05x", regs[rd], (uint32_t)((imm_j >> 1) & 0xFFFFF));
            sprintf(eq, "pc=0x%08x,%s=0x%08x", addr_alvo, regs[rd], return_addr);
            if(rd != 0) x[rd] = return_addr;
            next_pc = addr_alvo;
            break;
        }

        case 0x67: // jalr
            if (funct3 == 0) {
                strcpy(mnem, "jalr");
                sprintf(ops, "%s,%s,0x%03x", regs[rd], regs[rs1], imm_i & 0xFFF);
                res = pc + 4;
                next_pc = (x[rs1] + imm_i) & ~1;
                sprintf(eq, "pc=0x%08x+0x%08x,%s=0x%08x", x[rs1], imm_i, regs[rd], res);
                if (rd != 0) x[rd] = res;
            } else { illegal = 1; }
            break;

        case 0x37: // lui
            strcpy(mnem, "lui");
            sprintf(ops, "%s,0x%05x", regs[rd], imm_u >> 12);
            res = imm_u; sprintf(eq, "%s=0x%08x", regs[rd], res);
            if (rd != 0) x[rd] = res;
            break;

        case 0x17: // auipc
            strcpy(mnem, "auipc");
            sprintf(ops, "%s,0x%05x", regs[rd], imm_u >> 12);
            res = pc + imm_u; sprintf(eq, "%s=0x%08x+0x%08x=0x%08x", regs[rd], pc, imm_u, res);
            if (rd != 0) x[rd] = res;
            break;

        case 0x73: // System / CSR
            if (funct3 == 0) {
                if (imm_i == 0) { // ecall
                    if (f_saida) fprintf(f_saida, "0x%08x:ecall\n", pc);
                    trap(11, pc, 0, 0); 
                    return 0; 
                } else if (imm_i == 1) { // ebreak
                    if (f_saida) fprintf(f_saida, "0x%08x:ebreak\n", pc);
                    run = 0;
                    return 0; 
                } else if ((instruction >> 20) == 0x302) { // mret
                    strcpy(mnem, "mret");
                    next_pc = csr[CSR_MEPC];
                    
                    uint32_t mstatus_val = csr[CSR_MSTATUS];
                    uint32_t mpie = (mstatus_val >> 7) & 1;
                    mstatus_val = (mstatus_val & ~(1 << 3)) | (mpie << 3);
                    mstatus_val |= (1 << 7);
                    
                    mstatus_val &= ~(3 << 11); 

                    csr[CSR_MSTATUS] = mstatus_val;

                    sprintf(eq, "pc=0x%08x", next_pc);
                }
                else { illegal = 1; }
            } else if (funct3 == 1 || funct3 == 2 || funct3 == 3) {
                uint32_t csr_addr = imm_i & 0xFFF;
                const char* csr_name = get_csr_name(csr_addr);
                uint32_t old_val = csr[csr_addr];
                uint32_t new_val = old_val;
                
                if (funct3 == 1) { 
                    strcpy(mnem, "csrrw");
                    sprintf(ops, "%s,%s,%s", regs[rd], csr_name, regs[rs1]);
                    new_val = x[rs1];
                    sprintf(eq, "%s=%s=0x%08x,%s=%s=0x%08x", regs[rd], csr_name, old_val, csr_name, regs[rs1], new_val);
                } else if (funct3 == 2) { 
                    strcpy(mnem, "csrrs");
                    sprintf(ops, "%s,%s,%s", regs[rd], csr_name, regs[rs1]);
                    if (rs1 != 0) new_val = old_val | x[rs1];
                    sprintf(eq, "%s=%s=0x%08x,%s|=%s=0x%08x|0x%08x=0x%08x", regs[rd], csr_name, old_val, csr_name, regs[rs1], old_val, x[rs1], new_val);
                } else if (funct3 == 3) { 
                    strcpy(mnem, "csrrc");
                    sprintf(ops, "%s,%s,%s", regs[rd], csr_name, regs[rs1]);
                    if (rs1 != 0) new_val = old_val & ~x[rs1];
                    sprintf(eq, "%s=%s=0x%08x,%s&=~%s=0x%08x&0x%08x=0x%08x", regs[rd], csr_name, old_val, csr_name, regs[rs1], old_val, ~x[rs1], new_val);
                }
                csr[csr_addr] = new_val;
                if (rd != 0) x[rd] = old_val;
            } else {
                illegal = 1;
            }
            break;
        default:
            illegal = 1;
    }
    
    if (illegal) {
        trap(2, pc, instruction, 0);
        return 0; 
    }

    if ((run && opcode != 0x73) || (opcode == 0x73 && imm_i != 1 && imm_i != 0)) {
        if (f_saida) {
            fprintf(f_saida, "0x%08x:%-7s%-20s%s\n", pc, mnem, ops, eq);
        }
        return 1; 
    }

    return 0;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Uso: ./simulador entrada.hex saida.out\n");
        return 1;
    }

    f_saida = fopen(argv[2], "w");
    if (f_saida == NULL) return 1;

    carregar_hex(argv[1]);

    pc = RAM_BASE;

    while (run) {
        csr[CSR_MTVAL] = 0;

        // Processar os delays para gerar interrupções de hardware/timer
        if (msip_delay > 0) {
            msip_delay--;
            if (msip_delay == 0) {
                if (msip_val) csr[CSR_MIP] |= 0x08;
                else csr[CSR_MIP] &= ~0x08;
            }
        }
        if (uart_delay > 0) {
            uart_delay--;
            if (uart_delay == 0) {
                csr[CSR_MIP] |= 0x800; // Levanta a interrupção externa imediatamente
            }
        }

        // Atualiza o bit de Timer pendente antes de avaliar as prioridades
        if (mtime >= mtimecmp) csr[CSR_MIP] |= 0x80;
        else csr[CSR_MIP] &= ~0x80;

        // Verificação se pode executar interrupções pendentes (Prioridade: Externa > Software > Timer)
        if (csr[CSR_MSTATUS] & 0x08) {
            if ((csr[CSR_MIE] & 0x800) && (csr[CSR_MIP] & 0x800)) {
                trap(0x8000000b, pc, 0, 1);
                continue;
            }
            if ((csr[CSR_MIE] & 0x08) && (csr[CSR_MIP] & 0x08)) {
                trap(0x80000003, pc, 0, 1);
                continue;
            }
            if ((csr[CSR_MIE] & 0x80) && (csr[CSR_MIP] & 0x80)) {
                trap(0x80000007, pc, 0, 1);
                continue;
            }
        }

        if (!mem_read(pc, 4, &instruction)) {
            trap(1, pc, 0, 0);
            continue;
        }

        mtime++;
        decode();

        if (execute()) {
            pc = next_pc;
        }
    }

    if (f_saida) {
        fclose(f_saida);
    }

    return 0;
}