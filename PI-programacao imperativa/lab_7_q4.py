 def soma_impares_for(limite):
    soma=0
    for i in range (1,limite+1,2):
        soma +=i
    return soma

limite=int(input("Digite o limite superior:"))
print("obs:. o limite inferior esta pre-estabelecido como 1")
saida= soma_impares_for(limite)
print("A soma eh: ",saida)