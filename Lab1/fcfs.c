#include <stdio.h>

//calc waiting time 
//the current process wt is the previous process's wt + bt
void calculateWT(int bt[], int wt[], int n) {
    int i;

    //first process waiting time is always 0
    wt[0] = 0;

    for(i = 1; i < n; i++) {
        wt[i] = wt[i-1] + bt[i-1];
    }
}

//calc turnaround time
//the turnaround time is bt + wt
void calculateTAT(int bt[], int wt[], int tat[], int n) {
    int i;

    for(i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
    }
}

//print result
void display(int bt[], int wt[], int tat[], int n) {
    int i;

    //print table header (uniform spacing)
    printf("\n%-10s %-15s %-15s %-15s\n", "Process", "Burst Time", "Waiting Time", "Turnaround Time");

    //initialise variable for total wt and tat
    float total_wt = 0, total_tat = 0;

    //iterate through the loop to calculate total wt and tat
    for(i = 0; i < n; i++) {
        printf("P%-9d %-15d %-15d %-15d\n", i + 1, bt[i], wt[i], tat[i]);
        total_wt += wt[i];
        total_tat += tat[i];
    }

    //calc averages
    printf("\nAverage Waiting Time = %.2f", total_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", total_tat / n);
}

int main() {
    int n, i;
    
    //prompt user to enter number of processes (must be positive)
    do {
        printf("Enter number of processes: ");
        scanf("%d", &n);

        if(n <= 0) {
            printf("Invalid input. Please enter a positive number.\n");
        }
    } while(n <= 0);

    int bt[n], wt[n], tat[n];
    //bt[n] - burst time
    //wt[n] - waiting time
    //tat[n] - turnaround time

    //prompt the user to enter burst time for each process (must be non-negative)
    for(i = 0; i < n; i++) {
        do {
            printf("Enter burst time for process (positive number) %d: ", i + 1);
            scanf("%d", &bt[i]);

            if(bt[i] < 0) {
                printf("Invalid input. Burst time cannot be negative.\n");
            }
        } while(bt[i] < 0);
    }

    //function calls
    calculateWT(bt, wt, n);
    calculateTAT(bt, wt, tat, n);
    display(bt, wt, tat, n);

    return 0;
}