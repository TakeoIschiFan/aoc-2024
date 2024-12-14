#include "grid.h"
#include <math.h>
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

grid* grid_create_with(unsigned int width, unsigned int height, char c) {
    char* contents = calloc(sizeof(char), width * height);
    grid* g = calloc(sizeof(grid), 1);
    g->width = width;
    g->height = height;
    g->content = contents;

    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            g->content[i * width + j] = c;
        }
    }
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
    for (unsigned int i = 0; i < g->height; i++) {
        for (unsigned int j = 0; j < g->width; j++) {
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

int grid_get_int_at_coord(grid* g, coord c) {
    return (int)(g->content[grid_1d_from_coord(g, c)] - '0');
}
void grid_set_int_at_coord(grid* g, coord c, int x) {
    g->content[grid_1d_from_coord(g, c)] = (char)(x + '0');
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

char* grid_get_horizontal(grid* g, int row) {
    char* line = malloc((g->width + 1) * sizeof(char));

    memcpy(line, &g->content[row * g->width], g->width);
    line[g->width] = '\0';

    return line;
}

char* grid_get_vertical(grid* g, int col) {
    char* column = malloc((g->height + 1) * sizeof(char));

    for (unsigned int i = 0; i < g->height; i++) {
        column[i] = g->content[i * g->width + col];
    }
    column[g->height] = '\0';
    return column;
}

coord grid_coord_from_1d(grid* g, int index) {
    coord out = {.row = (int)(index / g->width),
                 .col = (int)(index % g->width)};
    return out;
}

inline int grid_1d_from_coord(grid* g, coord c) {
    return c.row * g->width + c.col;
}

bool grid_coord_in_bounds(grid* g, coord c) {
    if (c.row < 0 || c.row >= (int)g->height) {
        return false;
    }

    if (c.col < 0 || c.col >= (int)g->width) {
        return false;
    }

    return true;
}

coord grid_coord_modulo_bounds(grid* g, coord c) {
    return (coord){c.row % (g->height - 1), c.col % (g->width - 1)};
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

int modulo(int x, int N) { return (x % N + N) % N; }

coord coord_modulo(coord c, int mod_row, int mod_col) {
    return (coord){modulo(c.row, mod_row), modulo(c.col, mod_col)};
}
