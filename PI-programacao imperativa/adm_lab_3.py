#funcoes e programas principais
import math
#questao 1

a=float(input("Digite um numero real : "))
b=float(input("Digite um numero real : "))
c=float(input("Digite um numero real : "))
d=float(input("Digite um numero real : "))

media= (a+b+c+d)/4
print("Media: ",media)

#questao 2
#programa principal
celcius=float(input("Entre com o valor da temperatura em graus celcius: "))
farenheit= (1.8*celcius)+32
print("",farenheit)

#hora trabalho
def delta(a,b,c):
    d=(b**2)-(4*a*c)
    return d


#questao 3

#funcao principal para delta
a=int(input("Digite o valor de a : "))
b=int(input("Digite o valor de b : "))
c=int(input("Digite o valor de c : "))
d=delta(a,b,c)
print("Delta",d)


#2x^2+4x-3
#questao 4 
#programa principal da 3
raizdelta= math.sqrt(d)
print("raiz de delta: ",raizdelta)
raiz1= (-b+raizdelta)/(2*a)
raiz2= (-b-raizdelta)/(2*a)

print("raiz 1:",raiz1)
print("raiz 2: ",raiz2)


#questao 5 
r=0
def circulo(r):

    per=2*math.pi*r
    return per


r=float(input("Digite o valor do raio: "))
per=circulo(r)
print("Raio: ",r)
print("perimetro: ",per)
