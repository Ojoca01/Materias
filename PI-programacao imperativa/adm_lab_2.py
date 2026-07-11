#programas principais e entrada de dados em variaveis
a=4
b=5
soma=a+b
print("",soma)

subtracao=a+b
print("",subtracao)

divisao=a/b
print("",divisao)

multiplicacao=a*b
print("",multiplicacao)

#questao 2
import math

a=int(input("digite um novo valor inteiro para a: "))
print("a: ",a)

log10a= math.log10(a)
print("log10 de a ",log10a)

alog= math.log(a)
print("a log: ",alog)

araiz= math.sqrt(a)
print("a raiz",araiz)

acos= math.cos(a)
print("a cos: ",acos)

a=1.34
afloaat= float(a)
print("a float: ",afloaat)


#questao 3
#programa principal 


a=float(input("Digite um numero real : "))
b=float(input("Digite um numero real : "))
c=float(input("Digite um numero real : "))
d=float(input("Digite um numero real : "))

media= (a+b+c+d)/4
print("Media: ",media)

#questao 4
#programa principal
celcius=float(input("Entre com o valor da temperatura em graus celcius: "))
farenheit= (1.8*celcius)+32
print("",farenheit)

#questao 5

#2x^2+4x-3

a=2
b=4
c=-3

delta=(b**2)-(4*a*c)
print("delta: ",delta)
raizdelta= math.sqrt(delta)
print("raiz de delta: ",raizdelta)
baskara1= (-b+raizdelta)/(2*a)
baskara2= (-b-raizdelta)/(2*a)

print("raiz 1:",baskara1)
print("raiz 2: ",baskara2)