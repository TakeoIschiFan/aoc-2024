
#include "../common/grid.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <stdbool.h>
#include <stdio.h>

#define TILE_WIDTH 101
#define TILE_HEIGHT 103
#define STEPS 100

int part_a(FILE* txt) {

    char line[256];

    // parse input
    coord coords[500] = {0};
    coord vels[500] = {0};
    int coord_count = 0;

    while (fgets(line, sizeof(line), txt)) {
        int x = 0;
        int y = 0;
        int vx = 0;
        int vy = 0;
        sscanf(line, "p=%d,%d v=%d,%d", &x, &y, &vx, &vy);
        coords[coord_count] = (coord){y, x};
        vels[coord_count++] = (coord){vy, vx};
    }
    printf("parsed %d lines\n", coord_count);

    // simulate game
    for (int s = 0; s < STEPS; s++) {
        for (int i = 0; i < coord_count; i++) {
            coord newpos = coord_plus(coords[i], vels[i]);
            coords[i] = coord_modulo(newpos, TILE_HEIGHT, TILE_WIDTH);
        }
    }

    // aggregate results
    int q1 = 0;
    int q2 = 0;
    int q3 = 0;
    int q4 = 0;

    for (int y = 0; y < TILE_HEIGHT; y++) {
        for (int x = 0; x < TILE_WIDTH; x++) {
            coord loc = {y, x};
            int amount = 0;
            for (int i = 0; i < coord_count; i++) {
                if (coord_eq(loc, coords[i])) {
                    amount++;
                }
            }
            printf("%d ", amount);

            if (amount == 0) {
                continue;
            }

            // add the amount to the correct quadrant
            if (y < TILE_HEIGHT / 2) {
                if (x < TILE_WIDTH / 2) {
                    q2 += amount;
                } else if (x > TILE_WIDTH / 2) {
                    q1 += amount;
                }
            }
            if (y > TILE_HEIGHT / 2) {
                if (x < TILE_WIDTH / 2) {
                    q3 += amount;
                } else if (x > TILE_WIDTH / 2) {
                    q4 += amount;
                }
            }
        }
        printf("\n");
    }

    return q1 * q2 * q3 * q4;
}

long part_b(FILE* txt) {
    char line[256];

    // parse input
    coord coords[500] = {0};
    coord vels[500] = {0};
    int coord_count = 0;

    while (fgets(line, sizeof(line), txt)) {
        int x = 0;
        int y = 0;
        int vx = 0;
        int vy = 0;
        sscanf(line, "p=%d,%d v=%d,%d", &x, &y, &vx, &vy);
        coords[coord_count] = (coord){y, x};
        vels[coord_count++] = (coord){vy, vx};
    }
    printf("parsed %d lines\n", coord_count);

    // simulate game
    for (int s = 0; s < 10000; s++) {

        unsigned char output_buf[TILE_HEIGHT * TILE_WIDTH] = {0};
        for (int i = 0; i < coord_count; i++) {
            coord newpos = coord_plus(coords[i], vels[i]);
            coords[i] = coord_modulo(newpos, TILE_HEIGHT, TILE_WIDTH);
            output_buf[coords[i].row * TILE_WIDTH + coords[i].col] =
                (unsigned char)255;
        }

        char file_path[64];
        sprintf(file_path, "./day14frame/frame-%d.bmp", s + 1);
        stbi_write_bmp(file_path, TILE_WIDTH, TILE_HEIGHT, 1, output_buf);
    }
    return 0;
}

int main(void) {
    FILE* txt = fopen("day14/input.txt", "r");

    int answer_a = part_a(txt);
    printf("Part A: %d\n", answer_a);
    rewind(txt);
    long answer_b = part_b(txt);
    printf("Part B: %ld\n", answer_b);

    fclose(txt);
    return 0;
}
