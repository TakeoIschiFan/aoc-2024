#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int part_a(char* txt) {
    regex_t reegex;
    regmatch_t match;

    int offset = 0;

    int total = 0;

    regcomp(&reegex, "mul\\([0-9]{1,3},[0-9]{1,3}\\)", REG_EXTENDED);

    while (regexec(&reegex, txt + offset, 1, &match, 0) != REG_NOMATCH) {
        int start = match.rm_so + offset;
        int end = match.rm_eo + offset;

        char mul[64];
        sprintf(mul, "%.*s", end - start, txt + start);
        // printf("%s\n", mul);

        int a;
        int b;

        sscanf(mul, "mul(%d,%d)", &a, &b);

        total += (a * b);
        offset = end;
    }

    regfree(&reegex);
    return total;
}

int part_b(char* txt) {
    regex_t reegex;
    regmatch_t match;

    int offset = 0;

    int total = 0;
    bool enabled = true;

    regcomp(&reegex, "mul\\([0-9]{1,3},[0-9]{1,3}\\)|do\\(\\)|don't\\(\\)",
            REG_EXTENDED);

    while (regexec(&reegex, txt + offset, 1, &match, 0) != REG_NOMATCH) {
        int start = match.rm_so + offset;
        int end = match.rm_eo + offset;

        char mul[64];

        sprintf(mul, "%.*s", end - start, txt + start);
        // printf("%s\n", mul);

        if (strcmp(mul, "don't()") == 0) {
            enabled = false;
        } else if (strcmp(mul, "do()") == 0) {
            enabled = true;
        } else {
            int a;
            int b;

            sscanf(mul, "mul(%d,%d)", &a, &b);
            if (enabled) {
                total += (a * b);
            }
        }

        offset = end;
    }

    regfree(&reegex);
    return total;
}

int main(void) {
    FILE* txt = fopen("day3/input.txt", "r");

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
