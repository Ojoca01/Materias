# PI_Lab10 - Dicionários


# ----------- Hora-Trabalho_Aula18 -----------
print("\n=== Hora-Trabalho_Aula18 (usando while) ===")
dicionario = {}
indice = 0
comprimento = int(input("Entre com o comprimento do dicionário: "))

while indice < comprimento:
    chave = input("Entre com a chave: ")
    valor = input("Entre com o valor: ")
    dicionario[chave] = valor
    indice += 1

print("Dicionário criado:", dicionario)


# ----------- Alterando para laço for -----------
print("\n=== Versão com laço for ===")
dicionario_for = {}
comprimento = int(input("Entre com o comprimento do dicionário: "))

for i in range(comprimento):
    chave = input("Entre com a chave: ")
    valor = input("Entre com o valor: ")
    dicionario_for[chave] = valor

print("Dicionário criado com for:", dicionario_for)


# ----------- Criando agenda1 com 6 itens -----------
dicionario_for = {}
comprimento = int(input("Entre com o comprimento do dicionário: "))
agenda_vazia={}
for i in range(comprimento):
    chave = input("Entre com a chave: ")
    valor = input("Entre com o valor: ")
    agenda_vazia[chave] = valor

print("Dicionário criado com for:", agenda_vazia)

#============ ou ==================
print("\n=== Criando agenda1 ===")
agenda1 = {
    "Ana": "1111-1111",
    "Bruno": "2222-2222",
    "Carla": "3333-3333",
    "Daniel": "4444-4444",
    "Eduarda": "5555-5555",
    "Felipe": "6666-6666"
}
print("\nAgenda1:", agenda1)



# ----------- Adicionando itens -----------
print("\n=== Adicionando novo item ===")
agenda1["Gustavo"] = "7777-7777"
print("Agenda1 após adição:")
print("",agenda1)
print("Quantidade de itens:", len(agenda1))

nome_verificar = "Carla"
print(f"O contato '{nome_verificar}' está na agenda?", nome_verificar in agenda1)


# ----------- Removendo itens -----------
print("\n=== Removendo item ===")
remover = "Ana"
if remover in agenda1:
    del agenda1[remover]
print("\nAgenda1 após remoção:")
print(" : ",agenda1)


# ----------- Laços em dicionários -----------
print("\n=== Imprimindo chaves e valores da agenda1 ===")
for chave in agenda1:
    print("Chave: ", chave)
    valor=agenda1[chave]
    print("valor: ", valor)


# ----------- Junção de dicionários -----------
print("\n=== Criando agenda2 e juntando em agenda1 ===")
agenda2 = {
    "Hugo": "8888-8888",
    "Isabela": "9999-9999",
    "João": "1010-1010",
    "Karen": "1212-1212"
}

# Usando laço for para juntar
for chave in agenda2:
    agenda1[chave] = agenda2[chave]

print("\nAgenda1 após junção com agenda2:")
print("",agenda1)

