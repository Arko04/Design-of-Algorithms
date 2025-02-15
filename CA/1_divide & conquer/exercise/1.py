from math import comb
r = 10**9 + 7
def factorial(n):
    result = 1
    for i in range(1, n + 1):
        result = (result * i) % (r)
    return result

def choose(p, q):
    return factorial(p + q) // (factorial(p) * factorial(q))

def calc(a):
    right = []
    left = []
    init = a[0]
    n = len(a)

    for i in range(1, n):
        if a[i] > init:
            right.append(a[i])
        elif a[i] < init:
            left.append(a[i])

    size_r = len(right)
    size_l = len(left)

    if size_r == 0 and size_l == 0:
        return 1
    elif size_r == 0:
        return calc(left) % (r)
    elif size_l == 0:
        return calc(right) % (r)

    return (comb(size_l + size_r, size_r) % (r) * calc(right) % (r) * calc(left)% (r)) % (r)

n = int(input())
a = list(map(int, input().split()))

result = calc(a)
if result == 0:
    print((r) - 1)
else:
    print(result - 1)
