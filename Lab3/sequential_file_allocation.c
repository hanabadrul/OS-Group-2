#include <stdio.h>

struct Directory {
    char filename[20]; // file identifier, max 19 chars + null terminator '\0'
    int start_index; // first block occupied by this file on the disk
    int length; // number of contiguous blocks the file occupies
};

// Prompts user for file info and validates input.
// Returns 0 on success, 1 if allocation would collide or exceed bounds.
int inputLoop(int size, int volume[size], int sizeDirectory, struct Directory directoryTable[sizeDirectory],
              int lastDirectory);

// Checks if [start_index, start_index + length) overlaps any occupied block.
// Returns 1 if collision detected, 0 if the range is free.
int is_collide(int size, const int volume[size], int start_index, int length);

// Marks all blocks in the file's range as occupied (1) in volume[].
void sequentialAllocation(int size, int volume[size], int sizeDirectory, struct Directory directoryTable[sizeDirectory],
                          int lastDirectory);

// Prints the raw block grid and the current directory table to stdout.
void visualization(int size, int volume[size], int sizeDirectory, struct Directory directoryTable[sizeDirectory],
                   int lastDirectory);

// filename start_index len
int main() {
    // Total number of blocks on the simulated disk
    // Each index in volume[] represents one allocatable block
    const int size = 64;
    int volume[64] = {0};

    // Maximum number of files the directory can track
    // Simulates a fixed-size directory table (like FAT)
    int sizeDirectory = 10;
    struct Directory directoryTable[sizeDirectory] = {};

    // Index of the next empty slot in directoryTable[]
    // Acts as both a counter and a pointer to the last entry
    int lastDirectory = 0;

    while (1) {
        int menu;
        printf("Press 1 to Add a File. Press 2 to Exit.");
        scanf("%d", &menu);

        // Any input other than 1 exits the simulation
        if (menu != 1) {
            break;
        }

        // Guard: prevent writing beyond the directory table bounds
        if (lastDirectory >= sizeDirectory) {
            printf("Directory exceeds the limit.\n");
            break;
        }

        // Get and validate user input; skip allocation if input is invalid
        if (inputLoop(size, volume, sizeDirectory, directoryTable, lastDirectory) == 1) {
            continue;
        }

        // Allocate the file contiguously on the disk and confirm to user
        sequentialAllocation(size, volume, sizeDirectory, directoryTable, lastDirectory);
        printf("Files %s Allocated.\n", directoryTable[lastDirectory].filename);

        // Advance to the next free directory slot
        lastDirectory++;

        // Show updated disk state after each successful allocation
        visualization(size, volume, sizeDirectory, directoryTable, lastDirectory);
    }

    return 0;
}

int inputLoop(const int size, int volume[size], int sizeDirectory, struct Directory directoryTable[sizeDirectory],
              const int lastDirectory) {
    printf("Enter the name of the files:");
    scanf("%19s", directoryTable[lastDirectory].filename);

    int length = 0;
    do {
        printf("Enter the length of the files:");
        scanf("%d", &length);
        if (length >= size) {
            printf("Length exceeds the limit.\n");
        }
        if (length <= 0) {
            printf("Length must bigger than 0.\n");
        }
    } while (length >= size || length <= 0);

    int start_index = 0;
    printf("Enter the start index of files:");
    scanf("%d", &start_index);

    if (is_collide(size, volume, start_index, length)) {
        printf("Failed to allocate.\n");
        return 1;
    }

    directoryTable[lastDirectory].length = length;
    directoryTable[lastDirectory].start_index = start_index;

    return 0;
}

int is_collide(const int size, const int volume[size], const int start_index, const int length) {
    const int totalFileSize = start_index + length;
    if (totalFileSize > size) return 1;
    for (int i = start_index; i < totalFileSize; i++) {
        if (volume[i] == 1) return 1;
    }
    return 0;
}

void sequentialAllocation(int size, int volume[size], int sizeDirectory, struct Directory directoryTable[sizeDirectory],
                          const int lastDirectory) {
    for (int i = directoryTable[lastDirectory].start_index;
         i < directoryTable[lastDirectory].start_index + directoryTable[lastDirectory].length; i++) {
        volume[i] = 1;
    }
}

void visualization(const int size, int volume[size], int sizeDirectory, struct Directory directoryTable[sizeDirectory],
                   const int lastDirectory) {
    printf("Volume Visualization: \n");
    for (int i = 0; i < size; i++) {
        printf("%d ", volume[i]);
        if ((i + 1) % 8 == 0) {
            printf("\n");
        }
    }

    printf("File Directory Visualization: \n");
    for (int i = 0; i < lastDirectory; i++) {
        printf("%s %d %d\n", directoryTable[i].filename, directoryTable[i].start_index, directoryTable[i].length);
    }
}
