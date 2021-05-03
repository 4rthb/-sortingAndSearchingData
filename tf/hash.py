def hashingUM(n, size):
    return int(n % size)

def hashingT(tag,size):
    i = 0
    hash = 0
    tag = tag.replace(" ", "")
    while i < len(tag):
        hash = (ord(tag[i]) + 127 * hash) % size
        i += 1
    return int(hash)

def insertChainUT(hash, tuple, table):

    tag = 0
    for node in table:
        if node[0] == hash:
            oldnode = node
            node=node[:-1]
            for subnode in node[1:]:
                if subnode[0] == tuple[0]:
                    node[node.index(subnode)].append(tuple[1])
                    node[node.index(subnode)].append(tuple[2])
                    tag = 1
            if not tag:
                node.append(tuple)
            node.append('\0')
            table[table.index(oldnode)]=node
            break

def insertChainM(hash, tuple, table):

# tuple = [movieid, name, genre, avg rating, total user ratings]
# or
# tuple = [movieid, 0, 0, rating, 0](pra n precisar acessar toda hora o negocio das outras coisas)

    for node in table:
        if node[0] == hash:
            node=node[:-1]
            if len(node[1:])!=0:
                for movie in node[1:]:
                    if movie[0]==tuple[0]:
                        if movie[1]==0:
                            movie[1]=tuple[1]
                            movie[2]=tuple[2]
                        movie[3]=(movie[3]*movie[4]+tuple[1])/(movie[4]+1)
                        movie[4]+=1
            else:
                node.append([tuple])
            node.append('\0')
            break

def searchChainUM(id,table,size):

    hash = hashing(id,size)

    for node in table:
        if node[0]==hash:
            for tuple in node[1:]:
                if id == tuple[0]:
                    return tuple

def searchChainT(tag,table,size):

    hash = hashingT(tag,size)

    for node in table:
        if node[0]==hash:
            for tuple in node[1:]:
                if tag == tuple[0]:
                    return tuple

# '''
# Recebe: nome ou prefixo do filme
# Retorna: lista de generos, avaliação média e numero de avaliações
# '''
#
# #Estrutura com infos do filme
# class filme:
#
#     def __init__(self, movieId):
#         # soma total das avaliacoes
#         self.rating = []
#
#         # soma total dos users que avaliaram
#         self.tot_users= []
#
#         # media das avaliacoes
#         self.ave_rating = self.rating/self.tot_users
#
#         # id de identificacao dos filmes
#         self.movieId = movieId
#
#         # filme seguinte
#         self.next = {}
#     '''
#     tabela:
#     hash|nodo da lista|...
#     '''
#     def insert_chain(self, movieId, rating, table):
#         hash = movieId % len(table)                             # calcula o hash
#         # procurar filme na tabela
#         for tuple in table:
#             if tuple[0] == hash:                                # caso encontre a posicao
#                 if tuple[1] == None :                           # caso esteja vazio
#                     node = filme(movieId)
#                     # prenche os dados
#                     node.rating = rating
#                     node.tot_users = 1
#                     node.ave_rating = node.rating
#                     tuple[1] = node
#                 else:                                           # caso ja exista
#                     node = tuple[1]                             # recebe o nodo
#                     if node.movieId == movieId :                # caso tenha encontrado o filme
#                         #atualiza os dados
#                         node.rating = node.rating + rating
#                         node.tot_users = node.tot_users + 1
#                         node.ave_rating = node.rating / node.tot_users
#                     else:                                   # caso nao encontre
#                         node = node.next                    # segue adiante



