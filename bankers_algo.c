#include <stdio.h>
#include <stdbool.h>

#define P 5  // Number of processes
#define R 3  // Number of resources

// Function to find if a system is in a safe state
bool isSafe(int processes[], int avail[], int max[][R], int allot[][R]) {
    int need[P][R];
    int work[R];
    bool finish[P] = {false};
    int safeSeq[P];
    int count = 0;

    // Calculate the Need matrix (Need = Max - Allocation)
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - allot[i][j];
        }
    }

    // Initialize work as the available resources
    for (int i = 0; i < R; i++) {
        work[i] = avail[i];
    }

    // Try to find a safe sequence
    while (count < P) {
        bool found = false;

        // Find a process whose request can be satisfied
        for (int p = 0; p < P; p++) {
            if (!finish[p]) {
                bool canAllocate = true;

                // Check if the process's needs can be satisfied with available resources
                for (int j = 0; j < R; j++) {
                    if (need[p][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate) {
                    // Allocate resources to the process and mark it as finished
                    for (int j = 0; j < R; j++) {
                        work[j] += allot[p][j];  // Release allocated resources
                    }
                    finish[p] = true;
                    safeSeq[count++] = p;
                    found = true;
                    break;
                }
            }
        }

        // If no process could be allocated resources, the system is in an unsafe state
        if (!found) {
            printf("System is in an unsafe state.\n");
            return false;
        }
    }

    // If we reach here, the system is in a safe state
    printf("System is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < P; i++) {
        printf("P%d ", safeSeq[i]);
    }
    printf("\n");
    return true;
}

int main() {
    int processes[P] = {0, 1, 2, 3, 4};  // Processes P0, P1, P2, P3, P4
    int avail[R] = {3, 3, 2};  // Available instances of resources
    int max[P][R] = {
        {7, 5, 3},  // Max demand for P0
        {3, 2, 2},  // Max demand for P1
        {9, 0, 2},  // Max demand for P2
        {2, 2, 2},  // Max demand for P3
        {4, 3, 3}   // Max demand for P4
    };
    int allot[P][R] = {
        {0, 1, 0},  // Allocation for P0
        {2, 0, 0},  // Allocation for P1
        {3, 0, 2},  // Allocation for P2
        {2, 1, 1},  // Allocation for P3
        {0, 0, 2}   // Allocation for P4
    };

    // Check if the system is in a safe state
    isSafe(processes, avail, max, allot);

    return 0;
}

/*
Available resources: 3, 3, 2
Max matrix:
7 5 3
3 2 2
9 0 2
2 2 2
4 3 3
Allocation matrix:
0 1 0
2 0 0
3 0 2
2 1 1
0 0 2
*/