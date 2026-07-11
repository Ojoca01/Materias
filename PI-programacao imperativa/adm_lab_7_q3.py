def soma_impares_while(limite):
    soma=0
    i=1
    while i<=limite:
        if i % 2 != 0:
            soma +=i
        i+=1
    return soma

limite=int(input("Digite o limite superior:"))
print("obs:. o limite inferior esta pre-estabelecido como 1")
saida= soma_impares_while(limite)
print("A soma eh: ",saida)
