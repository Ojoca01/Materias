def inverter(palavra):
    return palavra[::-1]

#Programa principal 
texto=input("Entre com uma palavra para inverter:")
saida=inverter(texto)
print("palavra invertida:",saida)
