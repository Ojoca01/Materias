

def gerador_de_dicionario(nome,valor,pergunta,nomes_repetidos):
    dicionario=dict()
    dicionario[nome] = valor

    def funcao_nome_repetido(nome):
        i=0
        for nome in dicionario:
            i+=1
        return nomes_repetidos
   

    if nomes_repetidos>=1 in dicionario:
        print ("Este nome de usuario ja está sendo usado.")
        

        print("para que possa ser inserido no sistema digite outro!")
        
        
    else:
        for nome in dicionario:

             if valor in dicionario:
                print("\n")

                print("ja existe um valor:",valor)
                print("\n")

             elif valor not in dicionario:
                 print("\n")
                 print("este usuario nao tem valor!")
                 

                 print("deseja inserir um novo valor?")
                 

                 pergunta=input("sim ou não?: ")
                 if pergunta == "sim":
                     print("\n")
                     print("Usuario: ",nome)
                     novo_valor=input("Digite um novo valor: ")
                     dicionario[nome]=novo_valor
                     return dicionario
                 else :
                    return dicionario
             else:
                 return dicionario

pergunta=0
valor=0
nomes_repetidos=0
nome=input("digite um nome de usuario: ")
dicionario=gerador_de_dicionario(nome,valor,pergunta,nomes_repetidos)
print("\n")
print("Lista de Usuarios:")
print(dicionario)

# função de printar bonitnho
