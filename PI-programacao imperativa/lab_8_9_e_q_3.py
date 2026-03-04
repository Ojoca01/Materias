def contem_elemento(lista,elemento):
    j=1
    lista=[j]*qnt
    while j<=qnt:
        lista[j]=input(f"Digite o elemento {j} desta lista: ")
        j +=1


    i=0
    while i<len(lista):
        if lista[i]== elemento:
            return True
        i += 1
    return False

#Programa principal

#entrada da lista
qnt=int(input("Digite a quantidade de elementos desta lista: "))

# entrada do elemento

elemento = int(input("Digite o numero a ser procurado"))

if contem_elemento(lista,elemento):
    print("o numero esta contido na lista: ")
else:
    print("o numero nao esta contido na lista: ")
