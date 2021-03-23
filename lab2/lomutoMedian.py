def swap_arr(arr, m, n)
    chave=arr[m]
    arr[m]=arr[n]
    arr[n]=chave

def lomuto(arr, lo, hi):
    pivot = arr[hi]
    i = lo - 1
    for j in range(lo,hi - 1):
        if arr[j] <= pivot:
            i = i + 1
            swap_arr(arr, i, j)            
    swap_arr(arr, i+1, hi)
    return i+1

def lomutoMedian(arr, lo, hi):
    if arr[lo] > arr[(hi+lo)/2] :
        swap_arr(arr, lo, (hi+lo)/2)
    if arr[lo] > arr[hi] :
        swap_arr(arr, hi, lo)
    if arr[(hi+lo)/2] < arr[hi] :
        swap_arr(arr, (hi+lo)/2], hi)
    return lomuto(arr, lo, hi)

def quicksort(arr, lo, hi):
if lo < hi:
    p = lomutoMedian(arr, lo, hi)           
    quicksort(arr, lo, p - 1)           #esquerda
    quicksort(arr, p + 1, hi)           #direita