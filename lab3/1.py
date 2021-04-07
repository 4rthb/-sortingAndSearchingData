import radixsortmsb

fname = ["frankestein_clean.txt","war_and_peace_clean.txt"]
outname = ["frankestein_clean_ordenado.txt","war_and_peace_clean_ordenado.txt","frankestein_clean_stats.txt","war_and_peace_clean_stats.txt"]
ocur = [{},{}]

entrada = [open(fname[0],"r"),open(fname[1],"r")]
saida = [open(outname[0],"w"),open(outname[1],"w"),open(outname[2],"w"),open(outname[3],"w")]

f1 = entrada[0].read()
f2 = entrada[1].read()

f1 = f1.split(" ")
f2 = f2.split(" ")

for word in f1:
    if word not in ocur[0]:
        ocur[0][word] = f1.count(word)
print("First file stats analyzed!")
# for word in f2:
#     if word not in ocur[1]:
#         ocur[1][word] = f2.count(word)
# print("Second file stats analyzed!")

for word in ocur[0].items():
    saida[2].write(f"{word[0]}: {word[1]}\n")
# for word in ocur[1].items():
#     saida[3].write(f"{word[0]}: {word[1]}\n")
# print("Stats files completed!")
# print(f2)
radixsortmsb.sort(f1,0,len(f1)-1,0)
# f2.sort()
print("Files now sorted!")
'''print(f2)'''
for word in f1:
    saida[0].write("%s " % word)
# for word in f2:
#     saida[1].write("%s " % word)
# print("Sorted files completed!")

for file in entrada:
    file.close()
for file in saida:
    file.close()
print("Process completed!")

