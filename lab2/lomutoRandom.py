import random

nswaps = 0
nrec = 0

def lomutoRandomR(arr, lo, hi):
    global nswaps
    r = random.randrange(lo,hi)
    arr[hi], arr[r] = arr[r], arr[hi]
    nswaps+=1
    return lomutoRandom(arr,lo,hi)

def lomutoRandom(arr, lo, hi):
    global nswaps
    pivot =  arr[hi]
    i = lo
    for j in range(lo,hi):
        if arr[j] <= pivot:
            arr[i], arr[j] = arr[j], arr[i]
            nswaps+=1
            i+=1
    arr[hi], arr[i] = arr[i], arr[hi]
    nswaps+=1
    return i

def quicksort(arr, lo, hi):
    global nrec
    if lo < hi:
        p = lomutoRandomR(arr, lo, hi)
        quicksort(arr, lo, p-1)
        nrec+=1
        quicksort(arr, p + 1, hi)
        nrec+=1