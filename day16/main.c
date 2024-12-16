
#include "../common/grid.h"
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TILE_SIZE 17

typedef enum direction {
    UP = 1 << 0,
    LEFT = 1 << 1,
    DOWN = 1 << 2,
    RIGHT = 1 << 3
} direction;

int part_a(FILE* txt) {
    grid* g = grid_create(TILE_SIZE, TILE_SIZE);
    grid_load(g, txt);

    int start = grid_1d_from_coord(g, grid_find_first(g, 'S'));
    int end = grid_1d_from_coord(g, grid_find_first(g, 'E'));

    // we implement Dijkstra's algorithm here
    int distance_from_start[TILE_SIZE * TILE_SIZE];
    direction dirs[TILE_SIZE * TILE_SIZE];
    bool visited[TILE_SIZE * TILE_SIZE];
    int best_path[TILE_SIZE * TILE_SIZE];
    int best_path_length = 0;

    // set all initial distances to infinity except for the start node
    for (int i = 0; i < grid_size(g); i++) {
        if (i == start) {
            distance_from_start[i] = 0;
            dirs[i] = RIGHT;
        } else {
            distance_from_start[i] = INT_MAX;
        }
        visited[i] = false;
    }

    int node = -1;
    int its = 0;

    while (!(node == end)) {

        // grab the next node, which is the node with the smallest distance that
        // we have not visited yet
        int next_node = node;
        while (next_node == node) {
            int min_distance = INT_MAX;
            int min_node = -1;
            for (int i = 0; i < TILE_SIZE * TILE_SIZE; i++) {
                if (distance_from_start[i] < min_distance && !visited[i]) {
                    min_distance = distance_from_start[i];
                    min_node = i;
                }
            }
            next_node = min_node;
        }
        printf("next node: %d, total distance %d \n", next_node,
               distance_from_start[next_node]);

        // end condition
        if (next_node == end) {
            return distance_from_start[next_node];
        }

        // we consider stepping in all directions
        int left = next_node - 1;
        if (!(grid_get_at_1d(g, left) == '#')) {
            if (!(visited[left])) {
                if (dirs[next_node] == LEFT) {
                    int dist = distance_from_start[next_node] + 1;
                    if (dist < distance_from_start[left]) {
                        distance_from_start[left] = dist;
                        dirs[left] = LEFT;
                    }
                } else {
                    int dist = distance_from_start[next_node] + 1001;
                    if (dist < distance_from_start[left]) {
                        distance_from_start[left] = dist;
                        dirs[left] = LEFT;
                    }
                }
            }
        }

        int right = next_node + 1;
        if (!(grid_get_at_1d(g, right) == '#')) {
            if (!(visited[right])) {
                if (dirs[next_node] == RIGHT) {
                    int dist = distance_from_start[next_node] + 1;
                    if (dist < distance_from_start[right]) {
                        distance_from_start[right] = dist;
                        dirs[right] = RIGHT;
                    }

                } else {
                    int dist = distance_from_start[next_node] + 1001;
                    if (dist < distance_from_start[right]) {
                        distance_from_start[right] = dist;
                        dirs[right] = RIGHT;
                    }
                }
            }
        }

        int up = next_node - TILE_SIZE;
        if (!(grid_get_at_1d(g, up) == '#')) {
            if (!(visited[up])) {
                if (dirs[next_node] == UP) {
                    int dist = distance_from_start[next_node] + 1;
                    if (dist < distance_from_start[up]) {
                        distance_from_start[up] = dist;
                        dirs[up] = UP;
                    }

                } else {
                    int dist = distance_from_start[next_node] + 1001;
                    if (dist < distance_from_start[up]) {
                        distance_from_start[up] = dist;
                        dirs[up] = UP;
                    }
                }
            }
        }

        int down = next_node + TILE_SIZE;
        if (!(grid_get_at_1d(g, down) == '#')) {
            if (!(visited[down])) {
                if (dirs[next_node] == DOWN) {
                    int dist = distance_from_start[next_node] + 1;
                    if (dist < distance_from_start[down]) {
                        distance_from_start[down] = dist;
                        dirs[down] = DOWN;
                    }

                } else {
                    int dist = distance_from_start[next_node] + 1001;
                    if (dist < distance_from_start[down]) {
                        distance_from_start[down] = dist;
                        dirs[down] = DOWN;
                    }
                }
            }
        }

        visited[next_node] = true;
        node = next_node;
        its++;
        best_path[best_path_length++] = next_node;
    }

    return -1;
}

void visit_backwards(void) {}

long part_b(FILE* txt) {
    grid* g = grid_create(TILE_SIZE, TILE_SIZE);
    grid_load(g, txt);

    int start = grid_1d_from_coord(g, grid_find_first(g, 'S'));
    int end = grid_1d_from_coord(g, grid_find_first(g, 'E'));

    // we implement Dijkstra's algorithm here
    int distance_from_start[TILE_SIZE * TILE_SIZE];
    direction dirs[TILE_SIZE * TILE_SIZE];
    bool visited[TILE_SIZE * TILE_SIZE];
    int best_path[TILE_SIZE * TILE_SIZE];
    int best_path_length = 0;

    // set all initial distances to infinity except for the start node
    for (int i = 0; i < grid_size(g); i++) {
        if (i == start) {
            distance_from_start[i] = 0;
            dirs[i] = RIGHT;
        } else {
            distance_from_start[i] = INT_MAX;
        }
        visited[i] = false;
    }

    int node = -1;
    int its = 0;

    while (!(node == end)) {

        // grab the next node, which is the node with the smallest distance that
        // we have not visited yet
        int next_node = node;
        while (next_node == node) {
            int min_distance = INT_MAX;
            int min_node = -1;
            for (int i = 0; i < TILE_SIZE * TILE_SIZE; i++) {
                if (distance_from_start[i] < min_distance && !visited[i]) {
                    min_distance = distance_from_start[i];
                    min_node = i;
                }
            }
            next_node = min_node;
        }
        printf("next node: %d, total distance %d \n", next_node,
               distance_from_start[next_node]);

        // end condition
        if (next_node == end) {
            break;
        }

        // we consider stepping in all directions
        int left = next_node - 1;
        if (!(grid_get_at_1d(g, left) == '#')) {
            if (!(visited[left])) {
                if (dirs[next_node] == LEFT) {
                    int dist = distance_from_start[next_node] + 1;
                    if (dist < distance_from_start[left]) {
                        distance_from_start[left] = dist;
                        dirs[left] = LEFT;
                    }
                } else {
                    int dist = distance_from_start[next_node] + 1001;
                    if (dist < distance_from_start[left]) {
                        distance_from_start[left] = dist;
                        dirs[left] = LEFT;
                    }
                }
            }
        }

        int right = next_node + 1;
        if (!(grid_get_at_1d(g, right) == '#')) {
            if (!(visited[right])) {
                if (dirs[next_node] == RIGHT) {
                    int dist = distance_from_start[next_node] + 1;
                    if (dist < distance_from_start[right]) {
                        distance_from_start[right] = dist;
                        dirs[right] = RIGHT;
                    }

                } else {
                    int dist = distance_from_start[next_node] + 1001;
                    if (dist < distance_from_start[right]) {
                        distance_from_start[right] = dist;
                        dirs[right] = RIGHT;
                    }
                }
            }
        }

        int up = next_node - TILE_SIZE;
        if (!(grid_get_at_1d(g, up) == '#')) {
            if (!(visited[up])) {
                if (dirs[next_node] == UP) {
                    int dist = distance_from_start[next_node] + 1;
                    if (dist < distance_from_start[up]) {
                        distance_from_start[up] = dist;
                        dirs[up] = UP;
                    }

                } else {
                    int dist = distance_from_start[next_node] + 1001;
                    if (dist < distance_from_start[up]) {
                        distance_from_start[up] = dist;
                        dirs[up] = UP;
                    }
                }
            }
        }

        int down = next_node + TILE_SIZE;
        if (!(grid_get_at_1d(g, down) == '#')) {
            if (!(visited[down])) {
                if (dirs[next_node] == DOWN) {
                    int dist = distance_from_start[next_node] + 1;
                    if (dist < distance_from_start[down]) {
                        distance_from_start[down] = dist;
                        dirs[down] = DOWN;
                    }

                } else {
                    int dist = distance_from_start[next_node] + 1001;
                    if (dist < distance_from_start[down]) {
                        distance_from_start[down] = dist;
                        dirs[down] = DOWN;
                    }
                }
            }
        }

        visited[next_node] = true;
        node = next_node;
        its++;
        best_path[best_path_length++] = next_node;
    }

    // Credit to aadi312 on reddit
    // Part 2: Start backtracking from the answer node to start node, only visit
    // those which have either score of (score - 1) or (score - 1001)

    visit_backwards();
    return -1;
}

int main(void) {
    FILE* txt = fopen("day16/test.txt", "r");

    int answer_a = part_a(txt);
    printf("Part A: %d\n", answer_a);
    rewind(txt);
    long answer_b = part_b(txt);
    printf("Part B: %ld\n", answer_b);

    fclose(txt);
    return 0;
}
