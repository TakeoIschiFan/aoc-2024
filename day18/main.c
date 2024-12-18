
#include "../common/grid.h"
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TILE_SIZE 71
#define NUM_FALLS 1024

int part_a(FILE* txt) {
    grid* g = grid_create_with(TILE_SIZE, TILE_SIZE, '.');

    char line[32];
    int falls = 0;

    while (fgets(line, sizeof(line), txt) && falls < NUM_FALLS) {
        int x, y = 0;
        sscanf(line, "%d, %d", &y, &x);
        grid_set_at_coord(g, (coord){x, y}, '#');
        falls++;
    }

    grid_print(g);

    // now do dijkstra

    int start = 0;
    int end = TILE_SIZE * TILE_SIZE - 1;

    // we implement Dijkstra's algorithm here
    int distance_from_start[TILE_SIZE * TILE_SIZE];
    bool visited[TILE_SIZE * TILE_SIZE];
    int best_path[TILE_SIZE * TILE_SIZE];
    int best_path_length = 0;

    // set all initial distances to infinity except for the start node
    for (int i = 0; i < grid_size(g); i++) {
        if (i == start) {
            distance_from_start[i] = 0;
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
        if (!(next_node % TILE_SIZE == 0) & !(grid_get_at_1d(g, left) == '#')) {
            if (!(visited[left])) {
                int dist = distance_from_start[next_node] + 1;
                if (dist < distance_from_start[left]) {
                    distance_from_start[left] = dist;
                }
            }
        }

        int right = next_node + 1;
        if (!(right % TILE_SIZE == 0) && !(grid_get_at_1d(g, right) == '#')) {
            if (!(visited[right])) {
                int dist = distance_from_start[next_node] + 1;
                if (dist < distance_from_start[right]) {
                    distance_from_start[right] = dist;
                }
            }
        }

        int up = next_node - TILE_SIZE;
        if (up >= 0 && !(grid_get_at_1d(g, up) == '#')) {
            if (!(visited[up])) {
                int dist = distance_from_start[next_node] + 1;
                if (dist < distance_from_start[up]) {
                    distance_from_start[up] = dist;
                }
            }
        }

        int down = next_node + TILE_SIZE;
        if (down < TILE_SIZE * TILE_SIZE && !(grid_get_at_1d(g, down) == '#')) {
            if (!(visited[down])) {
                int dist = distance_from_start[next_node] + 1;
                if (dist < distance_from_start[down]) {
                    distance_from_start[down] = dist;
                }
            }
        }

        visited[next_node] = true;
        node = next_node;
        best_path[best_path_length++] = next_node;
    }
    grid_free(g);
    return best_path_length;
}

void visit_backwards(void) {}

long part_b(FILE* txt) {
    grid* g = grid_create_with(TILE_SIZE, TILE_SIZE, '.');

    char line[32];

    // now do dijkstra
    for (int f = 0; f < INT_MAX; f++) {
        printf("Letting block %d fall\n", f + 1);
        fgets(line, sizeof(line), txt);
        int x, y = 0;
        sscanf(line, "%d, %d", &y, &x);
        grid_set_at_coord(g, (coord){x, y}, '#');

        int start = 0;
        int end = TILE_SIZE * TILE_SIZE - 1;

        // we implement Dijkstra's algorithm here
        int distance_from_start[TILE_SIZE * TILE_SIZE];
        bool visited[TILE_SIZE * TILE_SIZE];
        int best_path[TILE_SIZE * TILE_SIZE];
        int best_path_length = 0;

        // set all initial distances to infinity except for the start node
        for (int i = 0; i < grid_size(g); i++) {
            if (i == start) {
                distance_from_start[i] = 0;
            } else {
                distance_from_start[i] = INT_MAX;
            }
            visited[i] = false;
        }

        int node = -1;
        int its = 0;

        while (!(node == end)) {

            // grab the next node, which is the node with the smallest distance
            // that we have not visited yet
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
            // printf("next node: %d, total distance %d \n", next_node,
            //       distance_from_start[next_node]);

            // end condition
            if (next_node == end) {
                break;
            }

            // we consider stepping in all directions
            int left = next_node - 1;
            if (!(next_node % TILE_SIZE == 0) &
                !(grid_get_at_1d(g, left) == '#')) {
                if (!(visited[left])) {
                    int dist = distance_from_start[next_node] + 1;
                    if (dist < distance_from_start[left]) {
                        distance_from_start[left] = dist;
                    }
                }
            }

            int right = next_node + 1;
            if (!(right % TILE_SIZE == 0) &&
                !(grid_get_at_1d(g, right) == '#')) {
                if (!(visited[right])) {
                    int dist = distance_from_start[next_node] + 1;
                    if (dist < distance_from_start[right]) {
                        distance_from_start[right] = dist;
                    }
                }
            }

            int up = next_node - TILE_SIZE;
            if (up >= 0 && !(grid_get_at_1d(g, up) == '#')) {
                if (!(visited[up])) {
                    int dist = distance_from_start[next_node] + 1;
                    if (dist < distance_from_start[up]) {
                        distance_from_start[up] = dist;
                    }
                }
            }

            int down = next_node + TILE_SIZE;
            if (down < TILE_SIZE * TILE_SIZE &&
                !(grid_get_at_1d(g, down) == '#')) {
                if (!(visited[down])) {
                    int dist = distance_from_start[next_node] + 1;
                    if (dist < distance_from_start[down]) {
                        distance_from_start[down] = dist;
                    }
                }
            }

            visited[next_node] = true;
            node = next_node;
            best_path[best_path_length++] = next_node;
        }
        printf("best path length %d\n", best_path_length);
    }
    grid_free(g);
    return -1;
}

int main(void) {
    FILE* txt = fopen("day18/input.txt", "r");

    int answer_a = part_a(txt);
    printf("Part A: %d\n", answer_a);
    rewind(txt);
    long answer_b = part_b(txt);
    printf("Part B: %ld\n", answer_b);

    fclose(txt);
    return 0;
}
