#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <time.h>

// seed
//srand(100);

int fibonacci(int i) {
    int t1 = 0, t2 = 1, nextTerm = 0, c = 3;
    int n = (rand() % 10000) + 5000; // random int between 5000-15000
    nextTerm = t1 + t2; // displays the first two terms which is always 0 and 1

    while (c++ < n) {
        t1 = t2;
        t2 = nextTerm;
        nextTerm = t1 + t2;
    }
    printf("process %d: fibo %d finished with result %d\n", getpid(), i, nextTerm);
    return nextTerm;
}

void bubblesort(int i) {
    int n = 10000;
    int array[n], c, d, swap;

    for (int i = 0; i < n; i++) {
        array[i] = (rand() % n) + 5000; // initialize
    }

    for (c = 0; c < (n - 1); c++) {
        for (d = 0; d < n - c - 1; d++) {
            if (array[d] > array[d + 1]) { // swapping two values
                swap = array[d];
                array[d] = array[d + 1];
                array[d + 1] = swap;
            }
        }
    }
    printf("process %d: bub %d finished\n", getpid(), i);
}

int main(int argc, char *argv[]) {
    // Generate array 90% fib, 10% bub sort
    // Launch fork() on array
    int numProcesses = 10;
    int processTypes[numProcesses];
    for (int i = 0; i < numProcesses; i++) {
        processTypes[i] = (rand() % 10 < 1 ? 1 : 0); // 10% CPU-intensive
    }

    pid_t pid;
    for (int i = 0; i < numProcesses; i++) {
        if ((pid = fork()) < 0) {
            perror("Error fork()ing!");
            abort();
        } else if (pid == 0) { // in child process
            processTypes[i] == 0 ? fibonacci(i) : bubblesort(i);
            exit(0); // important line, exiting child process
        } else {
            wait(NULL);
        }
    }

    printf("parent process finished\n");
    return 0;
}
