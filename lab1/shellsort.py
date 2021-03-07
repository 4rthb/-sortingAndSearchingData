def concha(arr):
    sub = len(arr)//2
    while sub:
        for st in range(sub):
            conchaEntra(arr,st,sub)
        print("After increments of size ", sub, " the list is ", arr)
        sub=sub//2
    return arr

def conchaEntra(arr,st,gap):
    for i in range(st+gap, len(arr),gap):
        cur = arr[i]
        pos=i
        while pos>=gap and arr[pos-gap]>cur:
            arr[pos]=arr[pos-gap]
            pos=pos-gap
        arr[pos]=cur