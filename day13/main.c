
#include "../common/grid.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRESSES_A 100
#define MAX_PRESSES_B 10000000000000000

// Comparison function
int compare(const void* a, const void* b) { return (*(int*)a - *(int*)b); }

int part_a(FILE* txt) {
    char line[256];
    int total = 0;

    int a_x = 0;
    int a_y = 0;
    int b_x = 0;
    int b_y = 0;
    int prize_x = 0;
    int prize_y = 0;

    while (fgets(line, sizeof(line), txt)) {
        // Parse each type of line and store data
        if (strncmp(line, "Button A:", 9) == 0) {
            sscanf(line, "Button A: X+%d, Y+%d", &a_x, &a_y);
        } else if (strncmp(line, "Button B:", 9) == 0) {
            sscanf(line, "Button B: X+%d, Y+%d", &b_x, &b_y);
        } else if (strncmp(line, "Prize:", 6) == 0) {
            sscanf(line, "Prize: X=%d, Y=%d", &prize_x, &prize_y);

            // after parsing a prize line, execute the logic

            coord a = {.row = a_x, .col = a_y};
            coord b = {.row = b_x, .col = b_y};
            coord prize = {.row = prize_x, .col = prize_y};
            int hits[MAX_PRESSES_A];
            int hit_count = 0;

            for (int i = 0; i < MAX_PRESSES_A; i++) {
                for (int j = 0; j < MAX_PRESSES_A; j++) {

                    if (coord_eq(prize, coord_plus(coord_times(a, i),
                                                   coord_times(b, j)))) {
                        int cost = 3 * i + j;
                        // printf("cost: %d\n", cost);
                        hits[hit_count++] = cost;
                    }
                }
            }

            if (hit_count > 0) {
                qsort(hits, hit_count, sizeof(int), compare);
                total += hits[0];
            }
        }
    }
    return total;
}

long part_b(FILE* txt) {
    char line[256];
    long total = 0;

    long a_x = 0;
    long a_y = 0;
    long b_x = 0;
    long b_y = 0;
    long prize_x = 0;
    long prize_y = 0;

    while (fgets(line, sizeof(line), txt)) {
        // Parse each type of line and store data
        if (strncmp(line, "Button A:", 9) == 0) {
            sscanf(line, "Button A: X+%ld, Y+%ld", &a_x, &a_y);
        } else if (strncmp(line, "Button B:", 9) == 0) {
            sscanf(line, "Button B: X+%ld, Y+%ld", &b_x, &b_y);
        } else if (strncmp(line, "Prize:", 6) == 0) {
            sscanf(line, "Prize: X=%ld, Y=%ld", &prize_x, &prize_y);

            printf("claw machine %s\n", line);

            prize_x += 10000000000000;
            prize_y += 10000000000000;

            double beta = (double)(prize_y * a_x - prize_x * a_y) /
                          (double)(b_y * a_x - b_x * a_y);

            double alpha = (double)(prize_x - beta * b_x) / (double)a_x;
            printf("alpha: %f, beta: %f\n", alpha, beta);

            bool alpha_integer = floor(alpha) == ceil(alpha);
            bool beta_integer = floor(beta) == ceil(beta);

            if (alpha_integer && beta_integer) {
                total += 3 * alpha + beta;
            }
        }
    }
    return total;
}

int main(void) {
    FILE* txt = fopen("day13/input.txt", "r");

    int answer_a = part_a(txt);
    printf("Part A: %d\n", answer_a);
    rewind(txt);
    long answer_b = part_b(txt);
    printf("Part B: %ld\n", answer_b);

    fclose(txt);
    return 0;
}
