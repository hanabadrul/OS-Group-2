#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAGES 50
#define MAX_FRAMES 10
#define BUFFER_SIZE 256

int main() {
    int reference_string[MAX_PAGES];
    int frames[MAX_FRAMES];
    int total_pages, total_frames;
    int page_faults = 0, page_hits = 0;
    int index_to_replace = 0;

    char input[BUFFER_SIZE];

    // =========================
    // INPUT NUMBER OF FRAMES
    // =========================
    while (1) {
        printf("Enter number of Frames (Max %d): ", MAX_FRAMES);

        if (fgets(input, sizeof(input), stdin) == NULL)
            continue;

        if (sscanf(input, "%d", &total_frames) == 1 &&
            total_frames > 0 &&
            total_frames <= MAX_FRAMES) {
            break;
        }

        printf("Invalid input! Please enter integer only.\n\n");
    }

    // =========================
    // INPUT NUMBER OF PAGES
    // =========================
    while (1) {
        printf("Enter number of Pages (Max %d): ", MAX_PAGES);

        if (fgets(input, sizeof(input), stdin) == NULL)
            continue;

        if (sscanf(input, "%d", &total_pages) == 1 &&
            total_pages > 0 &&
            total_pages <= MAX_PAGES) {
            break;
        }

        printf("Invalid input! Please enter integer only.\n\n");
    }

    // =========================
    // INPUT REFERENCE STRING
    // =========================
    while (1) {

        int count = 0;
        char *token;

        printf("Enter the Page Reference String : ");

        if (fgets(input, sizeof(input), stdin) == NULL)
            continue;

        // Remove newline
        input[strcspn(input, "\n")] = '\0';

        // Tokenize input
        token = strtok(input, " ");

        int valid = 1;

        while (token != NULL) {

            // Check if token is integer
            char extra;
            int page;

            if (sscanf(token, "%d%c", &page, &extra) != 1) {
                valid = 0;
                break;
            }

            // Store page
            if (count < MAX_PAGES) {
                reference_string[count] = page;
            }

            count++;
            token = strtok(NULL, " ");
        }

        // Check validation
        if (!valid) {
            printf("Invalid input! Reference string must contain integers only.\n\n");
            continue;
        }

        // Check if number entered exceeds total pages
        if (count != total_pages) {
            printf("Error! You must enter exactly %d page numbers.\n\n", total_pages);
            continue;
        }

        break;
    }

    // =========================
    // INITIALIZE FRAMES
    // =========================
    for (int i = 0; i < total_frames; i++) {
        frames[i] = -1;
    }

    // =========================
    // DISPLAY TABLE HEADER
    // =========================
    printf("\n+--------------+-----------------------+---------------+\n");
    printf("| Incoming Page| Memory Frames State   | Status        |\n");
    printf("+--------------+-----------------------+---------------+\n");

    // =========================
    // FIFO PAGE REPLACEMENT
    // =========================
    for (int i = 0; i < total_pages; i++) {

        int current_page = reference_string[i];
        int is_hit = 0;

        printf("|      %2d      | ", current_page);

        // Check HIT
        for (int j = 0; j < total_frames; j++) {
            if (frames[j] == current_page) {
                is_hit = 1;
                break;
            }
        }

        // PAGE HIT
        if (is_hit) {

            page_hits++;

            for (int j = 0; j < total_frames; j++) {
                if (frames[j] == -1)
                    printf(" -  ");
                else
                    printf("%2d  ", frames[j]);
            }

            for (int k = total_frames; k < 5; k++)
                printf("    ");

            printf("|   HIT         |\n");
        }

        // PAGE FAULT
        else {

            page_faults++;

            frames[index_to_replace] = current_page;

            index_to_replace =
                (index_to_replace + 1) % total_frames;

            for (int j = 0; j < total_frames; j++) {
                if (frames[j] == -1)
                    printf(" -  ");
                else
                    printf("%2d  ", frames[j]);
            }

            for (int k = total_frames; k < 5; k++)
                printf("    ");

            printf("|   FAULT (*)   |\n");
        }
    }

    printf("+--------------+-----------------------+---------------+\n");

    // =========================
    // FINAL RESULTS
    // =========================
    printf(" Total Page Requests : %d\n", total_pages);
    printf(" Total Page Hits     : %d\n", page_hits);
    printf(" Total Page Faults   : %d\n", page_faults);

    printf("--------------------------------------------------\n");

    printf(" Hit Ratio           : %.2f%%\n",
           ((float)page_hits / total_pages) * 100);

    printf(" Fault Ratio         : %.2f%%\n",
           ((float)page_faults / total_pages) * 100);

    printf("==================================================\n");

    return 0;
}