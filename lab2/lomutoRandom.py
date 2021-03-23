import random

def swap_arr(arr, m, n)
    chave=arr[m]
    arr[m]=arr[n]
    arr[n]=chave

def lomutoRandom(arr, lo, hi):
    swap_arr(arr,hi,random.randint(0,len(arr))
    pivot = arr[hi]
    i = lo - 1
    for j in range(lo,hi - 1):
        if arr[j] <= pivot:
            i = i + 1
            swap_arr(arr, i, j)            
    swap_arr(arr, i+1, hi)
    return i+1

def quicksort(arr, lo, hi):
    if lo < hi:
        p = lomutoRandom(arr, lo, hi)
        quicksort(arr, lo, p - 1)
        quicksort(arr, p + 1, hi)