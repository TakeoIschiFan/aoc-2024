
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long combo_operand(int operand, long long a, long long b, long long c) {
    if (operand < 4) {
        return operand;
    }
    if (operand == 4) {
        return a;
    }
    if (operand == 5) {
        return b;
    }
    if (operand == 6) {
        return c;
    }
    printf("Combo operand 7 requested, impossible");
    exit(-1);
}

int part_a(FILE* txt) {

    // parse input
    char line[1024];
    long long a, b, c = 0;

    fgets(line, sizeof(line), txt);
    sscanf(line, "Register A: %lld", &a);
    fgets(line, sizeof(line), txt);
    sscanf(line, "Register B: %lld", &b);
    fgets(line, sizeof(line), txt);
    sscanf(line, "Register C: %lld", &c);
    fgets(line, sizeof(line), txt);
    fgets(line, sizeof(line), txt);

    int program[1024];
    int len_program = 0;
    int output[1024];
    int len_output = 0;

    for (int i = 9; i < strlen(line); i += 2) {
        program[len_program++] = atoi(&line[i]);
    }

    // simulate game
    int instruction_pointer = 0;

    while (instruction_pointer < len_program) {

        printf("registers: %lld %lld %lld\n", a, b, c);

        int opcode = program[instruction_pointer];
        int operand = program[instruction_pointer + 1];

        switch (opcode) {
            case 0: {
                a = a / (2 << (combo_operand(operand, a, b, c) - 1));
                instruction_pointer += 2;
                break;
            }
            case 1: {
                b = b ^ operand;
                instruction_pointer += 2;
                break;
            }
            case 2: {
                b = combo_operand(operand, a, b, c) % 8;
                instruction_pointer += 2;
                break;
            }
            case 3: {
                if (a == 0) {
                    instruction_pointer += 2;
                } else {
                    instruction_pointer = operand;
                }
                break;
            }
            case 4: {
                b = b ^ c;
                instruction_pointer += 2;
                break;
            }
            case 5: {
                output[len_output++] = combo_operand(operand, a, b, c) % 8;
                instruction_pointer += 2;
                break;
            }
            case 6: {
                b = a / (2 << (combo_operand(operand, a, b, c) - 1));
                instruction_pointer += 2;
                break;
            }
            case 7: {
                c = a / (2 << (combo_operand(operand, a, b, c) - 1));
                instruction_pointer += 2;
                break;
            }
        }
        printf("registers after op: %lld %lld %lld\n", a, b, c);
    }
    for (int i = 0; i < len_output; i++) {
        printf("%d", output[i]);
        printf(",");
    }

    printf("\n");

    return -1;
}

long part_b(FILE* txt) { // parse input
    return -1;
}

int main(void) {
    FILE* txt = fopen("day17/test.txt", "r");

    int answer_a = part_a(txt);
    printf("Part A: %d\n", answer_a);
    rewind(txt);
    long answer_b = part_b(txt);
    printf("Part B: %ld\n", answer_b);

    fclose(txt);
    return 0;
}
