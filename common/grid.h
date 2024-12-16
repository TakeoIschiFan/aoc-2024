#pragma once

#include <stdbool.h>
#include <stdio.h>

typedef struct {
    unsigned int width;
    unsigned int height;
    char* content;
} grid;

typedef struct {
    int row;
    int col;
} coord;

grid* grid_create(unsigned int width, unsigned int height);
grid* grid_create_with(unsigned int width, unsigned int height, char c);
void grid_free(grid* g);
void grid_load(grid* g, FILE* txt);
void grid_print(grid* g);

int grid_size(grid* g);

char grid_get_at_coord(grid* g, coord c);
char grid_get_at_1d(grid* g, int i);
void grid_set_at_coord(grid* g, coord c, char x);
int grid_get_int_at_coord(grid* g, coord c);
void grid_set_int_at_coord(grid* g, coord c, int x);
int grid_count(grid* g, char x);
coord grid_find_first(grid* g, char x);

// You get ownership of the string, free after done
char* grid_get_horizontal(grid* g, int row);
// You get ownership of the string, free after done
char* grid_get_vertical(grid* g, int col);

coord grid_coord_from_1d(grid* g, int index);
int grid_1d_from_coord(grid* g, coord c);
bool grid_coord_in_bounds(grid* g, coord c);
coord grid_coord_modulo_bounds(grid* g, coord c);

bool coord_eq(coord c1, coord c2);
coord coord_plus(coord c1, coord c2);
coord coord_minus(coord c1, coord c2);
coord coord_times(coord c, int a);
coord coord_modulo(coord c, int mod_x, int mod_y);
