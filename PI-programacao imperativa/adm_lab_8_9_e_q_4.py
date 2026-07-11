def posicao_elem(lista,valor):
    for i  in range(len(lista)):
        if(lista[i])==valor:
            return i
        else:
            return len(lista)
        
lista=[10,20,30,40]

valor=int(input("Digite um valor: "))

posicao=posicao_elem(lista,valor)
if posicao<=len(lista):
    print("Valor encontrado: ",valor)
    print("posicao:",posicao)
else:
    print("Valor nao encontrado")