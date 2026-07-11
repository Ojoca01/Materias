def verifica_vazia(texto):
    return texto == "" #retorna true se for vazia 
#Programa principal
texto=input("Digite uma string: ")

saida=verifica_vazia(texto)
print("saida:",saida)
