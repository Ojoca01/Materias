// BIBLIOTECAS E PRE-SETS
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>

using namespace std;

// ======================================================
// CONFIG
// ======================================================

#define MEM_SIZE (1024 * 1024)
#define OFFSET   0x80000000

// ======================================================
// FIELD MASKS (ISA)
// ======================================================

#define MASK_OPCODE 0x7F
#define MASK_RD     0x1F
#define MASK_FUNCT3 0x07
#define MASK_RS1    0x1F
#define MASK_RS2    0x1F
#define MASK_FUNCT7 0x7F

// ======================================================
// IMMEDIATES
// ======================================================

#define MASK_IMM_I  0xFFF
#define MASK_IMM_S  0xFFF
#define MASK_IMM_U  0xFFFFF000

// ======================================================
// SHIFT
// ======================================================

#define MASK_SHAMT  0x1F
// ======================================================
// WRITE-BACK PROTECTION
// ======================================================
// garante que x0 nunca seja modificado
#define WRITE_BACK(rd, value) \
    do { if ((rd) != 0) x[(rd)] = (value); } while(0)

// ======================================================
// AUXILIAR HARDWARE-LIKE
// ======================================================
// garante comportamento idêntico ao hardware em shifts
#define U5(x) ((x) & 0x1F)

// ======================================================
// REGISTERS
// ======================================================

uint32_t x[32] = {0};

const char* x_label[32] = {
    "zero","ra","sp","gp","tp","t0","t1","t2",
    "s0","s1","a0","a1","a2","a3","a4","a5",
    "a6","a7","s2","s3","s4","s5","s6","s7",
    "s8","s9","s10","s11","t3","t4","t5","t6"
};

// ======================================================
// MEMORY
// ======================================================

uint8_t* mem;
FILE* input;
FILE* output;

// ======================================================
// CPU STATE
// ======================================================

uint32_t pc = 0;
uint32_t prox_pc = 0;
uint32_t instrucao = 0;
uint32_t run = 1;

// ======================================================
// DECODE FIELDS
// ======================================================

uint32_t opcode, rd, rs1, rs2, funct3, funct7;
int32_t imm;
uint32_t uimm;
uint32_t resultado;

// buffer de instrução (ESSENCIAL - faltava definição explícita)
char instr[128];

// ======================================================
// FETCH
// ======================================================

uint32_t fetch() {

    if (pc < OFFSET || pc >= OFFSET + MEM_SIZE) {
        run = 0;
        return 0;
    }

    uint32_t addr = pc - OFFSET;

    uint32_t instr =
        mem[addr] |
        (mem[addr+1] << 8) |
        (mem[addr+2] << 16) |
        (mem[addr+3] << 24);

    if (instr == 0x00000000) {
        run = 0;
    }

    return instr;
}

// ======================================================
// HEX LOADER
// ======================================================

void carregar_hex() {

    char line[256];
    uint32_t addr = 0;

    while (fgets(line, sizeof(line), input)) {

        if (line[0] == '@') {
            addr = strtoul(line + 1, NULL, 16);
            continue;
        }

        char* token = strtok(line, " \n");

        while (token) {

            uint32_t byte = strtoul(token, NULL, 16);

            uint32_t index = addr - OFFSET;

            if (index < MEM_SIZE) {
                mem[index] = byte;
            }

            addr++;

            token = strtok(NULL, " \n");
        }
    }
}

// ======================================================
// SIGN EXTEND
// ======================================================

int32_t sign_extend(uint32_t val, int bits) {
    int32_t shift = 32 - bits;
    return (int32_t)(val << shift) >> shift;
}

// ======================================================
// DECODE
// ======================================================

void decode() {

    opcode = instrucao & MASK_OPCODE;
    rd     = (instrucao >> 7)  & MASK_RD;
    funct3 = (instrucao >> 12) & MASK_FUNCT3;
    rs1    = (instrucao >> 15) & MASK_RS1;
    rs2    = (instrucao >> 20) & MASK_RS2;
    funct7 = (instrucao >> 25) & MASK_FUNCT7;

    switch (opcode) {

    // =========================
    // I-TYPE
    // =========================
    case 0x13:
    case 0x03:
    case 0x67:
        imm = sign_extend((instrucao >> 20) & MASK_IMM_I, 12);
        break;

    // =========================
    // S-TYPE
    // =========================
    case 0x23: {
        uint32_t imm4_0  = (instrucao >> 7)  & MASK_RD;      // 5 bits
        uint32_t imm11_5 = (instrucao >> 25) & MASK_FUNCT7;  // 7 bits

        imm = sign_extend((imm11_5 << 5) | imm4_0, 12);
        break;
    }

    // =========================
    // B-TYPE
    // =========================
    case 0x63: {
        uint32_t imm12   = (instrucao >> 31) & 0x1;
        uint32_t imm11   = (instrucao >> 7)  & 0x1;
        uint32_t imm10_5 = (instrucao >> 25) & 0x3F; // 6 bits (mantido literal ✔)
        uint32_t imm4_1  = (instrucao >> 8)  & 0xF;  // 4 bits (mantido literal ✔)

        imm = sign_extend(
            (imm12 << 12) |
            (imm11 << 11) |
            (imm10_5 << 5) |
            (imm4_1 << 1),
        13);
        break;
    }

    // =========================
    // U-TYPE
    // =========================
    case 0x37:
    case 0x17:
        imm = (int32_t)(instrucao & MASK_IMM_U);
        break;

    // =========================
    // J-TYPE
    // =========================
    case 0x6F: {
        uint32_t imm20    = (instrucao >> 31) & 0x1;
        uint32_t imm19_12 = (instrucao >> 12) & 0xFF;   // 8 bits 
        uint32_t imm11    = (instrucao >> 20) & 0x1;
        uint32_t imm10_1  = (instrucao >> 21) & 0x3FF;  // 10 bits 

        imm = sign_extend(
            (imm20 << 20) |
            (imm19_12 << 12) |
            (imm11 << 11) |
            (imm10_1 << 1),
        21);
        break;
    }

    default:
        imm = 0;
    }
}

// ======================================================
// EXECUTE v3 (HARDWARE-LIKE FINAL)
// ======================================================

void validarrd(int32_t resultado) { 
    if (rd != 0)
        x[rd] = resultado;
}

void execute() {

    prox_pc = pc + 4;

    switch(opcode) {

    // ==================================================
    // R-TYPE (0x33) — CORRIGIDO (SEM DUPLICAÇÃO)
    // ==================================================
case 0x33: {

    int32_t resultado = 0;

    switch(funct3) {

    // =========================
    // funct3 = 0x0 (ADD/SUB/MUL)
    // =========================
    case 0x0:
        if (funct7 == 0x00) { // ADD
            resultado = x[rs1] + x[rs2];

            sprintf(instr,"add    %s,%s,%s",
            x_label[rd],x_label[rs1],x_label[rs2]);

            fprintf(output,
            "0x%08x:%-26s %s=0x%08x+0x%08x=0x%08x\n",
            pc,instr,x_label[rd],x[rs1],x[rs2],resultado);
        }
        else if (funct7 == 0x20) { // SUB
            resultado = x[rs1] - x[rs2];

            sprintf(instr,"sub    %s,%s,%s",
            x_label[rd],x_label[rs1],x_label[rs2]);

            fprintf(output,
            "0x%08x:%-26s %s=0x%08x-0x%08x=0x%08x\n",
            pc,instr,x_label[rd],x[rs1],x[rs2],resultado);
        }
        else if (funct7 == 0x01) { // MUL
            int64_t tmp = (int64_t)(int32_t)x[rs1] * (int32_t)x[rs2];
            resultado = (int32_t)tmp;

            sprintf(instr,"mul    %s,%s,%s",
            x_label[rd],x_label[rs1],x_label[rs2]);

            fprintf(output,
            "0x%08x:%-26s %s=0x%08x*0x%08x=0x%08x\n",
            pc,instr,x_label[rd],x[rs1],x[rs2],resultado);
        }
        break;

    // =========================
    // funct3 = 0x1 (SLL / MULH)
    // =========================
    case 0x1:
        if (funct7 == 0x00) { // SLL
            uint32_t shamt = x[rs2] & 0x1F;
            resultado = x[rs1] << shamt;

            sprintf(instr,"sll    %s,%s,%s",
            x_label[rd],x_label[rs1],x_label[rs2]);

            fprintf(output,
            "0x%08x:%-26s %s=0x%08x<<%u=0x%08x\n",
            pc,instr,x_label[rd],x[rs1],shamt,resultado);
        }
        else if (funct7 == 0x01) { // MULH
            int64_t temp =
            (int64_t)(int32_t)x[rs1] *
            (int64_t)(int32_t)x[rs2];

            resultado = (uint32_t)(temp >> 32);

            sprintf(instr,"mulh   %s,%s,%s",
            x_label[rd],x_label[rs1],x_label[rs2]);

            fprintf(output,
            "0x%08x:%-26s %s=0x%08x*0x%08x=0x%08x\n",
            pc,instr,x_label[rd],x[rs1],x[rs2],resultado);
        }
        break;

    // =========================
    // funct3 = 0x2 (SLT / MULHSU)
    // =========================
    case 0x2:
        if (funct7 == 0x00) { // SLT
            resultado = ((int32_t)x[rs1] < (int32_t)x[rs2]);

            sprintf(instr,"slt    %s,%s,%s",
            x_label[rd],x_label[rs1],x_label[rs2]);

            fprintf(output,
            "0x%08x:%-26s %s=(0x%08x<0x%08x)=%u\n",
            pc,instr,x_label[rd],x[rs1],x[rs2],resultado);
        }
        else if (funct7 == 0x01) { // MULHSU
            int64_t temp =
            (int64_t)(int32_t)x[rs1] *
            (uint64_t)x[rs2];

            resultado = (uint32_t)(temp >> 32);

            sprintf(instr,"mulhsu %s,%s,%s",
            x_label[rd],x_label[rs1],x_label[rs2]);

            fprintf(output,
            "0x%08x:%-26s %s=0x%08x*0x%08x=0x%08x\n",
            pc,instr,x_label[rd],x[rs1],x[rs2],resultado);
        }
        break;

    // =========================
    // funct3 = 0x3 (SLTU / MULHU)
    // =========================
    case 0x3:
        if (funct7 == 0x00) { // SLTU
            resultado = (x[rs1] < x[rs2]);

            sprintf(instr,"sltu   %s,%s,%s",
            x_label[rd],x_label[rs1],x_label[rs2]);

            fprintf(output,
            "0x%08x:%-26s %s=(0x%08x<0x%08x)=%u\n",
            pc,instr,x_label[rd],x[rs1],x[rs2],resultado);
        }
        else if (funct7 == 0x01) { // MULHU
            uint64_t temp =
            (uint64_t)x[rs1] *
            (uint64_t)x[rs2];

            resultado = (uint32_t)(temp >> 32);

            sprintf(instr,"mulhu  %s,%s,%s",
            x_label[rd],x_label[rs1],x_label[rs2]);

            fprintf(output,
            "0x%08x:%-26s %s=0x%08x*0x%08x=0x%08x\n",
            pc,instr,x_label[rd],x[rs1],x[rs2],resultado);
        }
        break;

    // =========================
    // funct3 = 0x4 (XOR / DIV)
    // =========================
    case 0x4:
        if (funct7 == 0x00) { // XOR
            resultado = x[rs1] ^ x[rs2];

            sprintf(instr,"xor    %s,%s,%s",
            x_label[rd],x_label[rs1],x_label[rs2]);

            fprintf(output,
            "0x%08x:%-26s %s=0x%08x^0x%08x=0x%08x\n",
            pc,instr,x_label[rd],x[rs1],x[rs2],resultado);
        }
        else if (funct7 == 0x01) { // DIV
            resultado = (x[rs2] == 0) ? -1 :
                        (int32_t)x[rs1] / (int32_t)x[rs2];

            sprintf(instr,"div    %s,%s,%s",
            x_label[rd],x_label[rs1],x_label[rs2]);

            fprintf(output,
            "0x%08x:%-26s %s=0x%08x/0x%08x=0x%08x\n",
            pc,instr,x_label[rd],x[rs1],x[rs2],resultado);
        }
        break;

    // =========================
    // funct3 = 0x5 (SRL/SRA/DIVU)
    // =========================
    case 0x5:
        if (funct7 == 0x00) { // SRL
            resultado = x[rs1] >> (x[rs2] & 0x1F);

            sprintf(instr,"srl    %s,%s,%s",
            x_label[rd],x_label[rs1],x_label[rs2]);

            fprintf(output,
            "0x%08x:%-26s %s=0x%08x>>%u=0x%08x\n",
            pc,instr,x_label[rd],x[rs1],x[rs2]&0x1F,resultado);
        }
        else if (funct7 == 0x20) { // SRA
            resultado = (int32_t)x[rs1] >> (x[rs2] & 0x1F);

            sprintf(instr,"sra    %s,%s,%s",
            x_label[rd],x_label[rs1],x_label[rs2]);

            fprintf(output,
            "0x%08x:%-26s %s=0x%08x>>>%u=0x%08x\n",
            pc,instr,x_label[rd],x[rs1],x[rs2]&0x1F,resultado);
        }
        else if (funct7 == 0x01) { // DIVU
            resultado = (x[rs2] == 0)
                ? 0xFFFFFFFF
                : x[rs1] / x[rs2];

            sprintf(instr,"divu   %s,%s,%s",
            x_label[rd],x_label[rs1],x_label[rs2]);

            fprintf(output,
            "0x%08x:%-26s %s=0x%08x/0x%08x=0x%08x\n",
            pc,instr,x_label[rd],x[rs1],x[rs2],resultado);
        }
        break;

    // =========================
    // funct3 = 0x6 (OR / REM)
    // =========================
    case 0x6:
        if (funct7 == 0x00) {
            resultado = x[rs1] | x[rs2];

            sprintf(instr,"or     %s,%s,%s",
            x_label[rd],x_label[rs1],x_label[rs2]);

            fprintf(output,
            "0x%08x:%-26s %s=0x%08x|0x%08x=0x%08x\n",
            pc,instr,x_label[rd],x[rs1],x[rs2],resultado);
        }
        else if (funct7 == 0x01) {
            resultado = (x[rs2] == 0)
                ? x[rs1]
                : (int32_t)x[rs1] % (int32_t)x[rs2];

            sprintf(instr,"rem    %s,%s,%s",
            x_label[rd],x_label[rs1],x_label[rs2]);

            fprintf(output,
            "0x%08x:%-26s %s=0x%08x%%0x%08x=0x%08x\n",
            pc,instr,x_label[rd],x[rs1],x[rs2],resultado);
        }
        break;

    // =========================
    // funct3 = 0x7 (AND / REMU)
    // =========================
    case 0x7:
        if (funct7 == 0x00) {
            resultado = x[rs1] & x[rs2];

            sprintf(instr,"and    %s,%s,%s",
            x_label[rd],x_label[rs1],x_label[rs2]);

            fprintf(output,
            "0x%08x:%-26s %s=0x%08x&0x%08x=0x%08x\n",
            pc,instr,x_label[rd],x[rs1],x[rs2],resultado);
        }
        else if (funct7 == 0x01) {
            resultado = (x[rs2] == 0)
                ? x[rs1]
                : x[rs1] % x[rs2];

            sprintf(instr,"remu   %s,%s,%s",
            x_label[rd],x_label[rs1],x_label[rs2]);

            fprintf(output,
            "0x%08x:%-26s %s=0x%08x%%0x%08x=0x%08x\n",
            pc,instr,x_label[rd],x[rs1],x[rs2],resultado);
        }
        break;
    }

    validarrd(resultado);
    break;
}
    // ==================================================
    // I-TYPE (0x13) — COMPLETO
    // ==================================================
    case 0x13: {

        int32_t resultado = 0;

        switch(funct3) {

        // =========================
        // ADDI
        // =========================
        case 0x0: {
            resultado = x[rs1] + imm;

            sprintf(instr,"addi   %s,%s,0x%03x",
            x_label[rd],x_label[rs1],imm & 0xFFF);

            fprintf(output,
            "0x%08x:%-26s %s=0x%08x+0x%08x=0x%08x\n",
            pc,instr,x_label[rd],x[rs1],imm,resultado);

            validarrd(resultado);
            break;
        }

        // =========================
        // SLTI
        // =========================
        case 0x2: {
            resultado = ((int32_t)x[rs1] < (int32_t)imm);

            sprintf(instr,"slti   %s,%s,0x%03x",
            x_label[rd],x_label[rs1],imm & 0xFFF);

            fprintf(output,
            "0x%08x:%-26s %s=(0x%08x<0x%08x)=%u\n",
            pc,instr,x_label[rd],x[rs1],imm,resultado);

            validarrd(resultado);
            break;
        }

        // =========================
        // SLTIU
        // =========================
        case 0x3: {
            resultado = (x[rs1] < (uint32_t)imm);

            sprintf(instr,"sltiu  %s,%s,0x%03x",
            x_label[rd],x_label[rs1],imm & 0xFFF);

            fprintf(output,
            "0x%08x:%-26s %s=(0x%08x<0x%08x)=%u\n",
            pc,instr,x_label[rd],x[rs1],imm,resultado);

            validarrd(resultado);
            break;
        }

        // =========================
        // XORI
        // =========================
        case 0x4: {
            resultado = x[rs1] ^ imm;

            sprintf(instr,"xori   %s,%s,0x%03x",
            x_label[rd],x_label[rs1],imm & 0xFFF);

            fprintf(output,
            "0x%08x:%-26s %s=0x%08x^0x%08x=0x%08x\n",
            pc,instr,x_label[rd],x[rs1],imm,resultado);

            validarrd(resultado);
            break;
        }

        // =========================
        // ORI
        // =========================
        case 0x6: {
            resultado = x[rs1] | imm;

            sprintf(instr,"ori    %s,%s,0x%03x",
            x_label[rd],x_label[rs1],imm & 0xFFF);

            fprintf(output,
            "0x%08x:%-26s %s=0x%08x|0x%08x=0x%08x\n",
            pc,instr,x_label[rd],x[rs1],imm,resultado);

            validarrd(resultado);
            break;
        }

        // =========================
        // ANDI
        // =========================
        case 0x7: {
            resultado = x[rs1] & imm;

            sprintf(instr,"andi   %s,%s,0x%03x",
            x_label[rd],x_label[rs1],imm & 0xFFF);

            fprintf(output,
            "0x%08x:%-26s %s=0x%08x&0x%08x=0x%08x\n",
            pc,instr,x_label[rd],x[rs1],imm,resultado);

            validarrd(resultado);
            break;
        }

        // ==================================================
        // SHIFT IMMEDIATE (BIT-ACCURATE)
        // ==================================================

        // =========================
        // SLLI
        // =========================
        case 0x1: {
            uint32_t shamt = (instrucao >> 20) & 0x1F;

            if ((instrucao >> 25) == 0x00) { // funct7 = 0000000
                resultado = x[rs1] << shamt;

                sprintf(instr,"slli   %s,%s,%u",
                x_label[rd],x_label[rs1],shamt);

                fprintf(output,
                "0x%08x:%-26s %s=0x%08x<<%u=0x%08x\n",
                pc,instr,x_label[rd],x[rs1],shamt,resultado);

                validarrd(resultado);
            }
            break;
        }

        // =========================
        // SRLI / SRAI
        // =========================
        case 0x5: {
            uint32_t shamt = (instrucao >> 20) & 0x1F;
            uint32_t funct7_local = (instrucao >> 25) & 0x7F;

            if (funct7_local == 0x00) { // SRLI
                resultado = (uint32_t)x[rs1] >> shamt;

                sprintf(instr,"srli   %s,%s,%u",
                x_label[rd],x_label[rs1],shamt);

                fprintf(output,"0x%08x:%-26s %s=0x%08x>>%u=0x%08x\n",
                pc,instr,x_label[rd],x[rs1],shamt,resultado);

                validarrd(resultado);
            }
            else if (funct7_local == 0x20) { // SRAI
                resultado = (int32_t)x[rs1] >> shamt;

                sprintf(instr,"srai   %s,%s,%u",
                x_label[rd],x_label[rs1],shamt);

               fprintf(output,"0x%08x:%-26s %s=0x%08x>>>%u=0x%08x\n",
                pc,instr,x_label[rd],x[rs1],shamt,resultado);

                validarrd(resultado);
            }
            break;
        }

        } // fim switch funct3

        break;
    }    // ==================================================
    // B-TYPE (0x63) — COMPLETO
    // ==================================================
    case 0x63: {

        int cond = 0;
        uint32_t target = pc + imm;

        switch(funct3) {

        // =========================
        // BEQ
        // =========================
        case 0x0:
            cond = (x[rs1] == x[rs2]);

           sprintf(instr,"beq    %s,%s,0x%03x",x_label[rs1],x_label[rs2],(imm >> 1) & 0xFFF);

            fprintf(output,
            "0x%08x:%-26s (0x%08x==0x%08x)=%u->pc=0x%08x\n",
            pc,instr,x[rs1],x[rs2],cond,cond ? target : prox_pc);
            break;

        // =========================
        // BNE
        // =========================
        case 0x1:
            cond = (x[rs1] != x[rs2]);

            sprintf(instr,"bne    %s,%s,0x%03x",
            x_label[rs1],x_label[rs2],(imm >> 1) & 0xFFF);

            fprintf(output,
            "0x%08x:%-26s (0x%08x!=0x%08x)=%u->pc=0x%08x\n",
            pc,instr,x[rs1],x[rs2],cond,cond ? target : prox_pc);
            break;

        // =========================
        // BLT
        // =========================
        case 0x4:
            cond = ((int32_t)x[rs1] < (int32_t)x[rs2]);

            sprintf(instr,"blt    %s,%s,0x%03x",
            x_label[rs1],x_label[rs2],(imm >> 1) & 0xFFF);

            fprintf(output,
            "0x%08x:%-26s (0x%08x<0x%08x)=%u->pc=0x%08x\n",
            pc,instr,x[rs1],x[rs2],cond,cond ? target : prox_pc);
            break;

        // =========================
        // BGE
        // =========================
        case 0x5:
            cond = ((int32_t)x[rs1] >= (int32_t)x[rs2]);

            sprintf(instr,"bge    %s,%s,0x%03x",
            x_label[rs1],x_label[rs2],(imm >> 1) & 0xFFF);

            fprintf(output,
            "0x%08x:%-26s (0x%08x>=0x%08x)=%u->pc=0x%08x\n",
            pc,instr,x[rs1],x[rs2],cond,cond ? target : prox_pc);
            break;

        // =========================
        // BLTU
        // =========================
        case 0x6:
            cond = (x[rs1] < x[rs2]);

            sprintf(instr,"bltu   %s,%s,0x%03x",
            x_label[rs1],x_label[rs2],(imm >> 1) & 0xFFF);

            fprintf(output,
            "0x%08x:%-26s (0x%08x<0x%08x)=%u->pc=0x%08x\n",
            pc,instr,x[rs1],x[rs2],cond,cond ? target : prox_pc);
            break;

        // =========================
        // BGEU
        // =========================
        case 0x7:
            cond = (x[rs1] >= x[rs2]);

            sprintf(instr,"bgeu   %s,%s,0x%03x",
            x_label[rs1],x_label[rs2],(imm >> 1) & 0xFFF);

            fprintf(output,
            "0x%08x:%-26s (0x%08x>=0x%08x)=%u->pc=0x%08x\n",
            pc,instr,x[rs1],x[rs2],cond,cond ? target : prox_pc);
            break;
        }

        if (cond) prox_pc = target;

        break;
    }
    // ==================================================
    // LOAD (0x03) — COMPLETO
    // ==================================================
    case 0x03: {

        int32_t addr = x[rs1] + imm;
        
        switch(funct3) {

        // =========================
        // LB
        // =========================
        case 0x0: {
            int8_t val = *(int8_t*)&mem[addr - OFFSET];

            sprintf(instr,"lb     %s,0x%03x(%s)",
            x_label[rd],imm & 0xFFF,x_label[rs1]);

            int32_t resultado = (int32_t) val;

            fprintf(output,
            "0x%08x:%-26s %s=mem[0x%08x]=0x%08x\n",
            pc,instr,x_label[rd],addr,resultado);

            validarrd(resultado);
            break;
        }

        // =========================
        // LH
        // =========================
        case 0x1: {
            int16_t val = *(int16_t*)&mem[addr - OFFSET];

            sprintf(instr,"lh     %s,0x%03x(%s)",
            x_label[rd],imm & 0xFFF,x_label[rs1]);

            int32_t resultado = (int32_t) val;

            fprintf(output,
            "0x%08x:%-26s %s=mem[0x%08x]=0x%08x\n",
            pc,instr,x_label[rd],addr,resultado);

            validarrd(resultado);
            break;
        }

        // =========================
        // LW
        // =========================
        case 0x2: {
            int32_t val = *(int32_t*)&mem[addr - OFFSET];

            sprintf(instr,"lw     %s,0x%03x(%s)",
            x_label[rd],imm & 0xFFF,x_label[rs1]);
            
            int32_t resultado = val;

            fprintf(output,
            "0x%08x:%-26s %s=mem[0x%08x]=0x%08x\n",
            pc,instr,x_label[rd],addr,resultado);

            validarrd(resultado);
            break;
        }

        // =========================
        // LBU
        // =========================
        case 0x4: {
            uint8_t val = *(uint8_t*)&mem[addr - OFFSET];

            sprintf(instr,"lbu    %s,0x%03x(%s)",
            x_label[rd],imm & 0xFFF,x_label[rs1]);
            int32_t resultado = (uint32_t) val;

            fprintf(output,
            "0x%08x:%-26s %s=mem[0x%08x]=0x%08x\n",
            pc,instr,x_label[rd],addr,resultado);

            validarrd(resultado);
            break;
        }

        // =========================
        // LHU
        // =========================
        case 0x5: {
            uint16_t val = *(uint16_t*)&mem[addr - OFFSET];

            sprintf(instr,"lhu    %s,0x%03x(%s)",
            x_label[rd],imm & 0xFFF,x_label[rs1]);
            
            int32_t resultado = (uint32_t) val;

            fprintf(output,
            "0x%08x:%-26s %s=mem[0x%08x]=0x%08x\n",
            pc,instr,x_label[rd],addr,resultado);

            validarrd(resultado);
            break;
        }

        }

        break;
    }

    // ==================================================
    // STORE (0x23) — COMPLETO
    // ==================================================
    case 0x23: {

        int32_t addr = x[rs1] + imm;

        switch(funct3) {

        // =========================
        // SB
        // =========================
        case 0x0: {
            *(uint8_t*)&mem[addr - OFFSET] = (uint8_t)x[rs2];

            sprintf(instr,"sb     %s,0x%03x(%s)",
            x_label[rs2],imm & 0xFFF,x_label[rs1]);

            fprintf(output,
            "0x%08x:%-26s mem[0x%08x]=0x%02x\n",
            pc,instr,addr,(uint8_t)x[rs2]);
            break;
        }

        // =========================
        // SH
        // =========================
        case 0x1: {
            *(uint16_t*)&mem[addr - OFFSET] = (uint16_t)x[rs2];

            sprintf(instr,"sh     %s,0x%03x(%s)",
            x_label[rs2],imm & 0xFFF,x_label[rs1]);

            fprintf(output,
            "0x%08x:%-26s mem[0x%08x]=0x%04x\n",
            pc,instr,addr,(uint16_t)x[rs2]);
            break;
        }

        // =========================
        // SW
        // =========================
        case 0x2: {
            *(uint32_t*)&mem[addr - OFFSET] = x[rs2];

            sprintf(instr,"sw     %s,0x%03x(%s)",
            x_label[rs2],imm & 0xFFF,x_label[rs1]);

            fprintf(output,
            "0x%08x:%-26s mem[0x%08x]=0x%08x\n",
            pc,instr,addr,x[rs2]);
            break;
        }

        }

        break;
    }
    // =========================
// JAL
// =========================
case 0x6F: {

    int32_t ret = pc + 4;
    prox_pc = pc + imm;

    sprintf(instr,"jal    %s,0x%05x",
        x_label[rd],
        (imm >> 1) & 0xFFFFF);

    fprintf(output,
    "0x%08x:%-26s pc=0x%08x,%s=0x%08x\n",
    pc, instr,
    prox_pc,
    x_label[rd], ret);

    validarrd(ret);
    break;
}

// =========================
// JALR
// =========================
case 0x67: {

    int32_t ret = pc + 4;
    int32_t target = (x[rs1] + imm) & ~1;

    sprintf(instr,"jalr   %s,%s,0x%03x",
            x_label[rd],
            x_label[rs1],
            imm & 0xFFF);

    fprintf(output,
    "0x%08x:%-26s pc=0x%08x+0x%08x,%s=0x%08x\n",
    pc, instr,
    x[rs1], imm,
    x_label[rd], ret);

    validarrd(ret);
    prox_pc = target;
    break;
}

// =========================
// LUI
// =========================
case 0x37: {

    uint32_t imm_u = instrucao & 0xFFFFF000;

    sprintf(instr,"lui    %s,0x%05x",
            x_label[rd], imm_u >> 12);

    fprintf(output,
    "0x%08x:%-26s %s=0x%08x\n",
    pc, instr,
    x_label[rd], imm_u);

    validarrd(imm_u);
    break;
}

// =========================
// AUIPC
// =========================
case 0x17: {

    int32_t resultado = pc + imm;

    sprintf(instr,"auipc  %s,0x%05x",
            x_label[rd], imm >> 12);

    fprintf(output,
    "0x%08x:%-26s %s=0x%08x+0x%08x=0x%08x\n",
    pc, instr,
    x_label[rd], pc, imm, resultado);

    validarrd(resultado);
    break;
}

// =========================
// SYSTEM (ECALL / EBREAK)
// =========================
case 0x73: {
    uint32_t funct12 = (instrucao >> 20) & 0xFFF;

    if (funct12 == 0x000) { // ECALL
        fprintf(output,"0x%08x:ecall\n", pc);
        run = 0;
    }
    else if (funct12 == 0x001) { // EBREAK
        fprintf(output,"0x%08x:ebreak", pc);
        run = 0;
    }

    break;
}

// =========================
// DEFAULT (ILLEGAL)
// =========================
default: {

    fprintf(output,
    "0x%08x:illegal_instruction\n",
    pc);

    run = 0;
    break;
}

    // ==================================================
    // HARDWARE RULE: x0 SEMPRE ZERO
    // ==================================================
    x[0] = 0;
}
   
}
// ======================================================
// MAIN
// ======================================================

int main(int argc, char* argv[]) {

    // ==================================================
    // VALIDA ARGUMENTOS
    // ==================================================
    if (argc < 3) {
        cout << "uso: " << argv[0] << " in.hex out.txt\n";
        return 1;
    }

    // ==================================================
    // ABERTURA DE ARQUIVOS
    // ==================================================
    input  = fopen(argv[1], "r");
    output = fopen(argv[2], "w");

    if (!input || !output) {
        cout << "erro ao abrir arquivos\n";
        return 1;
    }

    // ==================================================
    // ALOCA MEMORIA
    // ==================================================
    mem = (uint8_t*) calloc(MEM_SIZE, 1);

    // ==================================================
    // RESET CPU
    // ==================================================
    pc  = OFFSET;
    run = 1;

    // ==================================================
    // LOAD PROGRAMA
    // ==================================================
    carregar_hex();

    // ==================================================
    // LOOP PRINCIPAL (FETCH-DECODE-EXECUTE)
    // ==================================================
    while (run) {

        // =========================
        // FETCH
        // =========================
        instrucao = fetch();
        if (!run) break;

        // =========================
        // DECODE
        // =========================
        decode();

        // =========================
        // EXECUTE
        // =========================
        execute();

        // =========================
        // WRITE PC (HARDWARE CORRETO)
        // =========================
        pc = prox_pc;
    }

    // ==================================================
    // FINALIZAÇÃO
    // ==================================================
    fclose(input);
    fclose(output);
    free(mem);

    return 0;
}