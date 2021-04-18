import hash

tables = [[],[],[],[]]
tamanho = [int(1.5*10000),int(1.5*10000),int(1.5*10000),int(1.5*10000)]
inputF = [open('consultas.txt','r'),open('nomes_10000.txt','r')]
nomes = [['  Encontrados:',],['  Não encontrados:',]]
verif = []
ppl = [[],[]]

for tab, tam in zip(tables,tamanho):
    for _ in range(tam):
        tab.append((_,'\0'))

names, search = inputF[1].read(), inputF[0].read()
names = names.split('\n')
search = search.split('\n')
names.remove('')

colisoes = 0
for name in names:
    hashes = [hash.hornerHash(name, len(tables[0])),hash.hornerHash(name, len(tables[1])),hash.fullNameHash(name, len(tables[2])),
              hash.fullNameHash(name, len(tables[3]))]
    colisoes += hash.insert_eabq(hashes[0],name,tables[0],0,0)
    hash.insert_eabq(hashes[2],name,tables[2],0,0)
    hash.insert_chain(hashes[1],name,tables[1])
    hash.insert_chain(hashes[3],name,tables[3])
print("Nomes inseridos!")

for name in search:
    returns = [hash.consulta_eabqH(name, tables[0]), hash.consulta_eabqFN(name, tables[2]), hash.consulta_chainH(name, tables[1]),
               hash.consulta_chainFN(name, tables[3])]
    inside = returns[0]
    if inside != -1:
        print(name, "se encontra na tabela, número de acessos ou entradas verificadas: {}".format(returns[0]))
        print(name, "se encontra na tabela, número de acessos ou entradas verificadas: {}".format(returns[1]))
        print(name, "se encontra na tabela, número de acessos ou entradas verificadas: {}".format(returns[2]))
        print(name, "se encontra na tabela, número de acessos ou entradas verificadas: {}".format(returns[3]))
        nomes[0].append(name)
        verif.append(returns[0])
    else:
        print(name, "não se encontra na tabela")
        nomes[1].append(name)
    print("-------------------------------------------------------------------------------NEXT")

print("Taxa de ocupação das tabelas com eabq - Horner: {}, FullName: {}".format((len(names)/len(tables[0])),((len(names)/len(tables[2])))))
print("Taxa de ocupação das tabelas com chainning - Horner: {}, FullName: {}\n".format((len(names)/len(tables[1])),((len(names)/len(tables[3])))))

for i in range(2):
    for column in nomes[i]:
        print(column)
    print("Tamanho da lista: " , len(nomes[i])-1)
    print("----------------")

mean = sum(verif)/len(verif)
mx = max(verif)
mn = min(verif)

for pessoa, numero in zip(nomes[0][1:],verif):
    if numero == mx:
        ppl[1].append(pessoa)

for pessoa, numero in zip(nomes[0][1:],verif):
    if numero == mn:
        ppl[0].append(pessoa)

print("Sobre entradas da tabela hash verificadas:\nMédia: {}\nMaior(es): {} com {}\nMenor(es): {} com {}".format(mean, ppl[1], mx,
                                                                                                 ppl[0], mn))

print("\nNúmero de colisões ao montar a tabela: {}".format(colisoes))