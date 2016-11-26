#include <stdio.h>
#include <sched.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <linux/sched.h>
#include <string.h>

long get_nanos(void) {
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return ts.tv_nsec;	
}

void print_sched() {
    char path[50], buff[255], out[255] ="";
    const char s[2] = " ";
    sprintf(path, "/proc/%d/sched", getpid());
    FILE* fp = fopen(path, "r");
    
    while (fgets(buff, 255, (FILE*)fp) != NULL) {
	char* token = strtok(buff, s);
	
	if (strcmp(token, "se.sum_exec_runtime") == 0 ||
	    strcmp(token, "se.statistics.wait_sum") == 0 ||
	    strcmp(token, "nr_switches") == 0 ||
	    strcmp(token, "nr_voluntary_switches") == 0 ||
	    strcmp(token, "nr_involuntary_switches") == 0) {
	    token = strtok(NULL, s); // skip the ":"
	    token = strtok(NULL, s);
	    token[strcspn(token, "\n")] = 0; // remove new line
	    strcat(token, ", ");
	    strcat(out, token); 
	}
    }
    out[strlen(out)-2] = '\0';
    printf("%d, %d, %s\n", getpid(), sched_getscheduler(0), out); 
    fclose(fp);
    return;
}

int fibonacci(int i, int n) {
    unsigned long long nextTerm = 0;
    for (int j = 0; j < 50000; j++) {
    	unsigned long long t1 = 0, t2 = 1;
    	int c = 3;
     	nextTerm = t1 + t2;

    	while (c++ < n) {
            t1 = t2;
            t2 = nextTerm;
            nextTerm = t1 + t2;
    	}
    }
    
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

}

int main(int argc, char *argv[]) {
    int numProcesses = atoi(argv[1]);

    pid_t pid;
    for (int i = 0; i < numProcesses; i++) {
        if ((pid = fork()) < 0) {
            perror("Error fork()ing!");
            abort();
        } else if (pid == 0) { // in child process
	    srand(get_nanos());
	    
	    // set policy for process
	    struct sched_param param;
	    param.sched_priority = 0;
  	    sched_setscheduler(0, SCHED_NORMAL, &param);

	    if (rand() % 100 >= atoi(argv[2])) {
            	fibonacci(i, (rand() % 50 + 100)); //100-150
	    } else {
		bubblesort(i, (rand() % 10000 + 5000)); //25000-35000
	    }

	    print_sched();
            exit(0); // important line, exiting child process
        } else {
            ;
        }
    }

    for (int i = 0; i < numProcesses; i++) {
	int status = 0;
	pid_t child_pid = wait(&status);
    }

    return 0;
}
