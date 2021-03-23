import random
import sys

sys.setrecursionlimit(1000000)
nswaps = 0
nrec = 0

def hoareRandomR(arr, lo, hi):
    global nswaps
    r = random.randrange(lo,hi)
    arr[lo], arr[r] = arr[r], arr[lo]
    nswaps+=1
    return hoareRandom(arr,lo,hi)

def hoareRandom(arr, lo, hi):
    global nswaps
    pivot = arr[lo]
    i = lo-1
    j = hi+1
    while i<= j:
        while True:
            j -= 1
            if arr[j] <= pivot:
                break
        while True:
            i += 1
            if arr[i] >= pivot:
                break
        if i < j:
            arr[i], arr[j] = arr[j], arr[i]
            nswaps+=1
        else:
            return j

def quicksort(arr, lo, hi):
    global nrec
    if lo < hi:
        p = hoareRandomR(arr, lo, hi)
        quicksort(arr, lo, p)
        nrec+=1
        quicksort(arr, p + 1, hi)
        nrec+=1