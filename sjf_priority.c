#include <stdio.h>
#include <stdlib.h>

struct Process {
    int pid;       // Process ID
    int bt;        // Burst time
    int wt;        // Waiting time
    int tat;       // Turnaround time
    int priority;  // Priority (used for priority scheduling)
};

// Function to calculate waiting time and turnaround time for non-preemptive scheduling
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

// Function to sort processes by priority (for Priority Scheduling)
void priorityScheduling(struct Process proc[], int n) {
    struct Process temp;
    
    // Sorting processes by priority (higher number means lower priority)
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

// Function to sort processes by burst time (for Shortest Job First Scheduling)
void sjfScheduling(struct Process proc[], int n) {
    struct Process temp;
    
    // Sorting processes by burst time
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[i].bt > proc[j].bt) {
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
    int n, choice;
    
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    // Dynamically allocate memory for processes array
    struct Process *proc = (struct Process*) malloc(n * sizeof(struct Process));
    
    printf("Enter burst time and priority for each process (for priority scheduling):\n");
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Process %d - Burst Time: ", i+1);
        scanf("%d", &proc[i].bt);
        printf("Process %d - Priority: ", i+1);
        scanf("%d", &proc[i].priority);
    }

    printf("\nChoose Scheduling Algorithm:\n");
    printf("1. Priority Scheduling\n");
    printf("2. Shortest Job First (SJF) Scheduling\n");
    scanf("%d", &choice);
    
    if (choice == 1) {
        printf("\nPriority Scheduling Algorithm:\n");
        priorityScheduling(proc, n);
    } else if (choice == 2) {
        printf("\nShortest Job First (SJF) Scheduling Algorithm:\n");
        sjfScheduling(proc, n);
    } else {
        printf("\nInvalid choice!\n");
    }
    
    printf("\nProcess | Burst Time | Priority | Waiting Time | Turnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].bt, proc[i].priority, proc[i].wt, proc[i].tat);
    }

    // Free dynamically allocated memory
    free(proc);
    
    return 0;
}

/*
Enter number of processes: 3
Enter burst time and priority for each process (for priority scheduling):
Process 1 - Burst Time: 6
Process 1 - Priority: 2
Process 2 - Burst Time: 8
Process 2 - Priority: 1
Process 3 - Burst Time: 7
Process 3 - Priority: 3

Choose Scheduling Algorithm:
1. Priority Scheduling
2. Shortest Job First (SJF) Scheduling
*/