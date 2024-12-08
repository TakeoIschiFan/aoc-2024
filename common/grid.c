#include "grid.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO: Bounds checking in pretty much every function...

grid* grid_create(unsigned int width, unsigned int height) {

    char* contents = calloc(sizeof(char), width * height);
    grid* g = calloc(sizeof(grid), 1);
    g->width = width;
    g->height = height;
    g->content = contents;

    return g;
}

void grid_free(grid* g) {
    free(g->content);
    free(g);
}
void grid_load(grid* g, FILE* txt) {

    char line[g->width + 2];
    unsigned int row = 0;

    while (fgets(line, sizeof(line), txt) != NULL) {
        memcpy(&g->content[row++ * g->width], line, g->width);
    }
}
void grid_print(grid* g) {
    for (int i = 0; i < g->height; i++) {
        for (int j = 0; j < g->width; j++) {
            coord c = {i, j};
            printf("%c ", grid_get_at_coord(g, c));
        }
        printf("\n");
    }
    printf("\n");
}

inline int grid_size(grid* g) { return g->width * g->height; }

inline char grid_get_at_coord(grid* g, coord c) {
    return g->content[grid_1d_from_coord(g, c)];
}

inline void grid_set_at_coord(grid* g, coord c, char x) {
    g->content[grid_1d_from_coord(g, c)] = x;
}

int grid_count(grid* g, char x) {
    int count = 0;
    for (int i = 0; i < grid_size(g); i++) {
        if (g->content[i] == x) {
            count++;
        }
    }
    return count;
}

coord grid_coord_from_1d(grid* g, int index) {
    coord out = {.row = (int)(index / g->width),
                 .col = (int)(index % g->width)};
    return out;
}

inline int grid_1d_from_coord(grid* g, coord c) {
    int test = c.row * g->width + c.col;
    return c.row * g->width + c.col;
}

bool grid_coord_in_bounds(grid* g, coord c) {
    if (c.row < 0 || c.row >= g->height) {
        return false;
    }

    if (c.col < 0 || c.col >= g->width) {
        return false;
    }

    return true;
}

inline bool coord_eq(coord c1, coord c2) {
    return c1.row == c2.row && c1.col == c2.col;
}

coord coord_plus(coord c1, coord c2) {
    coord out = {.row = c1.row + c2.row, .col = c1.col + c2.col};
    return out;
}

coord coord_minus(coord c1, coord c2) {
    coord out = {.row = c1.row - c2.row, .col = c1.col - c2.col};
    return out;
}

coord coord_times(coord c, int a) {
    coord out = {.row = c.row * a, .col = c.col * a};
    return out;
}