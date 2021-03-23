import time
import lomutoMedian
import lomutoRandom
import hoareMedian
import hoareRandom

fname = "entrada.txt"
array = []
times = []
recswap = []

entrada = open(fname,"r")
ofiles = [open("saida-mediana3-hoare.txt", "w"), open("saida-mediana3-lomuto.txt", "w"), open("saida-aleatorio-hoare.txt", "w"), open("saida-aleatorio-lomuto.txt", "w")]
statfiles = [open("stats-mediana3-hoare.txt", "w"), open("stats-mediana3-lomuto.txt", "w"), open("stats-aleatorio-hoare.txt", "w"), open("stats-aleatorio-lomuto.txt", "w")]


n = int(entrada.readline())      # n = numero de casos
while n:
    m = entrada.readline(1)     # m = numero de elementos do array
    array.append(entrada.readline())
    array[-1] = array[-1].split(" ")
    array[-1].pop(0)
    array[-1] = [ int(x) for x in array[-1] ]
    times.append(0)
    recswap.append(0)
    n-=1



for ind, arr in enumerate(array):##############HOARE MEDIAN
    times[ind]=time.process_time()
    hoareMedian.quicksort(array[ind],0,len(array[ind])-1)
    times[ind] = time.process_time() - times[ind]
    recswap[ind]=[hoareMedian.nrec,hoareMedian.nswaps]
    print(array[ind]==sorted(arr))
    print(array[ind])
    print(sorted(arr))
ofiles[0].write(str(len(array)))
ofiles[0].write("\n")
for arr in array:
    ofiles[0].write(str(len(arr)))
    ofiles[0].write(" ")
    for num in arr:
        ofiles[0].write(str(num))
        ofiles[0].write(" ")
    ofiles[0].write("\n")
statfiles[0].write("Estatisticas:\nNumero de swaps por vetor\tNumero total de chamadas recursivas\tTempo de execucao\n")
for tim, rec in zip(times, recswap):
    statfiles[0].write("\t\t\t\t\t")
    statfiles[0].write(str(rec[0]))
    statfiles[0].write("\t\t\t\t\t")
    statfiles[0].write(str(rec[1]))
    statfiles[0].write("\t\t\t\t\t")
    statfiles[0].write(str(tim))
    statfiles[0].write("\n")

for ind, arr in enumerate(array):##############LOMUTO MEDIAN
    times[ind]=time.process_time()
    lomutoMedian.quicksort(array[ind],0,len(array[ind])-1)
    times[ind] = time.process_time() - times[ind]
    recswap[ind]=[lomutoMedian.nrec,lomutoMedian.nswaps]
    print(array[ind]==sorted(arr))
    print(array[ind])
    print(sorted(arr))
ofiles[1].write(str(len(array)))
ofiles[1].write("\n")
for arr in array:
    ofiles[1].write(str(len(arr)))
    ofiles[1].write(" ")
    for num in arr:
        ofiles[1].write(str(num))
        ofiles[1].write(" ")
    ofiles[1].write("\n")
statfiles[1].write("Estatisticas:\nNumero de swaps por vetor\tNumero total de chamadas recursivas\tTempo de execucao\n")
for tim, rec in zip(times, recswap):
    statfiles[1].write("\t\t\t\t\t")
    statfiles[1].write(str(rec[0]))
    statfiles[1].write("\t\t\t\t\t")
    statfiles[1].write(str(rec[1]))
    statfiles[1].write("\t\t\t\t\t")
    statfiles[1].write(str(tim))
    statfiles[1].write("\n")


for ind, arr in enumerate(array):##############HOARE RANDOM
    times[ind]=time.process_time()
    hoareRandom.quicksort(array[ind],0,len(array[ind])-1)
    times[ind] = time.process_time() - times[ind]
    recswap[ind]=[hoareRandom.nrec,hoareRandom.nswaps]
    print(array[ind]==sorted(arr))
    print(array[ind])
    print(sorted(arr))
ofiles[2].write(str(len(array)))
ofiles[2].write("\n")
for arr in array:
    ofiles[2].write(str(len(arr)))
    ofiles[2].write(" ")
    for num in arr:
        ofiles[2].write(str(num))
        ofiles[2].write(" ")
    ofiles[2].write("\n")
statfiles[2].write("Estatisticas:\nNumero de swaps por vetor\tNumero total de chamadas recursivas\tTempo de execucao\n")
for tim, rec in zip(times, recswap):
    statfiles[2].write("\t\t\t\t\t")
    statfiles[2].write(str(rec[0]))
    statfiles[2].write("\t\t\t\t\t")
    statfiles[2].write(str(rec[1]))
    statfiles[2].write("\t\t\t\t\t")
    statfiles[2].write(str(tim))
    statfiles[2].write("\n")

for ind, arr in enumerate(array):##############LOMUTO RANDOM
    times[ind]=time.process_time()
    lomutoRandom.quicksort(array[ind],0,len(array[ind])-1)
    times[ind] = time.process_time() - times[ind]
    recswap[ind]=[lomutoRandom.nrec,lomutoRandom.nswaps]
    print(array[ind]==sorted(arr))
    print(array[ind])
    print(sorted(arr))
ofiles[3].write(str(len(array)))
ofiles[3].write("\n")
for arr in array:
    ofiles[3].write(str(len(arr)))
    ofiles[3].write(" ")
    for num in arr:
        ofiles[3].write(str(num))
        ofiles[3].write(" ")
    ofiles[3].write("\n")
statfiles[3].write("Estatisticas:\nNumero de swaps por vetor\tNumero total de chamadas recursivas\tTempo de execucao\n")
for tim, rec in zip(times, recswap):
    statfiles[3].write("\t\t\t\t\t")
    statfiles[3].write(str(rec[0]))
    statfiles[3].write("\t\t\t\t\t")
    statfiles[3].write(str(rec[1]))
    statfiles[3].write("\t\t\t\t\t")
    statfiles[3].write(str(tim))
    statfiles[3].write("\n")


print(times)
print(recswap)

for file, stat in zip(ofiles, statfiles):
    file.close()
    stat.close()


