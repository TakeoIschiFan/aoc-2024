// NOTE: not proud of this one, brute forced most of my way through this code...
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIDTH 141 // EVERY LINE ENDS WITH A NEWLINE GRRRRRRRRRRRRRRRR
#define LENGTH 140

int get_idx(int row, int col) {
    int idxr = row * WIDTH + col;
    return idxr;
}

int get_row(int idx) { return idx / WIDTH; }

int get_col(int idx) { return idx % WIDTH; }

int part_a(char* txt) {
    unsigned int count = 0;

    for (unsigned int i = 0; i < LENGTH * WIDTH; i++) {
        int icol = get_col(i);
        int irow = get_row(i);
        char c = txt[i];

        if (c == 'X') {

            // Check right
            if (icol + 3 < WIDTH) {
                char match[5] = {txt[i], txt[i + 1], txt[i + 2], txt[i + 3],
                                 '\0'};
                if (strcmp(match, "XMAS") == 0) {
                    count++;
                }
            }

            // Check left
            if (icol - 3 >= 0) {
                char match[5] = {txt[i], txt[i - 1], txt[i - 2], txt[i - 3],
                                 '\0'};
                if (strcmp(match, "XMAS") == 0) {
                    count++;
                }
            }

            // Check up
            if (irow - 3 >= 0) {
                char match[5] = {txt[get_idx(irow, icol)],
                                 txt[get_idx(irow - 1, icol)],
                                 txt[get_idx(irow - 2, icol)],
                                 txt[get_idx(irow - 3, icol)], '\0'};
                if (strcmp(match, "XMAS") == 0) {
                    count++;
                }
            }

            // Check down
            if (irow + 3 < LENGTH) {
                char match[5] = {txt[get_idx(irow, icol)],
                                 txt[get_idx(irow + 1, icol)],
                                 txt[get_idx(irow + 2, icol)],
                                 txt[get_idx(irow + 3, icol)], '\0'};
                if (strcmp(match, "XMAS") == 0) {
                    count++;
                }
            }

            // Check bottom-left to top-right
            if (irow - 3 >= 0 && icol - 3 >= 0) {
                char match[5] = {txt[get_idx(irow, icol)],
                                 txt[get_idx(irow - 1, icol - 1)],
                                 txt[get_idx(irow - 2, icol - 2)],
                                 txt[get_idx(irow - 3, icol - 3)], '\0'};
                if (strcmp(match, "XMAS") == 0) {
                    count++;
                }
            }

            // Check top-left to bottom-right
            if (irow - 3 >= 0 && icol + 3 < WIDTH) {
                char match[5] = {txt[get_idx(irow, icol)],
                                 txt[get_idx(irow - 1, icol + 1)],
                                 txt[get_idx(irow - 2, icol + 2)],
                                 txt[get_idx(irow - 3, icol + 3)], '\0'};
                if (strcmp(match, "XMAS") == 0) {
                    count++;
                }
            }

            // Check bottom-right to top-left
            if (irow + 3 < LENGTH && icol - 3 >= 0) {
                char match[5] = {txt[get_idx(irow, icol)],
                                 txt[get_idx(irow + 1, icol - 1)],
                                 txt[get_idx(irow + 2, icol - 2)],
                                 txt[get_idx(irow + 3, icol - 3)], '\0'};
                if (strcmp(match, "XMAS") == 0) {
                    count++;
                }
            }

            // Check top-right to bottom-left
            if (irow + 3 < LENGTH && icol + 3 < WIDTH) {
                char match[5] = {txt[get_idx(irow, icol)],
                                 txt[get_idx(irow + 1, icol + 1)],
                                 txt[get_idx(irow + 2, icol + 2)],
                                 txt[get_idx(irow + 3, icol + 3)], '\0'};
                if (strcmp(match, "XMAS") == 0) {
                    count++;
                }
            }
        }
    }

    return count;
}

int part_b(char* txt) {
    unsigned int count = 0;

    for (unsigned int i = 0; i < LENGTH * WIDTH; i++) {

        int icol = get_col(i);
        int irow = get_row(i);
        char c = txt[i];

        bool left = false;
        bool right = false;

        if (irow == 0 || icol == 0 || icol == WIDTH - 1 || irow == LENGTH - 1) {
            continue;
        }

        if (c == 'A') {

            if ((txt[get_idx(irow - 1, icol - 1)] == 'M' &&
                 txt[get_idx(irow + 1, icol + 1)] == 'S') ||
                (txt[get_idx(irow - 1, icol - 1)] == 'S' &&
                 txt[get_idx(irow + 1, icol + 1)] == 'M')) {
                left = true;
            }
            if ((txt[get_idx(irow + 1, icol - 1)] == 'M' &&
                 txt[get_idx(irow - 1, icol + 1)] == 'S') ||
                (txt[get_idx(irow + 1, icol - 1)] == 'S' &&
                 txt[get_idx(irow - 1, icol + 1)] == 'M')) {
                right = true;
            }
            if (left && right) {
                count++;
            }
        }
    }
    return count;
}

int main(void) {
    FILE* txt = fopen("day4/input.txt", "r");

    // get file size
    fseek(txt, 0, SEEK_END);
    long size = ftell(txt);
    rewind(txt);

    // read the entire file into memory
    char* contents = calloc(size, sizeof(char));
    fread(contents, size, 1, txt);
    fclose(txt);

    int answer_a = part_a(contents);
    printf("part a: %d\n", answer_a);
    int answer_b = part_b(contents);
    printf("part b: %d\n", answer_b);

    return 0;
}
