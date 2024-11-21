#include <stdio.h>
#include <stdio.h>
#include <stdlib.h> // For malloc and free

void fifoPageReplacement(int pages[], int n, int capacity) {
    int *frames = (int *)malloc(capacity * sizeof(int)); // Dynamically allocate memory for frames
    int front = 0;        // Points to the oldest page in the frames
    int count = 0;        // Counts the total page faults
    int isFull = 0;       // Tracks if frames are filled
    int i, j;

    // Initialize frames to -1 (empty)
    for (i = 0; i < capacity; i++) {
        frames[i] = -1;
    }

    printf("Page Reference | Frames\n");
    printf("------------------------\n");

    for (i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        // Check if the page is already in frames
        for (j = 0; j < capacity; j++) {
            if (frames[j] == page) {
                found = 1;
                break;
            }
        }

        // If the page is not in the frames, replace using FIFO
        if (!found) {
            frames[front] = page;      // Replace the oldest page
            front = (front + 1) % capacity; // Move to the next oldest position
            count++;                  // Increment page fault count
            isFull = (isFull < capacity) ? isFull + 1 : isFull;
        }

        // Display the frames at each step
        printf("%13d | ", page);
        for (j = 0; j < isFull; j++) {
            printf("%d ", frames[j]);
        }
        printf("\n");
    }

    printf("------------------------\n");
    printf("Total Page Faults: %d\n", count);

    free(frames); // Free dynamically allocated memory
}

int main() {
    int n, capacity;

    // Input the number of pages
    printf("Enter the number of pages: ");
    scanf("%d", &n);

    // Dynamically allocate memory for the pages array
    int *pages = (int *)malloc(n * sizeof(int));
    if (pages == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter the page reference string:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    // Input the frame capacity
    printf("Enter the number of frames: ");
    scanf("%d", &capacity);

    // Call the FIFO page replacement algorithm
    fifoPageReplacement(pages, n, capacity);

    free(pages); // Free dynamically allocated memory for pages
    return 0;
}


/*
Enter the number of pages: 9
Enter the page reference string:
7 0 1 2 0 3 0 4 2
Enter the number of frames: 3
*/