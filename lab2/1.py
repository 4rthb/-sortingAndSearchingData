import time
import lomutoMedian
import lomutoRandom
import hoareMedian
import hoareRandom

fname = "entrada.txt"
array = []
times = []

entrada = open(fname,"r")
files = [open("saida-mediana3-hoare.txt", "w"), open("saida-mediana3-lomuto.txt", "w"), open("saida-aleatorio-hoare.txt", "w"), open("saida-aleatorio-lomuto.txt", "w")]

n = int(entrada.readline())      # n = numero de casos
while n:
    m = entrada.readline(1)     # m = numero de elementos do array
    array.append(entrada.readline())
    array[-1] = array[-1].split(" ")
    array[-1].pop(0)
    array[-1] = [ int(x) for x in array[-1] ]
    times.append(0)
    n-=1
for ind, arr in enumerate(array):  #hoare median
    times[ind]=time.process_time()
    hoareRandom.quicksort(array[ind],0,len(array[ind])-1)
    times[ind] = time.process_time() - times[ind]
    print(array[ind]==sorted(arr))
    print(array[ind])
    print(sorted(arr))
print(times)


