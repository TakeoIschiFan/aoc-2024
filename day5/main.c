// NOTE: AI used to clean up code, but none of the logic
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_DIGITS 100

int part_a(FILE* txt) {

    char line[128];

    unsigned int sum = 0;

    // we represent the rules by an array[i] which is one at every index i =
    // a*NUM_DIGITS + b if b should after of a, 0 otherwise

    bool parsing_rules = 1;
    unsigned int* rules = calloc(NUM_DIGITS * NUM_DIGITS, sizeof(unsigned int));

    while (fgets(line, sizeof(line), txt) != NULL) {

        // 1. parse the rule lines

        if (parsing_rules) {

            if (strlen(line) == 1) { // the newline starting the updates rules
                parsing_rules = false;

                continue;
            }

            int a = 0;
            int b = 0;
            sscanf(line, "%d|%d", &a, &b);

            rules[a * NUM_DIGITS + b] = 1;

        } else {

            // 2. parse the updates

            int previous_nums[100] = {0};
            int previous_length = 0;

            bool ok = true;

            char* token = strtok(line, ",");
            while (token != NULL) {
                int num = atoi(token);
                for (int i = 0; i < previous_length; i++) {
                    if (rules[num * NUM_DIGITS + previous_nums[i]] == 1) {
                        ok = false;
                    }
                }

                token = strtok(NULL, ",");
                previous_nums[previous_length] = num;
                previous_length++;
            }

            if (ok) {
                sum += previous_nums[previous_length / 2];
            }
            printf("\n");
        }
    }

    free(rules);

    return sum;
}

int part_b(FILE* txt) {
    char line[128];

    unsigned int sum = 0;

    // we represent the rules by an array[i] which is one at every index i =
    // a*NUM_DIGITS + b if b should after of a, 0 otherwise

    bool parsing_rules = 1;
    unsigned int* rules = calloc(NUM_DIGITS * NUM_DIGITS, sizeof(unsigned int));

    while (fgets(line, sizeof(line), txt) != NULL) {

        // 1. parse the rule lines

        if (parsing_rules) {

            if (strlen(line) == 1) { // the newline starting the updates rules
                parsing_rules = false;
                continue;
            }

            int a = 0;
            int b = 0;
            sscanf(line, "%d|%d", &a, &b);

            rules[a * NUM_DIGITS + b] = 1;

        } else {

            // 2. parse the updates

            int previous_nums[100] = {0};
            int previous_length = 0;

            bool ok = true;

            char* token = strtok(line, ",");
            while (token != NULL) {
                int num = atoi(token);

                for (int i = 0; i < previous_length; i++) {
                    if (rules[num * NUM_DIGITS + previous_nums[i]] == 1) {
                        ok = false;
                    }
                }

                token = strtok(NULL, ",");
                previous_nums[previous_length] = num;
                previous_length++;
            }

            if (!ok) {
                unsigned int idx = 0;

                while (idx < previous_length) {
                    int to_check_num = previous_nums[idx];
                    for (int i = 0; i < idx; i++) {
                        if (rules[to_check_num * NUM_DIGITS +
                                  previous_nums[i]] == 1) {
                            // swap indices
                            int temp = previous_nums[idx];
                            previous_nums[idx] = previous_nums[i];
                            previous_nums[i] = temp;
                            // continue without advancing index
                            continue;
                        }
                    }
                    idx++;
                }

                sum += previous_nums[previous_length / 2];

                // print
                for (int i = 0; i < previous_length; i++) {
                    printf("%d ", previous_nums[i]);
                }
                printf("\n");
            }
        }
    }

    free(rules);

    return sum;
}

int main(void) {
    FILE* txt = fopen("day5/input.txt", "r");

    int answer_a = part_a(txt);
    printf("part a: %d\n", answer_a);
    rewind(txt);
    int answer_b = part_b(txt);
    printf("part b: %d\n", answer_b);

    fclose(txt);

    return 0;
}
