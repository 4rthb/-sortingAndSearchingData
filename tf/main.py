import hash
import trie
import csv
import time
import re

#fase 1
files = ["minirating.csv", "movie_clean.csv", "tag_clean.csv"]
buffer = []
pattern = [re.compile('user (\d*)$'), re.compile('movie ([^\n]*)$'), re.compile('tags ([^\n]*)$'), re.compile('top(\d*) ([^\n]*)$')]
tables = []
tamanho = []

for _ in range(len(files)):
    buffer.append([])
    tables.append([])
    tamanho.append([])

for file in files:
    with open(file, newline='') as csvfile:
        buffer[files.index(file)] = list(csv.reader(csvfile))
        buffer[files.index(file)].remove(buffer[files.index(file)][0])

tamanho = [int(len(buffer[0])*0.8), int(len(buffer[1])*1.5), len(buffer[2])]

for tab, tam in zip(tables,tamanho):
    for _ in range(tam):
        tab.append([_,'\0'])

for user in buffer[0]:
    hashh = hash.hashingUM(int(user[0]),tamanho[0])
    hash.insertChainUT(hashh, [user[0],user[1],user[2]], tables[0])


#fase 2
while True:
    inp = input("What do you want to do?\n(X) - Exit\n")

    if inp == "X" or inp == "x":
        break
    elif pattern[0].search(inp): #user ratings
        print(pattern[0].search(inp).group(1))
    elif pattern[1].search(inp): #movie search
        print(pattern[1].search(inp).group(1))
    elif pattern[2].search(inp): #tag search
        tags = pattern[2].search(inp).group(1)
        tags = tags.split(" ")
        tags[:] = [ tag.replace("'", "") for tag in tags ]
        print(tags)
    elif pattern[3].search(inp): #top nth from genre
        n = int(pattern[3].search(inp).group(1))
        genre = eval(pattern[3].search(inp).group(2))

        for num in range(n):
            pass
    else:
        print("Invalid command, try again.")
print("Goodbye! :)")