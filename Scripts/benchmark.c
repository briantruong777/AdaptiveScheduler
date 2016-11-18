#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// seed
srand(time(NULL));

int fibonacci(int n) {
    int t1 = 0, t2 = 1, nextTerm = 0, n;
  
    // random int between 5000-15000
    int r = (rand() % 10000) + 5000;

    // displays the first two terms which is always 0 and 1
    nextTerm = t1 + t2;

    while(nextTerm <= n) {
        t1 = t2;
        t2 = nextTerm;
        nextTerm = t1 + t2;
    }
    
    return nextTerm;
}

void bubblesort() {
  int array[10000], c, d, swap, i;
  
  for (i = 0; i < 10000; i++) {
    array[i] = (rand() % 10000) + 5000;
  }
  
  for (c = 0 ; c < ( n - 1 ); c++) {
    for (d = 0 ; d < n - c - 1; d++) {
      if (array[d] > array[d+1]) {
        swap       = array[d];
        array[d]   = array[d+1];
        array[d+1] = swap;
      }
    }
  }
}

int main() {
    // TODO: test functions
    // Generate array 90% fib, 10% bub sort
    // Launch fork() on array
    
    return 0;
}
