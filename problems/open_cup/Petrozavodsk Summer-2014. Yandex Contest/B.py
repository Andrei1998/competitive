from decimal import *
getcontext().prec = 100

N = int(input())
x = [] 
for i in range(N):
    x.append(2 ** i)
print(' '.join([s + ".0" for s in map(str, x)]))

while True:
    v = list(map(int, input().split()))
    if len(v) == 1 and v[0] == 0:
        break
    a, step = Decimal(0), Decimal(1)
    for i in range(N):
        if v[i] == -1:
            a = a + step
        step = step / Decimal(2)
    print('{:f}'.format(a + step))
