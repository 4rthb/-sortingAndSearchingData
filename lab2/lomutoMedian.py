import math

def lomuto(arr, lo, hi):
    pivot = arr[hi]
    i = lo
    for j in range(lo,hi):
        if arr[j] <= pivot:
            arr[i], arr[j] = arr[j], arr[i] #swap_arr(arr, i, j)
            i = i + 1
    arr[i], arr[hi] = arr[hi], arr[i] #swap_arr(arr, i+1, hi)
    return i

def lomutoMedian(arr, lo, hi):
    med = math.floor((hi+lo)/2)
    if arr[lo] > arr[med] :
        arr[lo], arr[med] = arr[med], arr[lo] #swap_arr(arr, lo, med)
    if arr[lo] > arr[hi] :
        arr[lo], arr[hi] = arr[hi], arr[lo] #swap_arr(arr, hi, lo)
    if arr[med] < arr[hi] :
        arr[hi], arr[med] = arr[med], arr[hi] #swap_arr(arr, med, hi)
    return lomuto(arr, lo, hi)

def quicksort(arr, lo, hi):
    if lo < hi:
        p = lomutoMedian(arr, lo, hi)
        quicksort(arr, lo, p - 1)           #esquerda
        quicksort(arr, p + 1, hi)           #direita