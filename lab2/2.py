arr = []
arr2 = []
arr.append(int(input())) # leio o n
n=arr[0]
while arr[-1] and not((len(arr)-1)%n!=0 or len(arr)!=1): # enquanto n lemos o 0
    arr.append(int(input())) # le input
arr.pop(-1) # remove o n e o 0 do vetor
arr.pop(0)
i=0
swap=0
while i!=len(arr): # percorre o vetor, numero a numero, para comparar valores
    if i%n==0: # quando chegar no fim da sequencia(sempre vai ser nk)
        arr2.append(swap) # adiciona swap no vetor de swap
        swap=0
    j=i+1 # checa parte superior do numero
    while j%n!=0 and j!=len(arr): # enquanto n chegarmos no fim fim da sequencia ou fim do vetor(caso da sequencia ser < n)
        if arr[i]>arr[j]:
            swap += 1 # se achar um numero à direita menor
        j+=1
    j-=n # vai pro primeiro termo da sequencia
    while j%n != 0: # caso a sequencia analisada antes for incompleta, precisa disso
        j+=1
    k=i-1 # checa parte inferior da sequencia
    while k != (j-1) and k!=-1: #v enquanto n chega no primeiro da sequencia ou sai do vetor
        if arr[i]<arr[k]:
            swap += 1 # se achar um numero à esquerda maior
        k-=1
    if i==len(arr)-1: # quando chega no fim do vetor faz isso pra salvar swap, dessa forma da certo com sequencias incompletas
        arr2.append(swap)
    i+=1
print(arr,arr2)