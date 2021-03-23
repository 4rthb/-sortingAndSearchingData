import math

nswaps = 0
nrec = 0

def hoare(arr, lo, hi):
    global nswaps
    pivot = arr[lo]
    i = lo
    j = hi
    esq = 1
    while i < j:
        if esq:
            if pivot >= arr[j]:
                arr[i], arr[j] = arr[j], arr[i]
                nswaps+=1
                i = i + 1
                esq = 0
            else:
                j = j-1
        else:
            if pivot < arr[i]:
                arr[i], arr[j] = arr[j], arr[i]
                nswaps+=1
                j = j - 1
                esq = 1
            else:
                i = i+1
    k=i
    arr[k] = pivot
    return k

def hoareMedian(arr, lo, hi):
    global nswaps
    med = math.floor((hi+lo)/2)
    if arr[hi] < arr[med]:
        arr[hi], arr[med] = arr[med], arr[hi]
        nswaps+=1
    if arr[hi] < arr[lo]:
        arr[hi], arr[lo] = arr[lo], arr[hi]
        nswaps+=1
    if arr[med] > arr[lo]:
        arr[lo], arr[med] = arr[med], arr[lo]
        nswaps+=1
    return hoare(arr, lo, hi)

def quicksort(arr, lo, hi):
    global nrec
    if lo < hi:
        p = hoareMedian(arr, lo, hi)
        quicksort(arr, lo, p - 1)
        nrec+=1
        quicksort(arr, p + 1, hi)
        nrec+=1