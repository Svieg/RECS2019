#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#define SECURE_ENCLAVE_LENGTH 1024
#define MAX_LOCK_KEY_LENGTH 50

// Secure enclave that only the VM can write too.
uint32_t secure_enclave[SECURE_ENCLAVE_LENGTH] = {0};

// Registers

// General purpose registers
int registers[3];

// Instruction pointer
int pc = 0;

// Secure Enclave Pointer
int sep = 0;


// Instructions

// inc reg
// opcode: 0x41
void inc(int* reg) {

    *reg = (*reg) + 1;

}

// movs
// mov reg, imm
// 0x42
void mov_reg_imm(int* reg, int imm) {

    *reg = imm;

}

// mov reg, reg
void mov_reg_reg(int* dest, int* src) {

    *dest = *src;

}

void mov_ptr_reg(int* offset, int* src) {

    if (*offset < SECURE_ENCLAVE_LENGTH) {

        secure_enclave[*offset] = *src;

    }

}

void validate() {

    int unlocked = 0;
    printf("[*] Accessing the secure enclave...\n");
    if (secure_enclave[sep] == 1) {
        if (secure_enclave[sep + 1] == 9) {
            if (secure_enclave[sep + 2] == 2) {
                if (secure_enclave[sep + 3] == 9) {
                    unlocked = 1;
                }
            }
        }
    }

    if (unlocked) {
        printf("[*] Unlocking lock one.\n");
    }
    else {
        printf("[*] Key is incorrect. Contact your administrator.\n");
    }

}

void save_sep(int* reg) {

    *reg = sep;

}

void generate_sep() {

    srand(time(0));

    sep = rand() % (SECURE_ENCLAVE_LENGTH - (4*sizeof(int)));

}

int* get_reg(uint8_t index) {
    if (index >= 0 && index <= 2) {
        return &(registers[index]);
    }
    return NULL;
}

int parse_bytecode() {

    int pc, imm, i, j;
    int* dst;
    int* src;

    generate_sep();

    char bytecode[MAX_LOCK_KEY_LENGTH];

    read(0, bytecode, MAX_LOCK_KEY_LENGTH);

    for (pc=0; pc < MAX_LOCK_KEY_LENGTH;) {
        char opcode = bytecode[pc++];
        switch(opcode) {

            // inc reg
            case 'A':
                dst = get_reg(bytecode[pc++]);
                if (!dst)
                    return EXIT_FAILURE;
                inc(dst);
                break;
            case 'B':
                // mov reg, imm
                dst = get_reg(bytecode[pc++]);
                if (!dst)
                    return EXIT_FAILURE;
                imm = *((int*) &bytecode[pc]);
                pc += sizeof(int);
                mov_reg_imm(dst, imm);
                break;
            case 'C':
                // mov reg, reg
                dst = get_reg(bytecode[pc++]);
                if (!dst)
                    return EXIT_FAILURE;
                src = get_reg(bytecode[pc++]);
                if (!src)
                    return EXIT_FAILURE;
                mov_reg_reg(dst, src);
                break;
            case 'D':
                // mov ptr, reg
                dst = get_reg(bytecode[pc++]);
                src = get_reg(bytecode[pc++]);
                if (!src)
                    return EXIT_FAILURE;
                mov_ptr_reg(dst, src);
                break;
            case 'E':
                // save sep
                dst = get_reg(bytecode[pc++]);
                if (!dst)
                    return EXIT_FAILURE;
                save_sep(dst);
                break;
            case 'F':
                // validate
                validate();
                break;
            case 'G':
                // DEBUG
                // TODO: Create function
                printf("[*] DEBUG\n");
                printf("[-] R0 = %d\n", registers[0]);
                printf("[-] R1 = %d\n", registers[1]);
                printf("[-] R2 = %d\n", registers[2]);
                printf("[-] SEP = %d\n", sep);
                printf("[-] PC = %d\n", pc);
                printf("[-] MEMORY\n");
                printf("0\t1\t2\t3\t4\t5\t6\t7\t8\t9\tA\tB\tC\tD\tE\tF\n");
                printf("-\t-\t-\t-\t-\t-\t-\t-\t-\t-\t-\t-\t-\t-\t-\t-\n");
                for (i = 0; i < SECURE_ENCLAVE_LENGTH / 16; i++) {
                    for (j = 0; j < 16; j++) {
                        printf("%d\t", secure_enclave[(i*16) + j]);
                    }
                    printf("\n");
                }
                break;
            default:
                return EXIT_SUCCESS;
        }

    }

    return EXIT_SUCCESS;

}


void usage() {

    printf("Usage: ./lock_one_service\n");

}

int main(int argc, char* argv[]) {

    if (argc > 1) {
        usage();
        return EXIT_FAILURE;
    }

    return parse_bytecode();

}
