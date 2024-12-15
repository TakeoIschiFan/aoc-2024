
#include "../common/grid.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TILE_SIZE 50

static coord UP = {-1, 0};
static coord DOWN = {1, 0};
static coord LEFT = {0, -1};
static coord RIGHT = {0, 1};

void play_move(coord robot, coord direction, grid* g) {
    // we dont need to bounds check at all, because the outer edges are all
    // walls, so the robot will never leave the n-1 area
    coord next = coord_plus(robot, direction);
    if (grid_get_at_coord(g, next) == '.') {
        grid_set_at_coord(g, robot, '.');
        grid_set_at_coord(g, next, '@');
        return;
    }

    if (grid_get_at_coord(g, next) == '#') {
        return;
    }

    coord cur_box = next;
    int num_boxes = 0;
    while (grid_get_at_coord(g, cur_box) == 'O') {
        num_boxes++;
        cur_box = coord_plus(cur_box, direction);
    }

    // check if next to the last box there is a wall
    if (grid_get_at_coord(g, cur_box) == '#') {
        return;
    }

    grid_set_at_coord(g, robot, '.');
    grid_set_at_coord(g, next, '@');
    grid_set_at_coord(g, cur_box, 'O');
}

void play_move_b(coord robot, coord direction, grid* g) {
    // we dont need to bounds check at all, because the outer edges are all
    // walls, so the robot will never leave the n-1 area
    coord next = coord_plus(robot, direction);
    if (grid_get_at_coord(g, next) == '.') {
        grid_set_at_coord(g, robot, '.');
        grid_set_at_coord(g, next, '@');
        return;
    }

    if (grid_get_at_coord(g, next) == '#') {
        return;
    }

    if (direction.row == 0) {
        // we are pushing left right, in that case the same logic applies as in
        // part a
        coord cur_box = next;
        int num_boxes = 0;
        while (grid_get_at_coord(g, cur_box) == '[' ||
               grid_get_at_coord(g, cur_box) == ']') {
            num_boxes++;
            cur_box = coord_plus(cur_box, coord_times(direction, 2));
        }

        // check if next to the last box there is a wall
        if (grid_get_at_coord(g, cur_box) == '#') {
            return;
        }

        grid_set_at_coord(g, robot, '.');
        grid_set_at_coord(g, next, '@');
        for (int b = 1; b < 2 * num_boxes + 1; b++) {
            coord box_loc = coord_plus(next, coord_times(direction, b));
            if (grid_get_at_coord(g, box_loc) == '[') {
                grid_set_at_coord(g, box_loc, ']');
            } else {
                grid_set_at_coord(g, box_loc, '[');
            }
        }

    } else {
        // if we are pushing top down, we need to handle things slightly
        // differently
    }
}

int part_a(FILE* txt, char* moves) {
    grid* g = grid_create(TILE_SIZE, TILE_SIZE);
    grid_load(g, txt);

    // play the game
    for (int s = 0; s < strlen(moves); s++) {
        // printf("move %c\n", moves[s]);
        //  find the robot location
        coord robot_loc;
        for (int i = 0; i < grid_size(g); i++) {
            coord loc = grid_coord_from_1d(g, i);
            if (grid_get_at_coord(g, loc) == '@') {
                robot_loc = loc;
                break;
            }
        }

        if (moves[s] == '^') {
            play_move(robot_loc, UP, g);
        } else if (moves[s] == 'v') {
            play_move(robot_loc, DOWN, g);
        } else if (moves[s] == '<') {
            play_move(robot_loc, LEFT, g);

        } else if (moves[s] == '>') {
            play_move(robot_loc, RIGHT, g);
        }

        // grid_print(g);
    }

    // count boxes
    int total = 0;

    for (int i = 0; i < grid_size(g); i++) {
        coord loc = grid_coord_from_1d(g, i);
        if (grid_get_at_coord(g, loc) == 'O') {
            total += loc.row * 100 + loc.col;
        }
    }

    grid_free(g);
    return total;
}

long part_b(FILE* txt, char* moves) {

    grid* old_g = grid_create(TILE_SIZE, TILE_SIZE);
    grid_load(old_g, txt);

    grid* g = grid_create_with(TILE_SIZE * 2, TILE_SIZE, '.');

    // construct the wider grid
    for (int i = 0; i < grid_size(old_g); i++) {
        coord loc = grid_coord_from_1d(old_g, i);
        coord new_loc = (coord){loc.row, loc.col * 2};
        coord new_neighbor = (coord){loc.row, loc.col * 2 + 1};

        char x = grid_get_at_coord(old_g, loc);
        if (x == '@') {
            grid_set_at_coord(g, new_loc, '@');
            grid_set_at_coord(g, new_neighbor, '.');
        } else if (x == '#') {
            grid_set_at_coord(g, new_loc, '#');
            grid_set_at_coord(g, new_neighbor, '#');
        } else if (x == 'O') {
            grid_set_at_coord(g, new_loc, '[');
            grid_set_at_coord(g, new_neighbor, ']');
        }
    }
    // play the game
    for (int s = 0; s < strlen(moves); s++) {
        // printf("move %c\n", moves[s]);
        //  find the robot location
        coord robot_loc;
        for (int i = 0; i < grid_size(g); i++) {
            coord loc = grid_coord_from_1d(g, i);
            if (grid_get_at_coord(g, loc) == '@') {
                robot_loc = loc;
                break;
            }
        }

        if (moves[s] == '^') {
            play_move_b(robot_loc, UP, g);
        } else if (moves[s] == 'v') {
            play_move_b(robot_loc, DOWN, g);
        } else if (moves[s] == '<') {
            play_move_b(robot_loc, LEFT, g);

        } else if (moves[s] == '>') {
            play_move_b(robot_loc, RIGHT, g);
        }

        // grid_print(g);
    }

    // count boxes
    int total = 0;

    for (int i = 0; i < grid_size(g); i++) {
        coord loc = grid_coord_from_1d(g, i);
        if (grid_get_at_coord(g, loc) == '[') {
            total += loc.row * 100 + loc.col;
        }
    }

    grid_free(g);
    return total;
}

int main(void) {
    FILE* txt = fopen("day15/input.txt", "r");
    FILE* movestxt = fopen("day15/input_moves.txt", "r");

    // get file size
    fseek(movestxt, 0, SEEK_END);
    long size = ftell(movestxt);
    rewind(movestxt);

    // read the entire file into memory
    char* contents = calloc(size, sizeof(char));
    fread(contents, size, 1, movestxt);
    fclose(movestxt);

    int answer_a = part_a(txt, contents);
    printf("Part A: %d\n", answer_a);
    rewind(txt);
    // long answer_b = part_b(txt, contents);
    // printf("Part B: %ld\n", answer_b);

    fclose(txt);
    return 0;
}
