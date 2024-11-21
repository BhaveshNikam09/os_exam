#include <stdio.h>
#include <stdlib.h>

struct Process {
    int pid;       // Process ID
    int bt;        // Burst time
    int priority;  // Priority
    int wt;        // Waiting time
    int tat;       // Turnaround time
};

// Function to calculate waiting time and turnaround time
void findWaitingTime(struct Process proc[], int n) {
    proc[0].wt = 0; // First process has no waiting time
    for (int i = 1; i < n; i++) {
        proc[i].wt = proc[i-1].bt + proc[i-1].wt;
    }
}

void findTurnaroundTime(struct Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].tat = proc[i].bt + proc[i].wt;
    }
}

// Function to calculate average waiting time and turnaround time
void findAverageTimes(struct Process proc[], int n) {
    int total_wt = 0, total_tat = 0;
    
    for (int i = 0; i < n; i++) {
        total_wt += proc[i].wt;
        total_tat += proc[i].tat;
    }

    printf("Average Waiting Time: %.2f\n", (float)total_wt/n);
    printf("Average Turnaround Time: %.2f\n", (float)total_tat/n);
}

// Function to sort processes based on priority
void priorityScheduling(struct Process proc[], int n) {
    struct Process temp;
    
    // Sorting processes by priority
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[i].priority > proc[j].priority) {
                temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }
    
    findWaitingTime(proc, n);
    findTurnaroundTime(proc, n);
    findAverageTimes(proc, n);
}

int main() {
    int n;
    
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    // Dynamically allocate memory for processes array
    struct Process *proc = (struct Process*) malloc(n * sizeof(struct Process));
    
    printf("Enter burst time and priority for each process:\n");
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Process %d - Burst Time: ", i+1);
        scanf("%d", &proc[i].bt);
        printf("Process %d - Priority: ", i+1);
        scanf("%d", &proc[i].priority);
    }

    priorityScheduling(proc, n);
    
    printf("\nProcess | Burst Time | Priority | Waiting Time | Turnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].bt, proc[i].priority, proc[i].wt, proc[i].tat);
    }

    // Free dynamically allocated memory
    free(proc);
    
    return 0;
}

/*
Enter number of processes: 4
Enter burst time and priority for each process:
Process 1 - Burst Time: 6
Process 1 - Priority: 2
Process 2 - Burst Time: 2
Process 2 - Priority: 1
Process 3 - Burst Time: 8
Process 3 - Priority: 3
Process 4 - Burst Time: 3
Process 4 - Priority: 4
*/