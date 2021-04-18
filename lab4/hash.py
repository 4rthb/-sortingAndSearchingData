prime1 = 127
prime2 = 7
c1 = 0.5
c2 = 0.5
'''
A funcao hornerHash une o nome e o sobrenome, 
depois percorre a string letra por letra realizando somas e 
multiplicacoes pelo metodo Horner
'''
def hornerHash(string,size):
    i = 0
    hash = 0
    string = string.replace(" ", "")
    while i < len(string):
        hash = (ord(string[i]) + prime1*hash) % size
        i+=1
    return int(hash)

'''
A funcao fullNameHash separa o nome so sobrenome, 
primeiro percorrendo letra por letra do nome realizando somas e 
multiplicacoes pelo metodo Horner. Depois percorrendo letra por 
letra do sobrenome da mesma forma
'''
def fullNameHash(string,size):
    name = string.split(' ')
    i = 0
    hash = 0
    while i < 2:
        j=0
        while j < len(name[i]):
            hash = (ord(string[j]) + prime1*hash) % size
            j+=1
        if i == 0:
            hash = (hash*prime2) % size
        i+=1
    return int(hash)

'''
A funcao insert_eabq se utiliza do metodo de resolucao de conflito Busca Quadradica 
para inserir os nomes na tabela e lidar com possiveis colisoes. 
'''
def insert_eabq(hash,name,table,i,n):

    hash = int((hash + i*(c1 + c2*i)) % len(table))
    for tuple in table:
        if tuple[0] == hash:
            if tuple[1] != '\0' and tuple[1] != name:
                n+=1
                insert_eabq(hash,name,table,i+1,n)
                break
            else:
                table.remove(tuple)
                table.append((hash,name,1))
                break
    return n

'''
A funcao incert_chain se utiliza do metodo de Encadeamento para inserir os nomes 
na tabela e lidar com possiveis colisoes
'''
def insert_chain(hash,name,table):

    for tuple in table:
        if tuple[0] == hash:
            table.remove(tuple)
            if tuple[1] == '\0':
                tuple = [tuple[0]]
            table.append(list(tuple) + [name])
            break

'''
Funcao de busca que usa a funcao hornerHash para mapeamento de string e 
metodo de resolucao de conflito Busca Quadratica
'''
def consulta_eabqH(name, table):

    hash = hornerHash(name, len(table))
    i = 0
    end = hash
    while True:
        hash = int((hash + i*(c1 + c2*i)) % len(table))
        if hash == end and i>0:
            return -1
        tuple = [ tup for tup in table if tup[0] == hash ]
        if tuple[0][1] == name:
            return i+1
        i+=1


'''
Funcao de busca que usa a funcao fullNameHash para mapeamento de string e 
metodo de resolucao de conflito Busca Quadratica
'''
def consulta_eabqFN(name, table):

    hash = fullNameHash(name, len(table))
    i = 0
    end = hash
    while True:
        hash = int((hash + i*(c1 + c2*i)) % len(table))
        if hash == end and i>0:
            return -1
        tuple = [ tup for tup in table if tup[0] == hash ]
        if tuple[0][1] == name:
            return i+1
        i+=1
'''
Funcao de busca que usa a funcao hornerHash para mapeamento de string e 
metodo do Encadeamento para a resolucao de conflito 
'''
def consulta_chainH(name, table):

    hash = hornerHash(name, len(table))
    for tup in table:
        if tup[0] == hash:
            for names in tup[1:]:
                if names == name:
                    return 1
    return -1

'''
Funcao de busca que usa a funcao fullNameHash para mapeamento de string e 
metodo do Encadeamento para a resolucao de conflito
'''
def consulta_chainFN(name, table):

    hash = fullNameHash(name, len(table))
    for tup in table:
        if tup[0] == hash:
            for names in tup[1:]:
                if names == name:
                    return 1
    return -1

