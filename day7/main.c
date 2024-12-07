#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long part_a(FILE* txt) {
    char line[256];
    long long total_valid = 0;

    while (fgets(line, sizeof(line), txt) != NULL) {
        // printf("%s\n", line);
        char* ptr = strtok(line, " ");

        // remove the last char which is a :
        int num_len = strlen(ptr);
        ptr[num_len - 1] = '\0';
        long long test_value = atoll(ptr);

        long long num_values[64] = {0};
        int num_count = 0;

        ptr = strtok(NULL, " ");
        while (ptr != NULL) {
            num_values[num_count++] = atoll(ptr);
            ptr = strtok(NULL, " ");
        }

        // we represent the different possible combinations of plus and times in
        // binary i.e for 3 numbers, the possibilitys are 11 (**) 10 (*+) 01
        // (+*) 00 (++) in general, for n numbers, the allowed combinations are
        // always going to be 2^(n-1)

        for (unsigned int bs = 0; bs < 1 << (num_count - 1); bs++) {
            long long result = num_values[0];
            // printf("%d\n", bs);

            for (unsigned int i = 0; i < num_count - 1; i++) {
                if (result > test_value && result < 0) {
                    break;
                }

                if ((bs >> i) & 1) {
                    // printf("doing *\n");
                    result *= num_values[i + 1];
                } else {
                    // printf("doing +\n");
                    result += num_values[i + 1];
                }
            }

            // printf("result: %lld\n", result);
            // printf("total valid: %lld\n", total_valid);

            if (result == test_value) {
                total_valid += test_value;
                break;
            }
        }
    }

    return total_valid;
}

long long part_b(FILE* txt) {
    char line[256];
    long long total_valid = 0;

    while (fgets(line, sizeof(line), txt) != NULL) {
        // printf("%s\n\n\n\n", line);
        char* ptr = strtok(line, " ");

        // remove the last char which is a :
        int num_len = strlen(ptr);
        ptr[num_len - 1] = '\0';
        long long test_value = atoll(ptr);

        long long num_values[64] = {0};
        int num_count = 0;

        ptr = strtok(NULL, " ");
        while (ptr != NULL) {
            num_values[num_count++] = atoll(ptr);
            ptr = strtok(NULL, " ");
        }

        // now we need 2 bits to represent all operations:
        for (unsigned int bs = 0; bs < 1 << (2 * (num_count - 1)); bs++) {

            bool valid =
                true; // flag that will trigger when we hit the one bit in the 4
                      // bit combo which does not mean anything, in whcih case
                      // we should skip the interation entirely

            long long result = num_values[0]; // Start with the first number

            for (unsigned int i = 0; i < num_count - 1; i++) {

                unsigned int op = (bs >> (2 * i)) & 0b11;

                if (op == 0b00) {
                    result += num_values[i + 1];
                } else if (op == 0b01) {
                    result *= num_values[i + 1];
                } else if (op == 0b11) {

                    // https://stackoverflow.com/questions/12700497/how-to-concatenate-two-integers-in-c
                    int digits = log10(num_values[i + 1]) + 1;
                    long long shifted = result * pow(10, digits);
                    long long final = shifted + num_values[i + 1];

                    result = final;

                } else {
                    valid = false;
                    break;
                }
            }

            if (!valid) {
                continue;
            }

            if (result == test_value) {
                total_valid += test_value;
                break;
            }
        }
    }

    return total_valid;
}

int main(void) {
    FILE* txt = fopen("day7/input.txt", "r");

    long long answer_a = part_a(txt);
    printf("Part A: %lld\n", answer_a);
    rewind(txt);
    long long answer_b = part_b(txt);
    printf("Part B: %lld\n", answer_b);

    fclose(txt);
    return 0;
}
