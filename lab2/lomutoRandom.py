import random

def lomutoRandomR(arr, lo, hi):
    r = random.randrange(lo,hi)
    arr[hi], arr[r] = arr[r], arr[hi]
    return lomutoRandom(arr,lo,hi)

def lomutoRandom(arr, lo, hi):
    pivot =  arr[hi]
    i = lo
    for j in range(lo,hi):
        if arr[j] <= pivot:
            arr[i], arr[j] = arr[j], arr[i]
            i+=1
    arr[hi], arr[i] = arr[i], arr[hi]
    return i

def quicksort(arr, lo, hi):
    if lo < hi:
        p = lomutoRandomR(arr, lo, hi)
        quicksort(arr, lo, p-1)
        quicksort(arr, p + 1, hi)