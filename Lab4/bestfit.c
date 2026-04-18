#include <stdio.h>

int main() {
    int n_blocks, n_processes;

    // 1. Get the memory blocks from the user
    printf("Enter the number of memory blocks: ");
    scanf("%d", &n_blocks);
    
    int blocks[n_blocks];
    int occupied[n_blocks]; // Array to keep track of whether a block is free (0) or occupied (1)

    printf("Enter the size of each block:\n");
    for (int i = 0; i < n_blocks; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &blocks[i]);
        occupied[i] = 0; // Initialize all partitions as free
    }

    // 2. Get the process requirements from the user
    printf("\nEnter the number of processes: ");
    scanf("%d", &n_processes);
    
    int processes[n_processes];
    int allocation[n_processes]; // Array to store the block index allocated to each process

    printf("Enter the size of each process:\n");
    for (int i = 0; i < n_processes; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &processes[i]);
        allocation[i] = -1; // Initialize all processes as unallocated (-1)
    }

    // 3. Best-fit Allocation Logic
    for (int i = 0; i < n_processes; i++) {
        int best_idx = -1;
        
        // Scan all blocks to find the best fit for the current process
        for (int j = 0; j < n_blocks; j++) {
            // Check if the block is free AND large enough for the process
            if (occupied[j] == 0 && blocks[j] >= processes[i]) {
                // If it's the first suitable block found, or if it's smaller than the current best block
                if (best_idx == -1 || blocks[j] < blocks[best_idx]) {
                    best_idx = j;
                }
            }
        }

        // If a suitable block was found, allocate it
        if (best_idx != -1) {
            allocation[i] = best_idx;
            occupied[best_idx] = 1; // Mark the partition as occupied (one process per partition)
        }
    }

    // 4. Display the results in a table format
    printf("\n--- Best-Fit Allocation Results ---\n");
    printf("%-15s %-15s %-15s %-15s\n", "Process No.", "Process Size", "Block No.", "Block Size");
    for (int i = 0; i < n_processes; i++) {
        // Print the first two columns (Process No. and Process Size)
        printf("%-15d %-15d ", i + 1, processes[i]);
        if (allocation[i] != -1) {
            // Print the allocated block details
            printf("%-15d %-15d\n", allocation[i] + 1, blocks[allocation[i]]);
        } else {
            // Print the unallocated status
            printf("%-15s %-15s\n", "Not Allocated", "---");
        }
    }

    return 0;
}