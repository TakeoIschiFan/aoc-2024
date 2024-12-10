#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../common/grid.h"

#define GRID_SIZE 55

static coord UP = {0, -1};
static coord DOWN = {0, 1};
static coord LEFT = {-1, 0};
static coord RIGHT = {1, 0};

void step(grid* g, grid* trail_g, coord previous_loc, int previous_num,
          coord direction) {

    // printf("at (%d, %d): %d, setting a step in the (%d, %d, direction)\n",
    //       previous_loc.row, previous_loc.col, previous_num, direction.row,
    //       direction.col);
    coord new_loc = coord_plus(previous_loc, direction);
    if (!grid_coord_in_bounds(g, new_loc)) {
        // printf("invalid out of bounds, returning\n");
        return;
    }

    int new_num = grid_get_int_at_coord(g, new_loc);
    if (!(new_num == previous_num + 1)) {
        // printf("invalid not the right number, returning\n");
        return;
    }

    if (new_num == 9) {
        // printf("found one!\n");
        grid_set_at_coord(trail_g, new_loc, '#');
        return;
    }

    step(g, trail_g, new_loc, new_num, UP);
    step(g, trail_g, new_loc, new_num, DOWN);
    step(g, trail_g, new_loc, new_num, LEFT);
    step(g, trail_g, new_loc, new_num, RIGHT);
}

void step_b(grid* g, int* total, coord previous_loc, int previous_num,
            coord direction) {

    // printf("at (%d, %d): %d, setting a step in the (%d, %d, direction)\n",
    //       previous_loc.row, previous_loc.col, previous_num, direction.row,
    //       direction.col);
    coord new_loc = coord_plus(previous_loc, direction);
    if (!grid_coord_in_bounds(g, new_loc)) {
        // printf("invalid out of bounds, returning\n");
        return;
    }

    int new_num = grid_get_int_at_coord(g, new_loc);
    if (!(new_num == previous_num + 1)) {
        // printf("invalid not the right number, returning\n");
        return;
    }

    if (new_num == 9) {
        // printf("found one!\n");
        (*total)++;
        return;
    }

    step_b(g, total, new_loc, new_num, UP);
    step_b(g, total, new_loc, new_num, DOWN);
    step_b(g, total, new_loc, new_num, LEFT);
    step_b(g, total, new_loc, new_num, RIGHT);
}

int part_a(FILE* txt) {

    grid* g = grid_create(GRID_SIZE, GRID_SIZE);
    grid* trail_g = grid_create(GRID_SIZE, GRID_SIZE);

    int total = 0;

    grid_load(g, txt);
    rewind(txt);

    // grid_print(g);

    for (int i = 0; i < grid_size(g); i++) {
        coord loc = grid_coord_from_1d(g, i);

        if (grid_get_int_at_coord(g, loc) == 0) {

            grid_load(trail_g, txt);
            rewind(txt);

            step(g, trail_g, loc, 0, UP);
            step(g, trail_g, loc, 0, DOWN);
            step(g, trail_g, loc, 0, LEFT);
            step(g, trail_g, loc, 0, RIGHT);

            total += grid_count(trail_g, '#');
        }
    }

    grid_free(trail_g);
    grid_free(g);

    return total;
}

int part_b(FILE* txt) {

    grid* g = grid_create(GRID_SIZE, GRID_SIZE);

    int total_total = 0;

    grid_load(g, txt);
    rewind(txt);

    // grid_print(g);

    for (int i = 0; i < grid_size(g); i++) {
        coord loc = grid_coord_from_1d(g, i);

        if (grid_get_int_at_coord(g, loc) == 0) {

            int* total = calloc(1, sizeof(int));

            step_b(g, total, loc, 0, UP);
            step_b(g, total, loc, 0, DOWN);
            step_b(g, total, loc, 0, LEFT);
            step_b(g, total, loc, 0, RIGHT);

            total_total += (*total);

            free(total);
        }
    }

    grid_free(g);

    return total_total;
}

int main(void) {
    FILE* txt = fopen("day10/input.txt", "r");

    int answer_a = part_a(txt);
    printf("Part A: %d\n", answer_a);
    rewind(txt);
    int answer_b = part_b(txt);
    printf("Part B: %d\n", answer_b);

    fclose(txt);
    return 0;
}
