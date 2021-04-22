import hash
import trie
import csv
import time

file = "rating.csv"
t0 = time.process_time()
with open(file, newline='') as csvfile:
    spamreader = csv.reader(csvfile)
    for row in spamreader:
        # print(row)
        pass
print(time.process_time()-t0)