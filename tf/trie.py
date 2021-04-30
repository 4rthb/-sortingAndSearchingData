''' 
Estrutura: Arvore trie 
Funções:
inserir: insere novas palavras na arvore
'''


class TrieNode:
    '''um nodo numa estrutura arvore'''

    def __init__(self, char):
        # o caractere guardado no nodo
        self.char = char

        # caso o nodo seja o fim da palavra
        self.is_end = False

        # indica o id da palavra, decidido em ordem de chegada
        # (apenas quando is_end é verdade)
        self.movieId = []

        # genero do filme
        '''NÃO SEI COMO COLAR, MAS QUERO QUE RECEBA UM VETOR DE STRINGS'''
        self.gen = []

        # um dicionario para os nodos filhos
        # chaves são os caracteres, valores são nodos
        '''NÃO SEI COMO COLOCAR, MAS QUERO QUE ELES RECEBAM A CLASSE TrieNose'''
        self.children = null          # igual a char
        self.children_left = null     # menor que char
        self.children_right = null    # maior que char



class Trie(object):
    """O objeto arvore"""

    def __init__(self):
        """
        a arvore tem pelo menos o nodo raiz
        a raiz não guarda caractere 
        """
        self.root = TrieNode("")
    
    def insert(self, word, movieId):
        """Inserir uma palavra na arvore"""
        node = self.root
        
        # Loop para cada caractere na palavra
        # Checar caso haja um nodo filho contendo o carctere, criar um novo nodo filho caso não haja 
        for char in word:
            if char == node.char:                   # caso seja igual
                node = node.children[char]
            if char < node.char:                    # caso seja menor que char
                if node.children_left == null:      # caso não tenha um nodo 
                    # criar um novo nodo
                    new_node = TrieNode(char)
                    node.children_left = new_node
                    node = new_node
                else:                               # caso haja um nodo
                    #seguir a diante
                    node = node.children_left
            if char  > node.char:                   # caso seja maior que char
                if node.children_right == null:     # caso não tenha um nodo 
                    # criar um novo nodo
                    new_node = TrieNode(char)
                    node.children_right = new_node
                    node = new_node
                else:                               # caso haja um nodo
                    #seguir a diante
                    node = node.children_right

        # marcar o fim da palavra
        node.is_end = True

        node.movieId.append(movieId)

'''   VER DEPOIS

    def dfs(self, node, prefix):
        """Depth-first traversal of the trie
        
        Args:
            - node: the node to start with
            - prefix: the current prefix, for tracing a
                word while traversing the trie
        """
        if node.is_end:
            self.output.append((prefix + node.char, node.id))
        
        for child in node.children.values():
            self.dfs(child, prefix + node.char)
        
    def query(self, x):
        """Given an input (a prefix), retrieve all words stored in
        the trie with that prefix, sort the words by the number of 
        times they have been inserted
        """
        # Use a variable within the class to keep all possible outputs
        # As there can be more than one word with such prefix
        self.output = []
        node = self.root
        
        # Check if the prefix is in the trie
        for char in x:
            if char in node.children:
                node = node.children[char]
            else:
                # cannot found the prefix, return empty list
                return []
        
        # Traverse the trie to get all candidates
        self.dfs(node, x[:-1])

        # Sort the results in reverse order and return
        return self.output
'''