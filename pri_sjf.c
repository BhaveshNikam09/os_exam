#include <stdio.h>
#include <stdlib.h>

struct Process {
    int pid;           // Process ID
    int bt;            // Burst time
    int at;            // Arrival time
    int wt;            // Waiting time
    int tat;           // Turnaround time
    int priority;      // Priority (used for priority scheduling)
};

// Function to sort processes by arrival time
void sortByArrivalTime(struct Process proc[], int n) {
    struct Process temp;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[i].at > proc[j].at) {
                temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }
}

// Function to calculate waiting time and turnaround time considering arrival time
void calculateTimes(struct Process proc[], int n) {
    int time = 0; // Keeps track of the current time
    proc[0].wt = 0; // First process always has 0 waiting time if it arrives at 0
    time = proc[0].at + proc[0].bt; // First process completion time

    for (int i = 1; i < n; i++) {
        if (time < proc[i].at) {
            // Idle time, if the process has not arrived yet
            time = proc[i].at;
        }
        proc[i].wt = time - proc[i].at; // Waiting time = Current time - Arrival time
        time += proc[i].bt;            // Update current time after the process finishes
        proc[i].tat = proc[i].wt + proc[i].bt; // Turnaround time = Waiting time + Burst time
    }

    // For the first process, explicitly calculate TAT
    proc[0].tat = proc[0].bt;
}

// Function to calculate average waiting time and turnaround time
void findAverageTimes(struct Process proc[], int n) {
    int total_wt = 0, total_tat = 0;

    for (int i = 0; i < n; i++) {
        total_wt += proc[i].wt;
        total_tat += proc[i].tat;
    }

    printf("Average Waiting Time: %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);
}

// Function to sort processes by priority for Priority Scheduling
void priorityScheduling(struct Process proc[], int n) {
    sortByArrivalTime(proc, n); // Sort by arrival time first
    struct Process temp;

    // Sort by priority among processes that have arrived
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((proc[i].priority > proc[j].priority) &&
                (proc[j].at <= proc[i].at)) {
                temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }

    calculateTimes(proc, n);
    findAverageTimes(proc, n);
}

// Function to sort processes by burst time for SJF Scheduling
void sjfScheduling(struct Process proc[], int n) {
    sortByArrivalTime(proc, n); // Sort by arrival time first
    struct Process temp;

    // Sort by burst time among processes that have arrived
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((proc[i].bt > proc[j].bt) &&
                (proc[j].at <= proc[i].at)) {
                temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }

    calculateTimes(proc, n);
    findAverageTimes(proc, n);
}

int main() {
    int n, choice;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process *proc = (struct Process *)malloc(n * sizeof(struct Process));

    printf("Enter arrival time, burst time, and priority for each process:\n");
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Process %d - Arrival Time: ", i + 1);
        scanf("%d", &proc[i].at);
        printf("Process %d - Burst Time: ", i + 1);
        scanf("%d", &proc[i].bt);
        printf("Process %d - Priority: ", i + 1);
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

    printf("\nProcess | Arrival Time | Burst Time | Priority | Waiting Time | Turnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].pid, proc[i].at, proc[i].bt, proc[i].priority, proc[i].wt, proc[i].tat);
    }

    free(proc);
    return 0;
}
/*
Enter number of processes: 3
Enter arrival time, burst time, and priority for each process:
Process 1 - Arrival Time: 0
Process 1 - Burst Time: 5
Process 1 - Priority: 2
Process 2 - Arrival Time: 1
Process 2 - Burst Time: 3
Process 2 - Priority: 1
Process 3 - Arrival Time: 2
Process 3 - Burst Time: 8
Process 3 - Priority: 3

Choose Scheduling Algorithm:
1. Priority Scheduling
2. Shortest Job First (SJF) Scheduling
1

Priority Scheduling Algorithm:
Average Waiting Time: 2.67
Average Turnaround Time: 10.33

Process | Arrival Time | Burst Time | Priority | Waiting Time | Turnaround Time
1               0              5              2              0                5
2               1              3              1              4                7
3               2              8              3              6               14
*/