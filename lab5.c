#include <stdio.h>
#define MAX 25

int main() {
    int fragment[MAX], b[MAX], p[MAX], bf[MAX], pf[MAX];
    int nb, np, temp, lowest = 9999;
    static int barray[MAX], parray[MAX];

    printf("\n\t\t-------- FIRST FIT MEMORY ALLOCATION --------\n");

    printf("\nEnter the number of memory blocks: ");
    scanf("%d", &nb);
    printf("Enter the number of processes: ");
    scanf("%d", &np);

    printf("\nEnter the size of each memory block:\n");
    for (int i = 1; i <= nb; i++) {
        printf("  Block %d: ", i);
        scanf("%d", &b[i]);
    }

    printf("\nEnter the size of each process:\n");
    for (int i = 1; i <= np; i++) {
        printf("  Process %d: ", i);
        scanf("%d", &p[i]);
    }

    /* 
     * for each process, scan blocks from left to right
     * assign the 1st block where block size >= process size
     * mark that block as used so it won't be reused
     */

    for (int i = 1; i <= np; i++) {
        for (int j = 1; j <= nb; j++) {
            if (barray[j] == 0 && b[j] >= p[i]) {
                pf[i] = j;                    // record which block was assigned
                fragment[i] = b[j] - p[i];   // internal fragmentation = leftover space
                barray[j] = 1;               // mark block as occupied
                break;                        // stop at the FIRST suitable block
            }
        }
    }

    /* --- OUTPUT TABLE ---
     * display each process, its assigned block, sizes, and fragmentation
     * processes that couldnt be allocated show "Not Allocated"
     */

    printf("\n\nProcess No.\tProcess Size\tBlock No.\tBlock Size\tFragment\n");
    for (int i = 1; i <= np; i++) {
        if (pf[i] != 0) {
            printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
                   i, p[i], pf[i], b[pf[i]], fragment[i]);
        } else {
            printf("%d\t\t%d\t\tNot Allocated\n", i, p[i]);
        }
    }

    return 0;
}