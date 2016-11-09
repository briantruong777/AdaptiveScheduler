import random
import time
n = random.randint(5000, 10000)

def bubblesort(A):
  for i in range(len(A)):
    for j in range(len(A)-1, i, -1):
      if A[k] < A[k-1]:
        A[k], A[k-1] = A[k-1], A[k]
  return A
  
start = time.time()
bubblesort(random.sample(range(0, n), n))
print time.time() - start
       
