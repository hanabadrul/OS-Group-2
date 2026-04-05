#include <stdio.h>

int main() {
    // Matrix for storing Process Id, Burst Time, Waiting Time & Turn Around Time.
    // Column 0: Process ID (Used for FCFS tie-breaker)
    // Column 1: Burst Time (BT)
    // Column 2: Waiting Time (WT)
    // Column 3: Turn Around Time (TAT)
    int A[100][4];
    int i, j, n, total = 0, index, temp;
    float avg_wt, avg_tat;

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter Burst Time:\n");

    // 1. User Input Burst Time and alloting Process Id.
    for (i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d", &A[i][1]);
        A[i][0] = i + 1; // Assigning Process ID based on input order
    }

    // 2. Sorting processes according to their Burst Time (SJF Logic).
    // If Burst Times are equal, sort by Process ID (FCFS Logic).
    for (i = 0; i < n; i++) {
        index = i;
        for (j = i + 1; j < n; j++) {
            // Check for shortest job
            if (A[j][1] < A[index][1]) {
                index = j;
            } 
            // FCFS Tie-Breaker: If execution times are the same, check which arrived first (Lower Process ID)
            else if (A[j][1] == A[index][1]) {
                if (A[j][0] < A[index][0]) {
                    index = j;
                }
            }
        }
        
        // Swap Burst Time
        temp = A[i][1];
        A[i][1] = A[index][1];
        A[index][1] = temp;
        
        // Swap Process ID
        temp = A[i][0];
        A[i][0] = A[index][0];
        A[index][0] = temp;
    }

    // 3. Calculation of Waiting Times
    A[0][2] = 0; // First executed process has zero waiting time
    for (i = 1; i < n; i++) {
        A[i][2] = 0;
        for (j = 0; j < i; j++) {
            A[i][2] += A[j][1];
        }
        total += A[i][2];
    }
    
    avg_wt = (float)total / n;
    total = 0;
    
    printf("\n-----------------------------------\n");
    printf("Process    BT      WT      TAT\n");
    printf("-----------------------------------\n");

    // 4. Calculation of Turn Around Time and printing the data.
    for (i = 0; i < n; i++) {
        A[i][3] = A[i][1] + A[i][2]; // TAT = Burst Time + Waiting Time
        total += A[i][3];
        printf("  P%d       %d       %d       %d\n", A[i][0], A[i][1], A[i][2], A[i][3]);
    }

    avg_tat = (float)total / n;
    printf("-----------------------------------\n");
    printf("Average Waiting Time    = %.2f\n", avg_wt);
    printf("Average Turnaround Time = %.2f\n", avg_tat);

    return 0;
}