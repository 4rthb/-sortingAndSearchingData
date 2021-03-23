import random

def swap_arr(arr, m, n)
    chave=arr[m]
    arr[m]=arr[n]
    arr[n]=chave

def hoareRandom(arr, lo, hi):
    swap_arr(arr,lo,random.randint(0,len(arr))
    pivot = arr[lo]
    i = lo
    j = hi
    esq = 1
    while i < f:
        if esq:
            if pivot >= arr[j]:
                swap_arr(arr,i,j)
                i = i + 1
                esq = 0
            else:
                j = j-1
        else:
            if pivot < arr[i]:
                swap_arr(arr,i,j)
                j = j - 1
                esq = 1
            else:
                i = i+1
    k=i
    arr[k] = pivot
    return k

def quicksort(arr, lo, hi):
    if lo < hi:
        p = hoareRandom(arr, lo, hi)
        quicksort(arr, lo, p - 1)
        quicksort(arr, p + 1, hi)