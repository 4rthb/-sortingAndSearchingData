import random

def hoareRandomR(arr, lo, hi):
    r = random.randrange(lo,hi)
    arr[lo], arr[r] = arr[r], arr[lo]
    return hoareRandom(arr,lo,hi)

def hoareRandom(arr, lo, hi):
    pivot = arr[lo]
    i = lo
    j = hi
    while True:
        while arr[i]<pivot:
            i+=1
        while arr[j]>pivot:
            j-=1
        if i>=j:
            return j
        arr[i], arr[j] = arr[j], arr[i]

def quicksort(arr, lo, hi):
    if lo < hi:
        p = hoareRandomR(arr, lo, hi)
        quicksort(arr, lo, p)
        quicksort(arr, p + 1, hi)