agenda1 = {"Ian":"1234-5678", "Pedro":
"9999-9999","Ana": "8765-4321","Marina":
"8877-7788"}
agenda2 = {"Ian":"1234-5678", "Pedro":
"9999-9999","Ana": "8765-4321","Marina":
"8877-7788"}
agenda3 = {"Ian":"1234-5678", "Pedro":
"9999-9999","Ana": "8765-4321","Marina":
"8877-7788"}

fone = agenda1["Pedro"]
print(fone)

dicionariovazio=dict()
dicionario2=dict()
dicionariovazio ["um"] = "one"
print (dicionariovazio)
{"um": "one"}
dicionariovazio ["dois"] = "two"
print (dicionariovazio)

tamanho_do_dicionario=len(dicionariovazio)

print (dicionario2)

#dict()
#in
#del

def histograma(str):
    dicionario = dict()
    for c in str:
        if c not in dicionario:
            dicionario[c] = 1
        else:
            dicionario[c] += 1
    
    return dicionario


def print_hist(h):
    for c in h:
        print (c, h[c])


h = histograma("parrot")

print_hist(h) 


for chave in agenda3:
     agenda1["chave"] = agenda3["chave"]
     print(agenda1)
     
     
def histograma(str):
    dicionario = dict()
    for c in str:
        if c not in dicionario:
            dicionario[c] = 1
        else:
            dicionario[c] += 1
    
    return dicionario


def print_hist(str):
    for c in str:
        print (c, str[c])



str=input("digite uma string: ")
print("\n\n")

str2=input("digite outra uma string: ")
print("\n\n")

dicionario=histograma(str)
h = histograma(str2)


print(dicionario)

print("\n\n")

print_hist(h) 



agenda2 = {"Ian":"1234-5678", "Pedro":
"9999-9999","Ana": "8765-4321","Marina":
"8877-7788"}

agenda1 = {"renan":"1234-5678", "joao":
"9999-9999","carlos": "8765-4321",}

for chave in agenda2:
     agenda2["Ian"] = agenda1["joao"]

print("\n\n")

print(agenda2)

print("\n\n")

print(agenda1)