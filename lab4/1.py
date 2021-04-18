import hash

tables = [[],[],[],[]]
tamanho = [int(1.3*10000),int(1.5*10000),int(1.8*10000),2*10000]
inputF = [open('consultas.txt','r'),open('nomes_10000.txt','r')]

for tab, tam in zip(tables,tamanho):
    for _ in range(tam):
        tab.append((_,'\0'))

names, search = inputF[1].read(), inputF[0].read()
names = names.split('\n')
search = search.split('\n')
names.remove('')

for name in names:
    hashes = [hash.hornerHash(name, len(tables[0])),hash.hornerHash(name, len(tables[1])),hash.fullNameHash(name, len(tables[2])),
              hash.fullNameHash(name, len(tables[3]))]
    hash.insert_eabq(hashes[0],name,tables[0],0)
    hash.insert_eabq(hashes[2],name,tables[2],0)
    hash.insert_chain(hashes[1],name,tables[1])
    hash.insert_chain(hashes[3],name,tables[3])
print("Nomes inseridos!")

for name in search:
    returns = [hash.consulta_eabqH(name, tables[0]), hash.consulta_eabqFN(name, tables[2]), hash.consulta_chainH(name, tables[1]),
               hash.consulta_chainFN(name, tables[3])]
    print(name, "se encontra na tabela? número de acessos: {} e hash: {}".format(returns[0][0], returns[0][1]))
    print(name, "se encontra na tabela? número de acessos: {} e hash: {}".format(returns[1][0], returns[1][1]))
    print(name, "se encontra na tabela? número de acessos: {} e hash: {}".format(returns[2][0], returns[2][1]))
    print(name, "se encontra na tabela? número de acessos: {} e hash: {}".format(returns[3][0], returns[3][1]))
    print("-------------------------------------------------------------------------------NEXT")