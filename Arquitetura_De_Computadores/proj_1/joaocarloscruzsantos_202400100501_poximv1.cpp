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

    // parada real
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

    opcode = instrucao & 0x7F;
    rd     = (instrucao >> 7) & 0x1F;
    funct3 = (instrucao >> 12) & 0x7;
    rs1    = (instrucao >> 15) & 0x1F;
    rs2    = (instrucao >> 20) & 0x1F;
    funct7 = (instrucao >> 25);

    switch (opcode) {

    // I-TYPE
    case 0x13:
    case 0x03:
    case 0x67:
        imm = sign_extend(instrucao >> 20, 12);
        break;

    // S-TYPE (SW)
    case 0x23:
        imm = ((instrucao >> 7) & 0x1F) |
              ((instrucao >> 25) << 5);
        imm = sign_extend(imm, 12);
        break;

    // B-TYPE (BLT)
    case 0x63: { // B-TYPE

    uint32_t imm12   = (instrucao >> 31) & 0x1;
    uint32_t imm10_5 = (instrucao >> 25) & 0x3F;
    uint32_t imm4_1  = (instrucao >> 8)  & 0xF;
    uint32_t imm11   = (instrucao >> 7)  & 0x1;

    imm = (imm12 << 12) |
          (imm11 << 11) |
          (imm10_5 << 5) |
          (imm4_1 << 1);

    imm = sign_extend(imm, 13);

    break;
}

    // U-TYPE
    case 0x37: // LUI
    case 0x17: // AUIPC
        imm = instrucao & 0xFFFFF000;
        break;

    // J-TYPE (JAL)
    case 0x6F: {
        uint32_t imm20    = (instrucao >> 31) & 0x1;
        uint32_t imm10_1  = (instrucao >> 21) & 0x3FF;
        uint32_t imm11    = (instrucao >> 20) & 0x1;
        uint32_t imm19_12 = (instrucao >> 12) & 0xFF;

        imm = (imm20 << 20) |
              (imm19_12 << 12) |
              (imm11 << 11) |
              (imm10_1 << 1);

        imm = sign_extend(imm, 21);
        break;
    }

    default:
        imm = 0;
    }
}

// ======================================================
// EXECUTE
// ======================================================
void execute() {

    prox_pc = pc + 4;
    char instr[64];

    switch(opcode) {

    // =========================
    // ADDI / SLLI
    // =========================
    case 0x13:
        if (funct3 == 0x0) { // ADDI

            int32_t result = x[rs1] + imm;

            sprintf(instr, "addi   %s,%s,0x%03x",
                    x_label[rd], x_label[rs1], imm & 0xFFF);

            fprintf(output,
                "0x%08x:%-26s %s=0x%08x+0x%08x=0x%08x\n",
                pc, instr,
                x_label[rd], x[rs1], imm, result);

            x[rd] = result;
        }

        else if (funct3 == 0x1) { // SLLI

            int shamt = (instrucao >> 20) & 0x1F;
            int32_t result = x[rs1] << shamt;

            sprintf(instr, "slli   %s,%s,%d",
                    x_label[rd], x_label[rs1], shamt);

            fprintf(output,
                "0x%08x:%-26s %s=0x%08x<<%d=0x%08x\n",
                pc, instr,
                x_label[rd], x[rs1], shamt, result);

            x[rd] = result;
        }
        break;

// =========================
// R-TYPE (M EXTENSION)
// =========================
case 0x33:

    // ADD
    if (funct3 == 0x0 && funct7 == 0x00) {
        int32_t result = x[rs1] + x[rs2];

        sprintf(instr, "add    %s,%s,%s",
                x_label[rd], x_label[rs1], x_label[rs2]);

        fprintf(output,
            "0x%08x:%-26s %s=0x%08x+0x%08x=0x%08x\n",
            pc, instr,
            x_label[rd], x[rs1], x[rs2], result);

        x[rd] = result;
    }

    // MUL
    else if (funct3 == 0x0 && funct7 == 0x01) {
        int32_t result = (int32_t)x[rs1] * (int32_t)x[rs2];

        sprintf(instr, "mul    %s,%s,%s",
                x_label[rd], x_label[rs1], x_label[rs2]);

        fprintf(output,
            "0x%08x:%-26s %s=0x%08x*0x%08x=0x%08x\n",
            pc, instr,
            x_label[rd], x[rs1], x[rs2], result);

        x[rd] = result;
    }

    // MULH
    else if (funct3 == 0x1 && funct7 == 0x01) {
        int64_t result = (int64_t)(int32_t)x[rs1] * (int64_t)(int32_t)x[rs2];

        sprintf(instr, "mulh   %s,%s,%s",
                x_label[rd], x_label[rs1], x_label[rs2]);

        fprintf(output,
            "0x%08x:%-26s %s=0x%08x*0x%08x=0x%08x\n",
            pc, instr,
            x_label[rd], x[rs1], x[rs2], (uint32_t)(result >> 32));

        x[rd] = (uint32_t)(result >> 32);
    }

    // MULHSU
    else if (funct3 == 0x2 && funct7 == 0x01) {
        int64_t result = (int64_t)(int32_t)x[rs1] * (uint64_t)x[rs2];

        sprintf(instr, "mulhsu %s,%s,%s",
                x_label[rd], x_label[rs1], x_label[rs2]);

        fprintf(output,
            "0x%08x:%-26s %s=0x%08x*0x%08x=0x%08x\n",
            pc, instr,
            x_label[rd], x[rs1], x[rs2], (uint32_t)(result >> 32));

        x[rd] = (uint32_t)(result >> 32);
    }

    // MULHU
    else if (funct3 == 0x3 && funct7 == 0x01) {
        uint64_t result = (uint64_t)x[rs1] * (uint64_t)x[rs2];

        sprintf(instr, "mulhu  %s,%s,%s",
                x_label[rd], x_label[rs1], x_label[rs2]);

        fprintf(output,
            "0x%08x:%-26s %s=0x%08x*0x%08x=0x%08x\n",
            pc, instr,
            x_label[rd], x[rs1], x[rs2], (uint32_t)(result >> 32));

        x[rd] = (uint32_t)(result >> 32);
    }

    // DIV
    else if (funct3 == 0x4 && funct7 == 0x01) {
        int32_t result = (x[rs2] == 0) ? -1 : (int32_t)x[rs1] / (int32_t)x[rs2];

        sprintf(instr, "div    %s,%s,%s",
                x_label[rd], x_label[rs1], x_label[rs2]);

        fprintf(output,
            "0x%08x:%-26s %s=0x%08x/0x%08x=0x%08x\n",
            pc, instr,
            x_label[rd], x[rs1], x[rs2], result);

        x[rd] = result;
    }

    // DIVU
    else if (funct3 == 0x5 && funct7 == 0x01) {
        uint32_t result = (x[rs2] == 0) ? 0xFFFFFFFF : x[rs1] / x[rs2];

        sprintf(instr, "divu   %s,%s,%s",
                x_label[rd], x_label[rs1], x_label[rs2]);

        fprintf(output,
            "0x%08x:%-26s %s=0x%08x/0x%08x=0x%08x\n",
            pc, instr,
            x_label[rd], x[rs1], x[rs2], result);

        x[rd] = result;
    }

    // REM
    else if (funct3 == 0x6 && funct7 == 0x01) {
        int32_t result = (x[rs2] == 0) ? x[rs1] : (int32_t)x[rs1] % (int32_t)x[rs2];

        sprintf(instr, "rem    %s,%s,%s",
                x_label[rd], x_label[rs1], x_label[rs2]);

        fprintf(output,
            "0x%08x:%-26s %s=0x%08x%%0x%08x=0x%08x\n",
            pc, instr,
            x_label[rd], x[rs1], x[rs2], result);

        x[rd] = result;
    }

    // REMU
    else if (funct3 == 0x7 && funct7 == 0x01) {
        uint32_t result = (x[rs2] == 0) ? x[rs1] : x[rs1] % x[rs2];

        sprintf(instr, "remu   %s,%s,%s",
                x_label[rd], x_label[rs1], x_label[rs2]);

        fprintf(output,
            "0x%08x:%-26s %s=0x%08x%%0x%08x=0x%08x\n",
            pc, instr,
            x_label[rd], x[rs1], x[rs2], result);

        x[rd] = result;
    }

    break;

    // =========================
    // LW
    // =========================
    case 0x03:
        if (funct3 == 0x2) {

            int32_t addr = x[rs1] + imm;
            uint32_t index = addr - OFFSET;
            int32_t val = *((int32_t*)&mem[index]);

            sprintf(instr, "lw     %s,0x%03x(%s)",
                    x_label[rd], imm & 0xFFF, x_label[rs1]);

            fprintf(output,
                "0x%08x:%-26s %s=mem[0x%08x]=0x%08x\n",
                pc, instr,
                x_label[rd], addr, val);

            x[rd] = val;
        }
        break;

    // =========================
    // SW
    // =========================
    case 0x23:
        if (funct3 == 0x2) {

            int32_t addr = x[rs1] + imm;

            sprintf(instr, "sw     %s,0x%03x(%s)",
                    x_label[rs2], imm & 0xFFF, x_label[rs1]);

            fprintf(output,
                "0x%08x:%-26s mem[0x%08x]=0x%08x\n",
                pc, instr,
                addr, x[rs2]);

            uint32_t index = addr - OFFSET;
            *((uint32_t*)&mem[index]) = x[rs2];
        }
        break;

    // =========================
    // BLT / BNE
    // =========================
    case 0x63:

        if (funct3 == 0x4) { // BLT

            int taken = (int32_t)x[rs1] < (int32_t)x[rs2];
            uint32_t destino = taken ? pc + imm : prox_pc;

            sprintf(instr, "blt    %s,%s,0x%03x",
        x_label[rs1], x_label[rs2], (imm >> 1) & 0xFFF);

            fprintf(output,
                "0x%08x:%-26s (0x%08x<0x%08x)=%d->pc=0x%08x\n",
                pc, instr,
                x[rs1], x[rs2], taken, destino);

            if (taken) prox_pc = destino;
        }

        else if (funct3 == 0x1) { // BNE

            int taken = x[rs1] != x[rs2];
            uint32_t destino = taken ? pc + imm : prox_pc;

                sprintf(instr, "bne    %s,%s,0x%03x",
                        x_label[rs1], x_label[rs2], (imm >> 1) & 0xFFF);

            fprintf(output,
                "0x%08x:%-26s (0x%08x!=0x%08x)=%d->pc=0x%08x\n",
                pc, instr,
                x[rs1], x[rs2], taken, destino);

            if (taken) prox_pc = destino;
        }
        break;

    // =========================
    // JAL
    // =========================
    case 0x6F: {

        int32_t ret = pc + 4;
        prox_pc = pc + imm;

        sprintf(instr, "jal    %s,0x%05x",
                x_label[rd], (imm >> 1) & 0xFFFFF);

        fprintf(output,
            "0x%08x:%-26s pc=0x%08x,%s=0x%08x\n",
            pc, instr,
            prox_pc,
            x_label[rd], ret);

        x[rd] = ret;
        break;
    }

    // =========================
    // JALR
    // =========================
    case 0x67:
        if (funct3 == 0x0) {

            int32_t target = (x[rs1] + imm) & ~1;
            int32_t ret = pc + 4;

            sprintf(instr, "jalr   %s,%s,0x%03x",
                    x_label[rd], x_label[rs1], imm & 0xFFF);

            fprintf(output,
                "0x%08x:%-26s pc=0x%08x+0x%08x,%s=0x%08x\n",
                pc, instr,
                x[rs1], imm,
                x_label[rd], ret);

            x[rd] = ret;
            prox_pc = target;
        }
        break;

    // =========================
    // AUIPC
    // =========================
    case 0x17: {

        int32_t result = pc + imm;

        sprintf(instr, "auipc  %s,0x%05x",
                x_label[rd], imm >> 12);

        fprintf(output,
            "0x%08x:%-26s %s=0x%08x+0x%08x=0x%08x\n",
            pc, instr,
            x_label[rd], pc, imm, result);

        x[rd] = result;
        break;
    }

    // =========================
    // LUI
    // =========================
    case 0x37:

        sprintf(instr, "lui    %s,0x%05x",
                x_label[rd], imm >> 12);

        fprintf(output,
            "0x%08x:%-26s %s=0x%08x\n",
            pc, instr,
            x_label[rd], imm);

        x[rd] = imm;
        break;

    // =========================
    // EBREAK
    // =========================
    case 0x73:
        fprintf(output, "0x%08x:ebreak", pc);
        run = 0;
        break;
    }
}
// ======================================================
// MAIN
// ======================================================

int main(int argc, char* argv[]) {

    if (argc < 3) {
        cout << "uso: " << argv[0] << " in.hex out.txt\n";
        return 1;
    }

    input = fopen(argv[1], "r");
    output = fopen(argv[2], "w");

    if (!input || !output) {
        cout << "erro ao abrir arquivos\n";
        return 1;
    }

    mem = (uint8_t*) calloc(MEM_SIZE, 1);

    pc = OFFSET;
    run = 1;

    carregar_hex();

    int contador = 0;

    while (run) {

        if (contador++ > 100000) {
            printf("STOP: limite de instrucoes atingido\n");
            break;
        }

        instrucao = fetch();

        if (!run) break;

        decode();
        execute();

        pc = prox_pc;

        x[0] = 0;
    }

    fclose(input);
    fclose(output);
    free(mem);

    return 0;
}