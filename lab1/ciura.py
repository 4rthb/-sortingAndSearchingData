import numpy as np
def conchaC(arr):
    ciu = [40423, 17965, 7984, 3548, 1577, 701, 301, 132, 57, 23, 10, 4, 1, 0]
    i=0
    while ciu[i]>len(arr)/2:
        i+=1
    while ciu[i]>0:
        sub=ciu[i]
        for st in range(sub):
            conchaCEntra(arr,st,sub)
        print("After increments of size ", sub, " the list is ", arr)
        i+=1
    return arr

def conchaCEntra(arr,st,gap):
    for i in range(st+gap, len(arr),gap):
        cur = arr[i]
        pos=i
        while pos>=gap and arr[pos-gap]>cur:
            arr[pos]=arr[pos-gap]
            pos=pos-gap
        arr[pos]=cur