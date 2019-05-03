from fractions import gcd

T = int(input())
for t in range(1, T + 1):
    print("Case #" + str(t) + ": ", end="")
    N, L = map(int, input().split())
    v = list(map(int, input().split()))

    primes = [0] * (L + 1)

    k = 0
    while v[k] == v[k + 1]:
        k = k + 1
    primes[k + 1] = gcd(v[k], v[k + 1])

    for i in range(k + 2, L + 1):
        primes[i] = v[i - 1] // primes[i - 1]
    for i in range(k, -1, -1):
        primes[i] = v[i] // primes[i + 1]
        
    p = primes.copy()
    primes = list(set(sorted(primes)))
    
    nrs = [len([1 for q in primes if q < i]) for i in p]
    print(''.join([chr(ord('A') + x) for x in nrs]))