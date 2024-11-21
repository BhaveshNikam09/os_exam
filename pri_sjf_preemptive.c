#include <stdio.h>
#include <limits.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time; // For preemptive scheduling
    int priority;       // For Priority Scheduling
    int finish_time;
    int turnaround_time;
    int waiting_time;
};

// Preemptive Priority Scheduling
void prioritySchedulingPreemptive(struct Process processes[], int n) {
    int time = 0, completed = 0, idx = -1;
    printf("\nPreemptive Priority Scheduling:\n");
    printf("Gantt Chart: ");

    // Input priority values
    for (int i = 0; i < n; i++) {
        printf("Enter Priority for Process %d: ", processes[i].pid);
        scanf("%d", &processes[i].priority);
        processes[i].remaining_time = processes[i].burst_time; // Initialize remaining time
    }

    while (completed < n) {
        int highest_priority = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= time && processes[i].remaining_time > 0 && processes[i].priority < highest_priority) {
                highest_priority = processes[i].priority;
                idx = i;
            }
        }

        if (idx != -1) {
            processes[idx].remaining_time--;
            printf(" P%d |", processes[idx].pid);

            if (processes[idx].remaining_time == 0) {
                processes[idx].finish_time = time + 1;
                processes[idx].turnaround_time = processes[idx].finish_time - processes[idx].arrival_time;
                processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;
                completed++;
                idx = -1;
            }
        }
        time++;
    }

    printf("\nProcess Details:\n");
    printf("PID\tAT\tBT\tPri\tFT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", processes[i].pid, processes[i].arrival_time, 
               processes[i].burst_time, processes[i].priority, processes[i].finish_time, 
               processes[i].turnaround_time, processes[i].waiting_time);
    }
}

// Non-Preemptive SJF Scheduling
void sjfSchedulingNonPreemptive(struct Process processes[], int n) {
    int time = 0, completed = 0, idx = -1;

    printf("\nShortest Job First (SJF) Scheduling:\n");
    printf("Gantt Chart: ");

    while (completed < n) {
        int shortest_burst = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= time && processes[i].burst_time > 0 && processes[i].burst_time < shortest_burst) {
                shortest_burst = processes[i].burst_time;
                idx = i;
            }
        }

        if (idx != -1) {
            time += processes[idx].burst_time;
            processes[idx].finish_time = time;
            processes[idx].turnaround_time = processes[idx].finish_time - processes[idx].arrival_time;
            processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;
            printf(" P%d |", processes[idx].pid);
            processes[idx].burst_time = 0; // Mark as completed
            completed++;
            idx = -1;
        } else {
            time++;
        }
    }

    printf("\nProcess Details:\n");
    printf("PID\tAT\tBT\tFT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", processes[i].pid, processes[i].arrival_time, 
               processes[i].burst_time, processes[i].finish_time, processes[i].turnaround_time, 
               processes[i].waiting_time);
    }
}

int main() {
    int n, choice;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter Arrival Time and Burst Time for Process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
    }

    do {
        printf("\nScheduling Algorithms Menu:\n");
        printf("1. Preemptive Priority Scheduling\n");
        printf("2. Shortest Job First (SJF) Scheduling\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                prioritySchedulingPreemptive(processes, n);
                break;
            case 2:
                sjfSchedulingNonPreemptive(processes, n);
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 3);

    return 0;
}
