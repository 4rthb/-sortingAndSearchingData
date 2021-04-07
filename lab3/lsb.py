MAXSIZE = 28

def radix_sort(arr):
        maxTam = max([len(word) for word in arr])
        for pos in range(maxTam-1, -1, -1):
                acc = [list() for _ in range(MAXSIZE)]
                for word in arr:
                        local = index(word, pos)
                        acc[local] += [word]
                arr = sum(acc, [])
        return arr

def index(word, pos):
        if pos >= len(word):
                return 0
        key = word[pos]
        if key >= 'A' and key <= 'Z':
                return ord(key) - ord('A') + 1
        return MAXSIZE-1