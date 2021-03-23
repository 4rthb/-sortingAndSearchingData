import math

def hoare(arr, lo, hi):
    pivot = arr[lo]
    i = lo
    j = hi
    esq = 1
    while i < j:
        if esq:
            if pivot >= arr[j]:
                arr[i], arr[j] = arr[j], arr[i] #swap_arr(arr,i,j)
                i = i + 1
                esq = 0
            else:
                j = j-1
        else:
            if pivot < arr[i]:
                arr[i], arr[j] = arr[j], arr[i] #swap_arr(arr,i,j)
                j = j - 1
                esq = 1
            else:
                i = i+1
    k=i
    arr[k] = pivot
    return k

def hoareMedian(arr, lo, hi):
    med = math.floor((hi+lo)/2)
    if arr[hi] < arr[med]:
        arr[hi], arr[med] = arr[med], arr[hi] #swap_arr(arr, hi, med)
    if arr[hi] < arr[lo]:
        arr[hi], arr[lo] = arr[lo], arr[hi] #swap_arr(arr, hi, lo)
    if arr[med] > arr[lo]:
        arr[lo], arr[med] = arr[med], arr[lo] #swap_arr(arr, med, lo)
    return hoare(arr, lo, hi)

def quicksort(arr, lo, hi):
    if lo < hi:
        p = hoareMedian(arr, lo, hi)
        quicksort(arr, lo, p - 1)       #esquerda
        quicksort(arr, p + 1, hi)       #direita