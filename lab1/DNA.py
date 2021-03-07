string1 = {
  "string": "AACATGAAGG",
  "chave": None
}
string2 = {
  "string":'TTTTGGCCAA',
  "chave": None
}
string3 =  {
  "string": 'TTTGGCCAAA',
  "chave": None
}
string4 = {
  "string": 'GATCAGATTT',
  "chave": None
}
string5 = {
  "string": 'CCCGGGGGGA',
  "chave": None
}
string6 = {
  "string": "ATCGATGCAT",
  "chave": None
}

dic={
    'AACATGAAGG':0,
    'TTTTGGCCAA':0,
    'TTTGGCCAAA':0,
    'GATCAGATTT':0,
    'CCCGGGGGGA':0,
    'ATCGATGCAT':0,
}


dic["AACATGAAGG"]=concha("AACATGAAGG")
dic["TTTTGGCCAA"]=concha("TTTTGGCCAA")
dic["TTTGGCCAAA"]=concha("TTTGGCCAAA")
dic["GATCAGATTT"]=concha("GATCAGATTT")
dic["CCCGGGGGGA"]=concha("CCCGGGGGGA")
dic["ATCGATGCAT"]=concha("ATCGATGCAT")

dict(sorted(x.items(), key=lambda item: item[1]))
def concha(string):
    sub = len(string)//2
    dna=0
    while sub:
        for st in range(sub):
            dna=dna+conchaEntra(string,st,sub)
        sub=sub//2
    return dna

def conchaEntra(string,st,gap):
    for i in range(st+gap, len(string),gap):
        cur = string[i]
        pos=i
        while pos>=gap and string[pos-gap]>cur:
            string[pos]=string[pos-gap]
            pos=pos-gap
            dna+=1
        string[pos]=cur
    return dna