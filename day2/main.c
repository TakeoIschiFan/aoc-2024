#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int part_a(FILE* txt) {
    char line[64];

    unsigned int num_safe = 0;

    while (fgets(line, sizeof(line), txt) != NULL) {

        int nums[16];
        unsigned int idx = 0;

        char* num = strtok(line, " ");

        while (num != NULL) {
            nums[idx] = atoi(num);
            idx++;
            num = strtok(NULL, " ");
        }

        bool positive = true;
        bool valid = true;

        for (unsigned int i = 0; i < idx - 1; i++) {
            int dist = nums[i + 1] - nums[i];

            // store the sign of the first dist
            if (i == 0) {
                if (dist < 0) {
                    positive = false;
                }
            }

            // check if the distance is in the valid range
            if (positive) {
                if (dist > 3 || dist < 1) {
                    valid = false;
                    break;
                }
            } else {
                if (dist < -3 || dist > -1) {
                    valid = false;
                    break;
                }
            }
        }
        if (valid) {
            num_safe++;
        }
    }

    return num_safe;
}

int part_b(FILE* txt) {
    char line[64];

    unsigned int num_safe = 0;

    while (fgets(line, sizeof(line), txt) != NULL) {

        int nums[16];
        unsigned int idx = 0;

        char* num = strtok(line, " ");

        while (num != NULL) {
            nums[idx] = atoi(num);
            idx++;
            num = strtok(NULL, " ");
        }

        bool positive = true;
        int invalids = 0;

        for (unsigned int i = 0; i < idx - 1; i++) {
            int dist = nums[i + 1] - nums[i];

            // store the sign of the first dist
            if (i == 0) {
                if (dist < 0) {
                    positive = false;
                }
            }

            // check if the distance is in the valid range
            if (positive) {
                if (dist > 3 || dist < 1) {
                    invalids++;
                }
            } else {
                if (dist < -3 || dist > -1) {
                    invalids++;
                }
            }
        }
        if (invalids <= 1) {
            num_safe++;
        }
    }

    return num_safe;
}

int main(void) {
    FILE* txt = fopen("day2/input.txt", "r");

    int answer_a = part_a(txt);
    printf("part a: %d\n", answer_a);
    rewind(txt);
    int answer_b = part_b(txt);
    printf("part b: %d\n", answer_b);

    fclose(txt);

    return 0;
}
