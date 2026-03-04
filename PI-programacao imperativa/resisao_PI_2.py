# ================================
# RESUMO: Uso de looping em Python
# ================================

# ================================

# WHILE

# ================================

# Executa enquanto a condição for verdadeira
# Aplicação: <= , >= , < , > , ==

print("Exemplo while:")
contador = 0
while contador <= 5:
    print(contador)
    contador += 1   # evita loop infinito

# ================================

# FOR

# ================================

# Itera sobre range, string, lista ou dicionário

print("\nExemplo for com lista:")
numeros = [1, 2, 3, 4, 5]
for numero in numeros:
    print(numero)

print("\nExemplo for com range:")
for i in range(5):   # imprime 0 a 4
    print(i)
    
# ================================

# STRINGS

# ================================

texto = "Python"

# comprimento da string
print("\nComprimento da string:", len(texto))

# percorrer string
for letra in texto:
    print(letra, end=" ")

# inversão de string
print("\nString invertida:", texto[::-1])

# verificação de string vazia
if texto == "":
    print("String vazia")
else:
    print("String não está vazia")

# busca de caracteres
if "P" in texto:
    print("Caractere encontrado!")

# ================================

# LISTAS

# ================================

qnt = int(input("\nDigite a quantidade de elementos da lista: "))

# Forma 1: lista com posições reservadas
lista = [0] * qnt
i = 0
while i < qnt:
    lista[i] = int(input(f"Digite o elemento {i+1}: "))
    i += 1
print("Lista final:", lista)

# Forma 2: lista dinâmica com append
lista = []
i = 0
while i < qnt:
    elemento = int(input(f"Digite o elemento {i+1}: "))
    lista.append(elemento)
    i += 1
print("Lista final:", lista)

# comprimento da lista
print("Tamanho da lista:", len(lista))

# percorrer lista
for item in lista:
    print("Item:", item)

# verificar se lista está vazia
if not lista:
    print("Lista vazia")
else:
    print("Lista não está vazia")

# busca de elementos em lista
if 10 in lista:
    print("10 encontrado na lista!")

# retorno de elemento e posição
for idx, valor in enumerate(lista):
    print(f"Posição {idx} -> Valor {valor}")

# ================================
# DICIONÁRIOS EM PYTHON (sem funções pré-definidas)
# ================================

# ----------------
# CRIAÇÃO DE DICIONÁRIOS
# ----------------
print("\n=== Criação manual ===")
dicionario = {}  # dicionário vazio

comprimento = int(input("Digite a quantidade de pares chave-valor: "))
for i in range(comprimento):
    chave = input("Digite a chave: ")
    valor = input("Digite o valor: ")
    dicionario[chave] = valor   # adiciona par no dicionário

print("Dicionário criado:", dicionario)

# ----------------
# ADIÇÃO DE ELEMENTOS
# ----------------
print("\n=== Adição de elementos ===")
chave_nova = input("Digite nova chave: ")
valor_novo = input("Digite novo valor: ")
dicionario[chave_nova] = valor_novo  # basta atribuir
print("Após adição:", dicionario)

# ----------------
# REMOÇÃO DE ELEMENTOS
# ----------------
print("\n=== Remoção de elementos ===")
chave_remover = input("Digite a chave a remover: ")
if chave_remover in dicionario:
    # recriando sem a chave removida
    novo_dic = {}
    for c in dicionario:
        if c != chave_remover:
            novo_dic[c] = dicionario[c]
    dicionario = novo_dic
print("Após remoção:", dicionario)

# ----------------
# IMPRESSÃO DE DICIONÁRIOS
# ----------------
print("\n=== Impressão ===")
for chave in dicionario:   # percorre chaves
    valor = dicionario[chave]
    print(chave, "->", valor)

# ----------------
# JUNÇÃO DE DICIONÁRIOS
# ----------------
print("\n=== Junção de dois dicionários ===")
dic1 = {"a": "1", "b": "2"}
dic2 = {"c": "3", "d": "4"}

dic3 = {}
# copia manual do primeiro
for chave in dic1:
    dic3[chave] = dic1[chave]
# copia manual do segundo
for chave in dic2:
    dic3[chave] = dic2[chave]

print("Resultado da junção:", dic3)
