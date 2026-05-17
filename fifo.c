#include <stdio.h>

#define MAX_PAGES 50
#define MAX_FRAMES 10

int main() {
    int reference_string[MAX_PAGES];
    int frames[MAX_FRAMES];
    int total_pages, total_frames;
    int page_faults = 0, page_hits = 0;
    int index_to_replace = 0; // Pointer to track the oldest page position for FIFO replacement

    // Get number of frames from user
    printf("Enter number of Frames (Max %d): ", MAX_FRAMES);
    scanf("%d", &total_frames);

    // Get total number of pages from user
    printf("Enter number of Pages (Max %d): ", MAX_PAGES);
    scanf("%d", &total_pages);

    // Get the page numbers sequence on a single line
    printf("Enter the Page Reference String : ");
    for (int i = 0; i < total_pages; i++) {
        scanf("%d", &reference_string[i]);
    }

    // Initialize all memory frames to -1 to represent empty slots
    for (int i = 0; i < total_frames; i++) {
        frames[i] = -1; 
    }

    // Display table headers for simulation tracking
    printf("\n+--------------+-----------------------+---------------+\n");
    printf("| Incoming Page| Memory Frames State   | Status        |\n");
    printf("+--------------+-----------------------+---------------+\n");

    // Loop through each page in the reference string
    for (int i = 0; i < total_pages; i++) {
        int current_page = reference_string[i];
        int is_hit = 0; // Flag to track if page is found in memory

        // Print current incoming page number
        printf("|      %2d      | ", current_page);

        // Check if the current page is already inside any of the memory frames
        for (int j = 0; j < total_frames; j++) {
            if (frames[j] == current_page) {
                is_hit = 1; // Page found (Hit)
                break;
            }
        }

        // If page is already in memory (Page Hit)
        if (is_hit == 1) {
            page_hits++; // Increment hit counter
            
            // Print the current state of frames
            for (int j = 0; j < total_frames; j++) {
                if (frames[j] == -1) printf(" -  ");
                else printf("%2d  ", frames[j]);
            }
            // Maintain column alignment in table output
            for (int k = total_frames; k < 5; k++) printf("    "); 

            printf("|   HIT         |\n");
        } 
        // If page is not in memory (Page Fault)
        else {
            page_faults++; // Increment fault counter
            
            // Place incoming page into the oldest frame slot
            frames[index_to_replace] = current_page;
            
            // Update replacement index circularly to point to the next oldest slot
            index_to_replace = (index_to_replace + 1) % total_frames;

            // Print the updated state of frames
            for (int j = 0; j < total_frames; j++) {
                if (frames[j] == -1) printf(" -  ");
                else printf("%2d  ", frames[j]);
            }
            for (int k = total_frames; k < 5; k++) printf("    ");

            printf("|   FAULT (*)   |\n");
        }
    }
    printf("+--------------+-----------------------+---------------+\n");

    // Display final performance results and metrics
    printf(" Total Page Requests : %d\n", total_pages);
    printf(" Total Page Hits     : %d\n", page_hits);
    printf(" Total Page Faults   : %d\n", page_faults);
    printf("--------------------------------------------------\n");
    printf(" Hit Ratio           : %.2f%%\n", ((float)page_hits / total_pages) * 100);
    printf(" Fault Ratio         : %.2f%%\n", ((float)page_faults / total_pages) * 100);
    printf("==================================================\n");

    return 0;
}