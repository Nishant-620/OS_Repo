#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define SIZE 30
#define HALF 15
#define NOT_FOUND 255

int main() {
    int arr[SIZE], key1, key2;
    pid_t p1, p2;
    int status;

    // Initialize random seed
    srand(time(NULL));

    printf("Array Elements:\n");
    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand() % 50 + 1;
        printf("%2d ", arr[i]);

        if (i == HALF - 1)
            printf(" | ");
    }

    // Input search keys
    printf("\n\nEnter Key 1 to search in 1st half: ");
    scanf("%d", &key1);

    printf("Enter Key 2 to search in 2nd half: ");
    scanf("%d", &key2);

    // -------- Fork Child 1 --------
    p1 = fork();

    if (p1 < 0) {
        perror("Fork failed");
        return 1;
    }

    if (p1 == 0) {  // Child 1
        int found_index = NOT_FOUND;

        for (int i = 0; i < HALF; i++) {
            if (arr[i] == key1) {
                found_index = i;
                break;
            }
        }

        _exit(found_index);  // safer in child
    }

    // Parent waits for Child 1
    waitpid(p1, &status, 0);

    if (WIFEXITED(status)) {
        int res1 = WEXITSTATUS(status);

        if (res1 == NOT_FOUND)
            printf("Child 1: Key %d not found in first half.\n", key1);
        else
            printf("Child 1: Key %d found at index %d.\n", key1, res1);
    }

    // -------- Fork Child 2 --------
    p2 = fork();

    if (p2 < 0) {
        perror("Fork failed");
        return 1;
    }

    if (p2 == 0) {  // Child 2
        int found_index = NOT_FOUND;

        for (int i = HALF; i < SIZE; i++) {
            if (arr[i] == key2) {
                found_index = i;
                break;
            }
        }

        _exit(found_index);
    }

    // Parent waits for Child 2
    waitpid(p2, &status, 0);

    if (WIFEXITED(status)) {
        int res2 = WEXITSTATUS(status);

        if (res2 == NOT_FOUND)
            printf("Child 2: Key %d not found in second half.\n", key2);
        else
            printf("Child 2: Key %d found at index %d.\n", key2, res2);
    }

    return 0;
}