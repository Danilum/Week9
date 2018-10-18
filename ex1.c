#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <zconf.h>

int* frame_address;
int* frame_status;

void oldest_status(int VA, int frames_number){
    int old_page_index = 0;
    int old_page_age = 0;
    for (int i = 0; i < frames_number; i++) {
        if (frame_status[i] > old_page_age) {
            old_page_age = frame_status[i];
            old_page_index = i;
        }
    }
    frame_address[old_page_index] = VA;
    frame_status[old_page_index] = 0;
}

int aging_Algorithm(int VA, int frames_number) {
    for (int i = 0; i < frames_number; i++) {
        if (frame_status[i] != INT_MAX) {
            frame_status[i]++;
        }
    }
    for (int i = 0; i < frames_number; i++) {
        if (frame_address[i] == VA) {
            frame_status[i] = 0;
            return 0;
        }
    }
    oldest_status(VA, frames_number);
    return 1;
}

void start() {
    FILE* input_file;
    int n;
    printf("%s", "Number of page frames: ");
    scanf("%d", &n);

    frame_address = malloc(n*sizeof(int));
    frame_status = malloc(n*sizeof(int));

    for (int i = 0; i < n; i++) {
        frame_address[i] = -1;
        frame_status[i] = INT_MAX;
    }
    input_file = fopen("input.txt", "r");
    int arr[1000];
    int i = 0;
    int hit = 0;
    int miss = 0;

    while (fscanf(input_file, "%i", &(arr[i])) != EOF) {
        if (aging_Algorithm(arr[i], n) == 0) {
            hit++;
        } else {
            miss++;
        }
        i++;
    }
    fclose(input_file);
    printf("Hit: %d\n", hit);
    printf("Miss: %d\n", miss);
}

int main() {
    start();
    return 0;
}