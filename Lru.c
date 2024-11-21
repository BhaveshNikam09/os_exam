#include <stdio.h>
#include <stdlib.h> // For malloc and free

void lruPageReplacement(int pages[], int n, int capacity) {
    int *frames = (int *)malloc(capacity * sizeof(int)); // Dynamically allocate memory for frames
    int *time = (int *)malloc(capacity * sizeof(int));   // Dynamically allocate memory for time array
    int count = 0;                                       // Count the total page faults
    int currentTime = 0;                                 // Incremental time counter
    int i, j;

    // Initialize frames and time arrays to -1
    for (i = 0; i < capacity; i++) {
        frames[i] = -1;
        time[i] = -1;
    }

    printf("Page Reference | Frames\n");
    printf("------------------------\n");

    for (i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        // Check if the page is already in the frames
        for (j = 0; j < capacity; j++) {
            if (frames[j] == page) {
                found = 1;
                time[j] = currentTime++; // Update usage time
                break;
            }
        }

        // If the page is not in the frames
        if (!found) {
            int lruIndex = 0; // Find the least recently used frame
            for (j = 1; j < capacity; j++) {
                if (time[j] < time[lruIndex]) {
                    lruIndex = j;
                }
            }
            frames[lruIndex] = page;      // Replace the LRU page
            time[lruIndex] = currentTime++; // Update usage time
            count++;                      // Increment page fault count
        }

        // Display the frames at each step
        printf("%13d | ", page);
        for (j = 0; j < capacity; j++) {
            if (frames[j] != -1)
                printf("%d ", frames[j]);
        }
        printf("\n");
    }

    printf("------------------------\n");
    printf("Total Page Faults: %d\n", count);

    // Free allocated memory
    free(frames);
    free(time);
}

int main() {
    int n, capacity;

    // Input the number of pages
    printf("Enter the number of pages: ");
    scanf("%d", &n);

    // Dynamically allocate memory for the pages array
    int *pages = (int *)malloc(n * sizeof(int));

    printf("Enter the page reference string:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    // Input the frame capacity
    printf("Enter the number of frames: ");
    scanf("%d", &capacity);

    // Call the LRU page replacement algorithm
    lruPageReplacement(pages, n, capacity);

    // Free the dynamically allocated pages array
    free(pages);

    return 0;
}
/*
Enter the number of pages: 10
Enter the page reference string:
7 0 1 2 0 3 0 4 2 3
Enter the number of frames: 3
*/