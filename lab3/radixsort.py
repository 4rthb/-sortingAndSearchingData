'''
pega o caractere que esta na posicao sendo avaliada 
da palavra que foi entrege e retorna sua posicao no vetor contador
a=1
z=26
'''
def posicao_char(arr,d)


#organizar array
def sort(arr, lo, hi, d)
#d é a posição de onde deve partir
    #se a primeira posição for a mesma que a ultima retornar
    if hi<=lo:
        return
    #contar a frequencia dos caracteres
    for i in range(lo, hi, 1):
        cont[posicao_char(arr[i], d)+2]+=1
    #acumula as frequencias, calculando as posicoes
    for i in range(0, 26, 1):
        cont[r+1]+=cont[r]
    #colocar as palavras em seus respectivos lugares
    for i in range(lo, hi, 1):
        j = cont[posicao_char(arr[i], d)+1]  #pega a posicao da palavra
        aux[j]= arr[i]                      #coloca a palavra em seu lugar 
        cont[posicao_char(arr[i], d)]+=1     #soma para a posicao da proxima palavra
    #copia o array auxiliar para o original
    for i in range(lo, hi, 1):
        arr[i]=aux[i-lo]
    #chama a funcao para a proxima posicao de caractere
    for i in range(0, 26, 1):
        sort(arr, lo + cont[r], lo + cont[r+1]-1, d+1)

