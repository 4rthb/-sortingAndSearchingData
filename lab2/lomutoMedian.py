import math

nswaps = 0
nrec = 0

def lomuto(arr, lo, hi):
    global nswaps
    pivot = arr[hi]
    i = lo
    for j in range(lo,hi):
        if arr[j] <= pivot:
            arr[i], arr[j] = arr[j], arr[i]
            nswaps+=1
            i = i + 1
    arr[i], arr[hi] = arr[hi], arr[i]
    nswaps+=1
    return i

def lomutoMedian(arr, lo, hi):
    global nswaps
    med = math.floor((hi+lo)/2)
    if arr[lo] > arr[med] :
        arr[lo], arr[med] = arr[med], arr[lo]
        nswaps+=1
    if arr[lo] > arr[hi] :
        arr[lo], arr[hi] = arr[hi], arr[lo]
        nswaps+=1
    if arr[med] < arr[hi] :
        arr[hi], arr[med] = arr[med], arr[hi]
        nswaps+=1
    return lomuto(arr, lo, hi)

def quicksort(arr, lo, hi):
    global nrec
    if lo < hi:
        p = lomutoMedian(arr, lo, hi)
        quicksort(arr, lo, p - 1)
        nrec+=1
        quicksort(arr, p + 1, hi)
        nrec+=1