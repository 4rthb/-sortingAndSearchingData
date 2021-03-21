def quicksort(arr, lo, hi):
    if lo < hi:
        p = hoareMedian(arr, lo, hi)
        quicksort(arr, lo, p)
        quicksort(arr, p + 1, hi)

def hoareMedian(arr, lo, hi):
    pivot = arr[ floor((hi + lo) / 2) ]
    i = lo - 1
    j = hi + 1
        while arr[i] < pivot:
            i = i + 1
        while arr[j] > pivot:
            j = j - 1
        if i ≥ j:
            return j
        #swap arr[i] with arr[j]