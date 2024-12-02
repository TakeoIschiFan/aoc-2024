#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void bubble_sort(int* arr, unsigned int size){
    for(unsigned int i = 0; i < size-1; i++){
        for(unsigned int j = 0; j < size - i - 1; j++){
            if (arr[j] > arr[j+1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int part_a(FILE* txt) {
    char line[16];

    int left[1000];
    int right[1000];

    unsigned int idx = 0;

    while (fgets(line, sizeof(line), txt) != NULL) {
        int l;
        int r;

        sscanf(line, "%d   %d", &l, &r);

        left[idx] = l;
        right[idx] = r;
        idx++;
    }

    bubble_sort(left, 1000);
    bubble_sort(right, 1000);

    int sum = 0;

    for (int i = 0; i < 1000; i++){
        sum += abs(left[i] - right[i]);

    }

    return sum;

}

int part_b(FILE* txt) {
    char line[16];

    int left[1000];
    int right[1000];

    unsigned int idx = 0;

    while (fgets(line, sizeof(line), txt) != NULL) {
        int l;
        int r;

        sscanf(line, "%d   %d", &l, &r);

        left[idx] = l;
        right[idx] = r;
        idx++;
    }

    int sim = 0;

    for (int i = 0; i < 1000; i++){
        int occ = 0;
        for (int j = 0; j < 1000; j++){
            if (right[j] == left[i]){
                occ++;
            }

        }
        sim += (occ * left[i]);
    }

    return sim;
}

int main(void) {
    // open file
    FILE* txt = fopen("day1/input.txt", "r");

    int answer_a = part_a(txt);
    printf("part a: %d\n", answer_a);
    rewind(txt);
    int answer_b = part_b(txt);
    printf("part b: %d\n", answer_b);

    fclose(txt);


    return 0;
}
