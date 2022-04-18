import random

n, m = 10, 30

print(n, m)

for i in range(m):
    for j in range(n):
        print(random.random(), end=' ')
    print(random.random() * 100)
       
for i in range(n):
    print(random.random(), end=' ')
