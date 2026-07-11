#strings basicas
#valores
#funções de conta(4 operações fundamentais)

print("Olá, mundo!")
print("30")
print("o custo fo de 1000")
print("o custo foi de",1000)
print("o custo foi de ",1000-700)
faturamento = 100
faturamento_2=1412
custo=324
lucro = faturamento-custo
nome ="lucas carlos cruz"
teve_lucro = True
margem_lucro= lucro/faturamento 
taxa= 0.4
imposto= faturamento*taxa 
print("o valor foi de ",faturamento)
print("o valor foi de ",faturamento_2)


print("a margem de lucro foi de ",margem_lucro)

print("a taxa é de ",taxa)

print("o imposto é de ",imposto)

print("estado do lucro",teve_lucro)

email="meuemail@gmail.com.br"

 
print(f"Faturamento da empresa:{faturamento},{custo},{imposto},funcionario: {nome}")

print("Faturamento da empresa:{},{},{},funcionario: {}".format(faturamento,custo,imposto,nome))

email=email.upper()
print(email)

email=email.lower()
print(email)

print(email.find("@"))

print(email.find("m"))

print(len(email))

print(email[4])

print(email[-4])

print(email[-1])

print(email[2:4])

novo_email=email.replace("@gmail.com","hotmail.com")
print(novo_email)

print(nome.capitalize())
print(nome.title())
# para saber o servidor

posicao_do_arroba=email.find("@")+1
servidor=email[posicao_do_arroba:]
primeira_parte=email[:posicao_do_arroba]
print(servidor)

primeiro_espaco=nome.find(" ")
primeiro_nome=nome[:primeiro_espaco]
segundo_nome=nome[primeiro_espaco:]
print(primeiro_nome)
print(segundo_nome)

margem_lucro2=8.75
margem_lucro2=round(margem_lucro2,2)

print(f"Faturamento da empresa:R${faturamento:.2f},R${custo:.2f},R${imposto:.2f},funcionario: {nome}, margem: {margem_lucro2:.0%}")
