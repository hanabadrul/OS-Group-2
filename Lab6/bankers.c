#include <stdio.h>

#define MAX_P 10
#define MAX_R 10

int main() {
    int n, r, i, j, k;

    // how many processes are we dealing with?
    printf("Enter number of processes: ");
    scanf("%d", &n);
    if (n <= 0 || n > MAX_P) {
        printf("Error: processes must be between 1 and %d.\n", MAX_P);
        return 1;
    }

    // and how many resource types?
    printf("Enter number of resources: ");
    scanf("%d", &r);
    if (r <= 0 || r > MAX_R) {
        printf("Error: resources must be between 1 and %d.\n", MAX_R);
        return 1;
    }

    int alloc[MAX_P][MAX_R], max[MAX_P][MAX_R], avail[MAX_R];

    // what does each process currently hold?
    printf("\nEnter Allocation matrix (%d x %d):\n", n, r);
    for (i = 0; i < n; i++) {
        printf("P%d: ", i);
        for (j = 0; j < r; j++) {
            if (scanf("%d", &alloc[i][j]) != 1 || alloc[i][j] < 0) {
                printf("Error: allocation values must be non-negative integers.\n");
                return 1;
            }
        }
    }

    // what's the most each process will ever need?
    printf("\nEnter Max matrix (%d x %d):\n", n, r);
    for (i = 0; i < n; i++) {
        int valid = 0;
        while (!valid) {
            printf("P%d: ", i);
            valid = 1;
            for (j = 0; j < r; j++) {
                if (scanf("%d", &max[i][j]) != 1 || max[i][j] < 0) {
                    printf("Error: max values must be non-negative integers. Re-enter row.\n");
                    // flush leftover input
                    while (getchar() != '\n');
                    valid = 0;
                    break;
                }
                if (max[i][j] < alloc[i][j]) {
                    printf("Error: max[%d][%d] cannot be less than alloc[%d][%d]. Re-enter row.\n", i, j, i, j);
                    // flush leftover input
                    while (getchar() != '\n');
                    valid = 0;
                    break;
                }
            }
        }
    }

    // what's left in the pool right now?
    printf("\nEnter Available resources (%d values):\n", r);
    for (j = 0; j < r; j++) {
        if (scanf("%d", &avail[j]) != 1 || avail[j] < 0) {
            printf("Error: available values must be non-negative integers.\n");
            return 1;
        }
    }

    // figure out how much more each process might still ask for
    int need[MAX_P][MAX_R];
    for (i = 0; i < n; i++)
        for (j = 0; j < r; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    // try to find an order where every process can finish safely
    int f[MAX_P] = {0}, ans[MAX_P], ind = 0;

    for (k = 0; k < n; k++) {
        for (i = 0; i < n; i++) {
            if (f[i] == 0) {
                int flag = 0;
                for (j = 0; j < r; j++) {
                    // this process needs more than we can give right now, skip it
                    if (need[i][j] > avail[j]) {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0) {
                    // process can run to completion, add it to the sequence
                    ans[ind++] = i;
                    // and release its resources back into the pool
                    for (j = 0; j < r; j++)
                        avail[j] += alloc[i][j];
                    f[i] = 1;
                }
            }
        }
    }

    // if we couldn't schedule everyone, the system is stuck
    if (ind < n) {
        printf("\nSystem is in an UNSAFE state. No safe sequence exists.\n");
        return 1;
    }

    printf("\nSystem is in a SAFE state.\nSafe sequence: ");
    for (i = 0; i < n - 1; i++)
        printf("P%d -> ", ans[i]);
    printf("P%d\n", ans[n - 1]);

    return 0;
}