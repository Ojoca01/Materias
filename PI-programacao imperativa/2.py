
# inputs e listas
#obs:. input sempre vem em formato de texto 

#input("Escreva seu email:")

#email=input("Escreva seu email:")
#nome=input("Escreva seu nome:")
#print(nome, email)

#faturamento= float (input("digite o seu faturamento: "))
#imposto = faturamento * 0.4

#print(imposto)

#listas

lista1=[1,2,3,4,5,6,7,8,9,10]
#soma de listas 
total_lista=sum(lista1)
print(total_lista)

# tamanho da lista
print(len(lista1))

#max e min
print(max(lista1))
print(min(lista1))

#posição
print(lista1[4])

#lista de prodotos
lista_produtos=["macbook","iphone","sansung","nokia","morotola","apple watch","apple watch","apple watch","apple watch","apple watch"]
#produto_procurado=input("digite o nome do produto a ser procurado: ")
#produto_procurado= produto_procurado.lower()
#print(produto_procurado in lista_produtos)

#metodos de listas

# adcicionar um item 
lista_produtos.append("apple watch")#obs:. modifica a lista original 
print(lista_produtos)


# remover um item

lista_produtos.remove("apple watch")#elimina pelo nome
print(lista_produtos)

lista_produtos.pop(0)#elimina pelo indice
print(lista_produtos)


# editar um item
precos=[10,15,25]
print(precos)

precos[0]=15000
print(precos)
# quantificar os itens repetidos de umas lista
print(lista_produtos.count("apple watch"))#conta quantas vezes um nome passado como argumento é repetido na lista

# ordenar uma lista
lista_produtos.sort(reverse=True)
print(lista_produtos)
lista_produtos.sort(reverse=False)
print(lista_produtos)

lista_produtos.sort(reverse=True)
print(lista_produtos)

precos.sort(reverse=False)
print(precos)

precos.sort(reverse=True)
print(precos)

