
#include "../common/grid.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GRID_SIZE 140

static coord UP = {-1, 0};
static coord DOWN = {1, 0};
static coord LEFT = {0, -1};
static coord RIGHT = {0, 1};

typedef struct {
    coord loc;
    int num_neighbours;
} node;

typedef struct {
    node** nodes;
    int num_nodes;
    int capacity;
} farm;

farm* create_farm() {
    farm* f = malloc(sizeof(farm));
    f->nodes = malloc(10 * sizeof(node));
    f->num_nodes = 0;
    f->capacity = 10;
    return f;
}

void free_farm(farm* f) {
    free(f->nodes);
    free(f);
}

bool in_farm(farm* f, coord n) {
    for (int i = 0; i < f->num_nodes; i++) {
        if (coord_eq(f->nodes[i]->loc, n)) {
            return true;
        }
    }
    return false;
}

node* add_node_to_farm(farm* f, coord n) {
    // printf("adding %d,%d to farm\n", n.row, n.col);
    if (f->num_nodes >= f->capacity) {
        f->capacity *= 2;
        f->nodes = realloc(f->nodes, f->capacity * sizeof(node));
    }

    node* no = calloc(1, sizeof(node));
    no->loc = n;
    f->nodes[f->num_nodes++] = no;
    return no;
}

void add_coord_and_neighbors_to_farm(farm* f, grid* g, coord start) {
    node* me = add_node_to_farm(f, start);
    char type = grid_get_at_coord(g, start);

    coord left = coord_plus(start, LEFT);
    if (grid_coord_in_bounds(g, left) && grid_get_at_coord(g, left) == type) {
        me->num_neighbours++;
        if (!in_farm(f, left)) {
            add_coord_and_neighbors_to_farm(f, g, left);
        }
    }
    coord right = coord_plus(start, RIGHT);
    if (grid_coord_in_bounds(g, right) && grid_get_at_coord(g, right) == type) {
        me->num_neighbours++;
        if (!in_farm(f, right)) {
            add_coord_and_neighbors_to_farm(f, g, right);
        }
    }
    coord down = coord_plus(start, DOWN);
    if (grid_coord_in_bounds(g, down) && grid_get_at_coord(g, down) == type) {
        me->num_neighbours++;
        if (!in_farm(f, down)) {
            add_coord_and_neighbors_to_farm(f, g, down);
        }
    }
    coord up = coord_plus(start, UP);
    if (grid_coord_in_bounds(g, up) && grid_get_at_coord(g, up) == type) {
        me->num_neighbours++;
        if (!in_farm(f, up)) {
            add_coord_and_neighbors_to_farm(f, g, up);
        }
    }
}

int part_a(FILE* txt) {
    grid* g = grid_create(GRID_SIZE, GRID_SIZE);
    grid_load(g, txt);

    farm* farms[GRID_SIZE * GRID_SIZE] = {NULL};
    int num_farms = 0;

    for (int i = 0; i < grid_size(g); i++) {
        coord loc = grid_coord_from_1d(g, i);

        // check if this coord is not already part of a farm due to some
        // previous recursive calling of the add_to_farm function
        bool already_part_of_farm = false;

        for (int f = 0; f < num_farms; f++) {
            if (in_farm(farms[f], loc)) {
                already_part_of_farm = true;
                break;
            }
        }

        // if not, create a new farm
        if (already_part_of_farm) {
            continue;
        }

        farm* new_farm = create_farm();
        farms[num_farms++] = new_farm;
        add_coord_and_neighbors_to_farm(new_farm, g, loc);
    }

    int total = 0;
    printf("num farms: %d\n", num_farms);

    // calculate area and perimeter of each farm
    for (int i = 0; i < num_farms; i++) {
        int area = farms[i]->num_nodes;
        // printf("farm %d (chars %c) has %d nodes\n", i,
        // grid_get_at_coord(g, farms[i]->nodes[0]->loc), area);
        int perimeter = 0;
        for (int j = 0; j < area; j++) {
            // printf("calculating perimeter, coord %d %d has %d neighbors \n",
            //       farms[i]->nodes[j]->loc.row, farms[i]->nodes[j]->loc.col,
            //      farms[i]->nodes[j]->num_neighbours);
            int neighbors = farms[i]->nodes[j]->num_neighbours;
            perimeter += (4 - neighbors);
        }

        total += area * perimeter;
    }

    for (int i = 0; i < num_farms; i++) {
        free_farm(farms[i]);
    }

    grid_free(g);
    return total;
}

int part_b(FILE* txt) {
    grid* g = grid_create(GRID_SIZE, GRID_SIZE);
    grid_load(g, txt);

    farm* farms[GRID_SIZE * GRID_SIZE] = {NULL};
    int num_farms = 0;

    for (int i = 0; i < grid_size(g); i++) {
        coord loc = grid_coord_from_1d(g, i);

        // check if this coord is not already part of a farm due to some
        // previous recursive calling of the add_to_farm function
        bool already_part_of_farm = false;

        for (int f = 0; f < num_farms; f++) {
            if (in_farm(farms[f], loc)) {
                already_part_of_farm = true;
                break;
            }
        }

        // if not, create a new farm
        if (already_part_of_farm) {
            continue;
        }

        farm* new_farm = create_farm();
        farms[num_farms++] = new_farm;
        add_coord_and_neighbors_to_farm(new_farm, g, loc);
    }

    int total = 0;
    printf("num farms: %d\n", num_farms);

    // calculate area and perimeter of each farm
    for (int i = 0; i < num_farms; i++) {
        farm* farm = farms[i];
        int area = farm->num_nodes;

        // strategy for calculating the perimeter
        // for each farm, create a (2n+1, n grid that contains the nodes and
        // their horizontal edges, ie for the following grid
        //
        //          . . .    . . .
        //          A A A    . . .
        //  AAA     . . .    . . .
        //  ABA ->  A . A &  . B .
        //  AAA     . . .    . . .
        //          A A A    . . .
        //          . . .    . . .

        // now construct the edges, keeping track whether this is an up or down
        // edge (1 & 0), we need to do this because the same line might
        // transition from an up -> down edge which is considered a different
        // edge
        //
        //          1 1 1    . . .
        //          A A A    . . .
        //  AAA     x 0 x    . 1 .
        //  ABA ->  A . A &  . B .
        //  AAA     x 1 x    . 0 .
        //          A A A    . . .
        //          0 0 0    . . .

        // count the amount of horizontal 1 & 0 lines.

        int perimeter = 0;

        // up down

        int num_horizontal = 0;
        grid* horizontal_grid =
            grid_create_with(GRID_SIZE, 2 * GRID_SIZE + 1, '.');

        for (int j = 0; j < farm->num_nodes; j++) {
            node* node = farm->nodes[j];
            char type = grid_get_at_coord(g, node->loc);
            coord horizontal_loc = {.row = node->loc.row * 2 + 1,
                                    .col = node->loc.col};

            grid_set_at_coord(horizontal_grid, horizontal_loc, 'X');

            coord down = coord_plus(node->loc, DOWN);
            coord hor_down = coord_plus(horizontal_loc, DOWN);

            if (!in_farm(farms[i], down)) {
                grid_set_at_coord(horizontal_grid, hor_down, 'D');
            }

            coord up = coord_plus(node->loc, UP);
            coord hor_up = coord_plus(horizontal_loc, UP);

            if (!in_farm(farms[i], up)) {
                grid_set_at_coord(horizontal_grid, hor_up, 'U');
            }
        }

        // grid_print(horizontal_grid);

        // now loop over all edge lines and count
        for (int r = 0; r < 2 * GRID_SIZE + 1; r += 2) {
            char* line = grid_get_horizontal(horizontal_grid, r);

            int line_idx = 0;
            int num_different = 0;
            char previous = '.';
            while (line_idx < strlen(line)) {
                if ((line[line_idx] == 'U' || line[line_idx] == 'D') &&
                    line[line_idx] != previous) {
                    num_different++;
                }

                previous = line[line_idx];
                line_idx++;
            }
            num_horizontal += num_different;
            free(line);
        }
        // printf("num horizontal found: %d\n", num_horizontal);
        perimeter += num_horizontal;
        grid_free(horizontal_grid);

        // left right

        int num_vertical = 0;
        grid* vertical_grid =
            grid_create_with(GRID_SIZE * 2 + 1, GRID_SIZE, '.');

        for (int j = 0; j < farm->num_nodes; j++) {
            node* node = farm->nodes[j];
            char type = grid_get_at_coord(g, node->loc);
            coord vertical_loc = {.row = node->loc.row,
                                  .col = node->loc.col * 2 + 1};

            grid_set_at_coord(vertical_grid, vertical_loc, 'X');

            coord left = coord_plus(node->loc, LEFT);
            coord ver_left = coord_plus(vertical_loc, LEFT);

            if (!in_farm(farms[i], left)) {
                grid_set_at_coord(vertical_grid, ver_left, 'L');
            }

            coord right = coord_plus(node->loc, RIGHT);
            coord ver_right = coord_plus(vertical_loc, RIGHT);

            if (!in_farm(farms[i], right)) {
                grid_set_at_coord(vertical_grid, ver_right, 'R');
            }
        }

        // grid_print(vertical_grid);

        // now loop over all edge lines and count
        for (int r = 0; r < 2 * GRID_SIZE + 1; r += 2) {
            char* line = grid_get_vertical(vertical_grid, r);

            int line_idx = 0;
            int num_different = 0;
            char previous = '.';
            while (line_idx < strlen(line)) {
                if ((line[line_idx] == 'L' || line[line_idx] == 'R') &&
                    line[line_idx] != previous) {
                    num_different++;
                }

                previous = line[line_idx];
                line_idx++;
            }
            num_vertical += num_different;
            free(line);
        }
        // printf("num vertical found: %d\n", num_vertical);
        perimeter += num_vertical;
        grid_free(vertical_grid);
        total += area * perimeter;
        // printf("total thusfar %d, area %d \n", total, area);
    }

    for (int i = 0; i < num_farms; i++) {
        free_farm(farms[i]);
    }

    grid_free(g);
    return total;
}

int main(void) {
    FILE* txt = fopen("day12/input.txt", "r");

    int answer_a = part_a(txt);
    printf("Part A: %d\n", answer_a);
    rewind(txt);
    int answer_b = part_b(txt);
    printf("Part B: %d\n", answer_b);

    fclose(txt);
    return 0;
}
