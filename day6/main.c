#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_ROWS 10
#define NUM_COLS 10

typedef enum direction { UP, LEFT, DOWN, RIGHT } direction;

direction turn_pos(direction d) {
    if (d == LEFT)
        return UP;
    if (d == UP)
        return RIGHT;
    if (d == RIGHT)
        return DOWN;
    if (d == DOWN)
        return LEFT;

    return -1; // Unreachable
}

int next_pos(int position, direction dir) {
    if (dir == LEFT) {
        if (position % NUM_COLS == 0)
            return -1;
        return position - 1;
    }
    if (dir == RIGHT) {
        if ((position + 1) % NUM_COLS == 0)
            return -1;
        return position + 1;
    }
    if (dir == UP) {
        if (position - NUM_COLS < 0)
            return -1;
        return position - NUM_COLS;
    }
    if (dir == DOWN) {
        if (position + NUM_COLS >= NUM_COLS * NUM_ROWS)
            return -1;
        return position + NUM_COLS;
    }
    return -1; // Unreachable
}

void print_board(bool* obstructions, int position, direction d) {
    printf("\nDirection: %d\n\n", d);
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            int loc = i * NUM_COLS + j;
            if (loc == position) {
                printf("X ");
            } else if (obstructions[loc]) {
                printf("# ");
            } else {
                printf(". ");
            }
        }
        printf("\n");
    }
}

void print_board_obstructions(bool* obstructions, int position, direction d) {
    printf("\nDirection: %d\n\n", d);
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            int loc = i * NUM_COLS + j;
            if (loc == position) {
                printf("X ");
            } else if (obstructions[loc]) {
                printf("# ");
            } else {
                printf(". ");
            }
        }
        printf("\n");
    }
}
int part_a(FILE* txt) {
    char line[256];

    bool obstructions[NUM_ROWS * NUM_COLS] = {0};
    int location;
    direction dir;
    unsigned int cur_line = 0;

    // Parse the playing field
    while (fgets(line, sizeof(line), txt) != NULL) {
        for (int i = 0; i < NUM_COLS; i++) {
            if (line[i] == '#') {
                obstructions[cur_line * NUM_COLS + i] = true;
            }
            if (line[i] == '>') {
                location = cur_line * NUM_COLS + i;
                dir = RIGHT;
            }
            if (line[i] == '^') {
                location = cur_line * NUM_COLS + i;
                dir = UP;
            }
            if (line[i] == '<') {
                location = cur_line * NUM_COLS + i;
                dir = LEFT;
            }
            if (line[i] == 'v') {
                location = cur_line * NUM_COLS + i;
                dir = DOWN;
            }
        }
        cur_line++;
    }

    // Play the game
    bool visited[NUM_ROWS * NUM_COLS] = {0};
    visited[location] = true;

    while (true) {
        // print_board(obstructions, location, dir);
        int tentative_pos = next_pos(location, dir);
        if (tentative_pos == -1) {
            // return the unique visited squares
            int sum = 0;
            for (int i = 0; i < NUM_ROWS * NUM_COLS; i++) {
                if (visited[i] == true) {
                    sum++;
                }
            }
            return sum;
        }

        if (obstructions[tentative_pos]) {
            dir = turn_pos(dir);
            continue;
        } else {
            location = tentative_pos;
            visited[location] = true;
        }
    }

    return -1; // Unreachable
}

int part_b(FILE* txt) {
    char line[256];

    bool obstructions[NUM_ROWS * NUM_COLS] = {0};
    int location;
    direction dir;
    unsigned int cur_line = 0;

    // Parse the playing field
    while (fgets(line, sizeof(line), txt) != NULL) {
        for (int i = 0; i < NUM_COLS; i++) {
            if (line[i] == '#') {
                obstructions[cur_line * NUM_COLS + i] = true;
            }
            if (line[i] == '>') {
                location = cur_line * NUM_COLS + i;
                dir = RIGHT;
            }
            if (line[i] == '^') {
                location = cur_line * NUM_COLS + i;
                dir = UP;
            }
            if (line[i] == '<') {
                location = cur_line * NUM_COLS + i;
                dir = LEFT;
            }
            if (line[i] == 'v') {
                location = cur_line * NUM_COLS + i;
                dir = DOWN;
            }
        }
        cur_line++;
    }

    // Play the game
    int starting_position = location;
    bool visited[NUM_ROWS * NUM_COLS] = {0};
    int direction_at_visited[NUM_ROWS * NUM_COLS] = {0};

    int new_obstructions = 0;

    while (true) {
        print_board(obstructions, location, dir);
        int tentative_pos = next_pos(location, dir);

        // if we exit the board
        if (tentative_pos == -1) {
            return new_obstructions;
        }

        // if we find an obstruction
        if (obstructions[tentative_pos]) {

            direction_at_visited[location] |= (1 << dir);
            dir = turn_pos(dir);
            continue;
        } else {

            // the rule for possible new obstructions is this
            // a) if tentative_pos is not an obstruction already
            // b) if tentative_pos is not the starting position
            // d) if a single turn at current_pos would turn us into the
            //      direction where we at some point
            //      start to overlap with a path we have already taken, in a
            //      direction we've already taken, without bumping into
            //      exisiting obstructions
            // then tentative_pos is a good new obstruction location.

            if (!(tentative_pos == starting_position)) {

                direction check_dir = turn_pos(dir);
                int check_pos = next_pos(location, check_dir);
                bool checking = true;

                while (checking) {
                    printf("%d ", direction_at_visited[check_pos]);
                    if (check_pos == -1) {
                        checking = false;
                    } else if (obstructions[check_pos]) {
                        checking = false;
                    } else if (visited[check_pos] &&
                               direction_at_visited[check_pos] &
                                   (1 << check_dir)) {
                        new_obstructions++;
                        printf("\n obstruction!");
                        checking = false;
                    }

                    check_pos = next_pos(check_pos, check_dir);
                }
            }
        }
        visited[location] = true;
        direction_at_visited[location] |= (1 << dir);
        location = tentative_pos;
    }
    return -1; // Unreachable
}

int main(void) {
    FILE* txt = fopen("day6/test.txt", "r");

    int answer_a = part_a(txt);
    printf("Part A: %d\n", answer_a);
    rewind(txt);
    int answer_b = part_b(txt);
    printf("Part B: %d\n", answer_b);

    fclose(txt);
    return 0;
}
