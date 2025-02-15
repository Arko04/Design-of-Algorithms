import sys

sys.setrecursionlimit(10 ** 6)

n = int(input())

arr = list(map(int, input().split()))

m = min(arr)

def find_last_ocuurrence_of_min(start_ind, end_ind) :
    if start_ind >= end_ind :
        if arr[end_ind] == m :
            return end_ind
        else:
            return -1

    mid_ind = (start_ind + end_ind) // 2

    r = find_last_ocuurrence_of_min(mid_ind + 1, end_ind)
    
    if r == -1 :
        return find_last_ocuurrence_of_min(start_ind, mid_ind)
    else:
        return r

print(f'({find_last_ocuurrence_of_min(0, n - 1)},{m})')