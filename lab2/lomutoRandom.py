def quicksort(arr, lo, hi):
    if lo < hi:
        p = lomutoRandom(arr, lo, hi)
        quicksort(arr, lo, p - 1)
        quicksort(arr, p + 1, hi)

def lomutoRandom(arr, lo, hi):
    pivot = arr[hi]
    i = lo
    for j in range(lo,hi):
        if arr[j] < pivot:
            #swap arr[i] with arr[j]
            i = i + 1
    #swap arr[i] with arr[hi]
    return i