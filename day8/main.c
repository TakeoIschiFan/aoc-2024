#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../common/grid.h"

#define GRID_SIZE 50

int part_a(FILE* txt) {

    grid* g = grid_create(GRID_SIZE, GRID_SIZE);
    grid* antinode_g = grid_create(GRID_SIZE, GRID_SIZE);

    grid_load(g, txt);
    rewind(txt);

    grid_load(antinode_g, txt);

    grid_print(g);

    for (int i = 0; i < grid_size(g); i++) {

        coord c = grid_coord_from_1d(g, i);
        char x = grid_get_at_coord(g, c);

        if (isalnum(x)) {
            for (int j = 0; j < grid_size(g); j++) {

                coord cp = grid_coord_from_1d(g, j);
                char y = grid_get_at_coord(g, cp);

                if (coord_eq(c, cp)) {
                    continue;
                }

                if (!(x == y)) {
                    continue;
                }

                coord dist = coord_minus(cp, c);
                coord antinode_loc = coord_plus(c, coord_times(dist, 2));

                if (grid_coord_in_bounds(g, antinode_loc)) {
                    grid_set_at_coord(antinode_g, antinode_loc, '#');
                }
            }
        }
    }

    grid_print(antinode_g);
    int antinode_count = grid_count(antinode_g, '#');
    grid_free(g);
    return antinode_count;
}

int part_b(FILE* txt) {
    grid* g = grid_create(GRID_SIZE, GRID_SIZE);
    grid* antinode_g = grid_create(GRID_SIZE, GRID_SIZE);

    grid_load(g, txt);
    rewind(txt);

    grid_load(antinode_g, txt);

    grid_print(g);

    for (int i = 0; i < grid_size(g); i++) {

        coord c = grid_coord_from_1d(g, i);
        char x = grid_get_at_coord(g, c);

        if (isalnum(x)) {
            for (int j = 0; j < grid_size(g); j++) {

                coord cp = grid_coord_from_1d(g, j);
                char y = grid_get_at_coord(g, cp);

                if (coord_eq(c, cp)) {
                    continue;
                }

                if (!(x == y)) {
                    continue;
                }
                coord dist = coord_minus(cp, c);

                // brute force
                for (int multiplier = 1; multiplier < GRID_SIZE; multiplier++) {
                    coord antinode_loc =
                        coord_plus(c, coord_times(dist, multiplier));

                    if (grid_coord_in_bounds(g, antinode_loc)) {
                        grid_set_at_coord(antinode_g, antinode_loc, '#');
                    }
                }
            }
        }
    }

    grid_print(antinode_g);
    int antinode_count = grid_count(antinode_g, '#');
    grid_free(g);
    return antinode_count;
}

int main(void) {
    FILE* txt = fopen("day8/input.txt", "r");

    int answer_a = part_a(txt);
    printf("Part A: %d\n", answer_a);
    rewind(txt);
    int answer_b = part_b(txt);
    printf("Part B: %d\n", answer_b);

    fclose(txt);
    return 0;
}
