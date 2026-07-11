def contem_caractere(texto, caractere):
    qnt = 0
    for c in texto:
        if c == caractere:
            qnt += 1
    return qnt

# Programa principal
texto = input("Digite uma string: ")
caractere = input("Digite um caractere: ")

qnt = contem_caractere(texto, caractere)

if qnt > 0:
    print("Caractere encontrado:", caractere)
    print("Quantidade em que se repete:", qnt)
else:
    print("Caractere não encontrado, não pertence a esta palavra!")
