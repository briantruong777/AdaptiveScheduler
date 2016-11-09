import random
import time

def fib():
  n = random.randint(10000, 100000)
  a, b = 1, 1
  for i in range(n-1):
    a, b = b, a+b
  return a
  
start = time.time()
fib()
print time.time() - start
