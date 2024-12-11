#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../common/ht.h"

u64 count_stones(u64 stone, u64 blink, ht_table* memo) {
    // if we reach the zero'th blink, return 1
    if (blink == 0) {
        return 1;
    }

    // if we have this value stored in the hashtable, return that
    // note that the stone*blink key is not unique, but apparently that is okay
    u64 count = 0;
    if (ht_find(memo, (stone << 32) | (blink), &count)) {
        return count;
    }

    // else, do the calculation manually
    if (stone == 0) {
        count += count_stones(1, blink - 1, memo);
    } else {
        int num_digits = floor(log10(stone)) + 1;

        if (num_digits % 2 == 0) {

            u64 divisor = pow(10, num_digits / 2);
            u64 firstHalf = stone / divisor;
            u64 secondHalf = stone % divisor;

            count += count_stones(firstHalf, blink - 1, memo);
            count += count_stones(secondHalf, blink - 1, memo);
        } else {
            count += count_stones(stone * 2024, blink - 1, memo);
        }
    }

    ht_insert(memo, (stone << 32) | (blink), count);
    return count;
}

u64 part_a(char* txt) {

    u64* buf = calloc(16, sizeof(u64));
    int size = 0;

    char* token = strtok(txt, " ");

    while (token != NULL) {
        buf[size++] = atoll(token);
        token = strtok(NULL, " ");
    }

    ht_table* table = ht_create();

    u64 total = 0;
    for (int i = 0; i < size; ++i) {
        total += count_stones(buf[i], 25, table);
    }

    ht_free(table);
    return total;
}

u64 part_b(char* txt) {
    u64* buf = calloc(16, sizeof(u64));
    int size = 0;

    char* token = strtok(txt, " ");

    while (token != NULL) {
        buf[size++] = atoll(token);
        token = strtok(NULL, " ");
    }

    ht_table* table = ht_create();

    u64 total = 0;
    for (int i = 0; i < size; ++i) {
        total += count_stones(buf[i], 75, table);
    }

    ht_free(table);
    return total;
}

int main(void) {
    char input[] = "6563348 67 395 0 6 4425 89567 739318";

    u64 answer_a = part_a(input);
    printf("Part A: %llu\n", answer_a);
    u64 answer_b = part_b(input);
    printf("Part B: %llu\n", answer_b);

    return 0;
}
