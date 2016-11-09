import random
import time
n = random.randint(5000, 10000)

def bubblesort(A):
  for i in range(len(A)):
    for j in range(len(A)-1, i, -1):
      if A[j] < A[j-1]:
        A[j], A[j-1] = A[j-1], A[j]
  return A
  
start = time.time()
bubblesort(random.sample(range(0, n), n))
print time.time() - start
       
