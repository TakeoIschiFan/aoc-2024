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
void grid_free(grid* g);
void grid_load(grid* g, FILE* txt);
void grid_print(grid* g);

int grid_size(grid* g);

char grid_get_at_coord(grid* g, coord c);
void grid_set_at_coord(grid* g, coord c, char x);
int grid_count(grid* g, char x);

coord grid_coord_from_1d(grid* g, int index);
int grid_1d_from_coord(grid* g, coord c);
bool grid_coord_in_bounds(grid* g, coord c);

bool coord_eq(coord c1, coord c2);
coord coord_plus(coord c1, coord c2);
coord coord_minus(coord c1, coord c2);
coord coord_times(coord c, int a);