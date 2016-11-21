#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

long get_nanos(void) {
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return ts.tv_nsec;	
}

int fibonacci(int i, int n) {
    unsigned long long t1 = 0, t2 = 1, nextTerm = 0;
    int c = 3; // random int between 5-105
    nextTerm = t1 + t2; // displays the first two terms which is always 0 and 1

    while (c++ < n) {
        t1 = t2;
        t2 = nextTerm;
        nextTerm = t1 + t2;
    }
    printf("process %d: fibo %d finished with result %llu\n", getpid(), i, nextTerm);
    return nextTerm;
}

void bubblesort(int i, int n) {
    int array[n], c, d, swap;

    for (int i = 0; i < n; i++) {
        array[i] = (rand() % n); // initialize
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

    printf("process %d: bub %d finished sorting %d elements\n", getpid(), i, n);
}

int main(int argc, char *argv[]) {
    int numProcesses = atoi(argv[1]);
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
	    srand(get_nanos());
            processTypes[i] == 0 ? fibonacci(i, (rand() % 100 + 5)) : bubblesort(i, (rand() % 5000 + 10000));
            exit(0); // important line, exiting child process
        } else {
            wait(NULL);
        }
    }

    printf("parent %d process finished\n", getpid());
    return 0;
}
