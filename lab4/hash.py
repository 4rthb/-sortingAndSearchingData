prime1 = 127
prime2 = 7
c1 = 0.5
c2 = 0.5

def hornerHash(string,size):
    i = 0
    hash = 0
    string = string.replace(" ", "")
    while i < len(string):
        hash = (ord(string[i]) + prime1*hash) % size
        i+=1
    return int(hash)

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

def insert_eabq(hash,name,table,i):

    hash = int((hash + i*(c1 + c2*i)) % len(table))
    for tuple in table:
        if tuple[0] == hash:
            if tuple[1] != '\0' and tuple[1] != name:
                insert_eabq(hash,name,table,i+1)
                break
            else:
                table.remove(tuple)
                table.append((hash,name,1))
                break

def insert_chain(hash,name,table):

    for tuple in table:
        if tuple[0] == hash:
            table.remove(tuple)
            if tuple[1] == '\0':
                tuple = [tuple[0]]
            table.append(list(tuple) + [name])
            break

def consulta_eabqH(name, table):

    hash = hornerHash(name, len(table))
    i = 0
    while i<100:
        hash = int((hash + i*(c1 + c2*i)) % len(table))
        tuple = [ tup for tup in table if tup[0] == hash ]
        if tuple[0][1] == name:
            return i+1, hash
        i+=1
    return -1, None

def consulta_eabqFN(name, table):

    hash = fullNameHash(name, len(table))
    i = 0
    while i<100:
        hash = int((hash + i*(c1 + c2*i)) % len(table))
        tuple = [ tup for tup in table if tup[0] == hash ]
        if tuple[0][1] == name:
            return i+1, hash
        i+=1
    return -1, None

def consulta_chainH(name, table):

    hash = hornerHash(name, len(table))
    for tup in table:
        if tup[0] == hash:
            for names in tup[1:]:
                if names == name:
                    return 1, hash
    return -1, None

def consulta_chainFN(name, table):

    hash = fullNameHash(name, len(table))
    for tup in table:
        if tup[0] == hash:
            for names in tup[1:]:
                if names == name:
                    return 1, hash
    return -1, None

