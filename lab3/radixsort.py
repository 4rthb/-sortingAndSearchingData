'''
pega o caractere que esta na posicao sendo avaliada 
da palavra que foi entrege e retorna sua posicao no vetor contador
a=1
z=26
'''
def posicao_char(arr, d):
    print(len(arr), arr, d)
    return ord(arr[d])-ord("A")

#organizar array
def sort(arr, lo, hi, d):
#d é a posição de onde deve partir
    cont=[]
    aux=[]
    [cont.append(0) for x in range(28)]
    [aux.append(" ") for x in range(len(arr))]
    #se a primeira posição for a mesma que a ultima retornar
    if hi<=lo:
        print("123")
        return None
    #contar a frequencia dos caracteres
    for i in range(lo, hi+1):
        cont[posicao_char(arr[i], d)+2]+=1
    #acumula as frequencias, calculando as posicoes
    for i in range(0, 27, 1):
        cont[i+1]+=cont[i]
    #colocar as palavras em seus respectivos lugares
    for i in range(lo, hi+1, 1):
        j = cont[posicao_char(arr[i], d)+1]  #pega a posicao da palavra
        aux[j]= arr[i]                      #coloca a palavra em seu lugar 
        cont[posicao_char(arr[i], d)]+=1     #soma para a posicao da proxima palavra
    #copia o array auxiliar para o original
    for i in range(lo, hi+1, 1):
        if aux[i-lo]!=" ":
            arr[i]=aux[i-lo]
    #chama a funcao para a proxima posicao de caractere
    for i in range(0, 27, 1):
        sort(arr, lo + cont[i], lo + cont[i+1]-1, d+1)

