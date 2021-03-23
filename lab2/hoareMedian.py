def swap_arr(arr, m, n)
    chave=arr[m]
    arr[m]=arr[n]
    arr[n]=chave

def hoare(arr, lo, hi):
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

def hoareMedian(arr, lo, hi):
    if arr[hi] < arr[(hi+lo)/2]
        swap_arr(arr, hi, (hi+lo)/2)
    if arr[hi] < arr[lo] 
        swap_arr(arr, hi, lo)
    if arr[(hi+lo)/2] > arr[lo]
        swap_arr(arr, (hi+lo)/2], lo)
    return hoare(arr, lo, hi)

def quicksort(arr, lo, hi):
    if lo < hi:
        p = hoareMedian(arr, lo, hi)
        quicksort(arr, lo, p - 1)       #esquerda
        quicksort(arr, p + 1, hi)       #direita