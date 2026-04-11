#include <stdio.h>

struct Directory {
    char filename[20];
    int start_index;
    int length;
};

int inputLoop(int size, int volume[size], int sizeDirectory, struct Directory directoryTable[sizeDirectory],
              int lastDirectory);

int is_collide(int size, const int volume[size], int start_index, int length);

void sequentialAllocation(int size, int volume[size], int sizeDirectory, struct Directory directoryTable[sizeDirectory],
                          int lastDirectory);

void visualization(int size, int volume[size], int sizeDirectory, struct Directory directoryTable[sizeDirectory],
                   int lastDirectory);

// filename start_index len
int main() {
    const int size = 64;
    int volume[64] = {0};
    int sizeDirectory = 10;
    struct Directory directoryTable[sizeDirectory] = {};
    int lastDirectory = 0;

    while (1) {
        int menu;
        printf("Press 1 to Add a File. Press 2 to Exit.");
        scanf("%d", &menu);
        if (menu != 1) {
            break;
        }

        if (lastDirectory >= sizeDirectory) {
            printf("Directory exceeds the limit.\n");
            break;
        }

        if (inputLoop(size, volume, sizeDirectory, directoryTable, lastDirectory) == 1) {
            continue;
        }

        sequentialAllocation(size, volume, sizeDirectory, directoryTable, lastDirectory);
        printf("Files %s Allocated.\n", directoryTable[lastDirectory].filename);

        lastDirectory++;

        visualization(size, volume, sizeDirectory, directoryTable, lastDirectory);
    }

    return 0;
}

int inputLoop(const int size, int volume[size], int sizeDirectory, struct Directory directoryTable[sizeDirectory],
              const int lastDirectory) {
    printf("Enter the name of the files:");
    scanf("%s", directoryTable[lastDirectory].filename);

    int length = 0;
    do {
        printf("Enter the length of the files:");
        scanf("%d", &length);
        if (length >= size) {
            printf("Length exceeds the limit.\n");
        }
    } while (length >= size);

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
