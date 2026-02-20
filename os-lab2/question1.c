#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main() {
    int arr[30], key1, key2, status;
    pid_t p1, p2;
    srand(time(NULL));
    printf("Array Elements:\n");

    for (int i = 0; i < 30; i++) {
        arr[i] = rand() % 50 + 1;
        printf("%d ", arr[i]);
        if (i == 14)
            printf(" | ");
    }
    printf("\n\nEnter Key 1 to search in 1st half: ");
    scanf("%d", &key1);

    printf("Enter Key 2 to search in 2nd half: ");
    scanf("%d", &key2);
    p1 = fork();

    if (p1 < 0) {
        perror("Fork failed");
        return 1;
    }

    if (p1 == 0) {  
        int found_index = 255;

        for (int i = 0; i < 15; i++) {
            if (arr[i] == key1) {
                found_index = i;
                break;
            }
        }
    exit(found_index);
    }
    waitpid(p1, &status, 0);
    int res1 = WEXITSTATUS(status);

    if (res1 == 255)
        printf("Child 1: Key %d not found in the first half.\n", key1);
    else
        printf("Child 1: Key %d found at index %d.\n", key1, res1);

    // Fork Child 2
    p2 = fork();

    if (p2 < 0) {
        perror("Fork failed");
        return 1;
    }

    if (p2 == 0) {  // Child 2
        int found_index = 255;

        for (int i = 15; i < 30; i++) {
            if (arr[i] == key2) {
                found_index = i;
                break;
            }
        }

        exit(found_index);
    }
    waitpid(p2, &status, 0);
    int res2 = WEXITSTATUS(status);

    if (res2 == 255)
        printf("Child 2: Key %d not found in the second half.\n", key2);
    else
        printf("Child 2: Key %d found at index %d.\n", key2, res2);

    return 0;
}