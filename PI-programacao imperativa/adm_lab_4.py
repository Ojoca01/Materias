#funcoes locais e globais
import math
#hora trabalho/questao 1
m1=0
m2=0
def comodo():
    global pot,m1,m2
    pot=(m1*m2)*18
    
#programa principal
m1=float(input("digite a primeira dimensao do seu comodo: "))
m2=float(input("digite a segunda dimensao do seu comodo: "))
comodo()
print("Gasto em energia no comodo: ",pot)

#questao 2
r=0
def circulo():
    global per,r
    per=2*math.pi*r
   


r=float(input("Digite o valor do raio: "))
circulo()
print("Raio: ",r)
print("perimetro: ",per)

#questao 3
a=0
b=0
c=0
def semi_area_do_triangulo(a,b,c):
    s=(a+b+c)/2
    area= math.sqrt( s*(s-a)*(s-b)*(s-c)    )
    return s,area

#programa principal
a=int(input("digite o valor do primeiro lado do triangulo: "))
b=int(input("digite o valor do segundo lado do triangulo: "))
c=int(input("digite o valor do terceiro lado do triangulo: "))
s,area=semi_area_do_triangulo(a,b,c)
print("VALORES: ")
print("A: ",a)
print("B: ",b)
print("C: ",c)

print("Semiperimetro:",s)
print("Area: ",area)

#questao 4
#igual  a 3 so que global 
a=0
b=0
c=0
def semi_area_do_trianguloglobal():
    global a,b,c,s,area
    s=(a+b+c)/2
    area= math.sqrt( s*(s-a)*(s-b)*(s-c)    )
    

#programa principal
a=int(input("digite o valor do primeiro lado do triangulo: "))
b=int(input("digite o valor do segundo lado do triangulo: "))
c=int(input("digite o valor do terceiro lado do triangulo: "))
semi_area_do_trianguloglobal()

print("VALORES: ")
print("A: ",a)
print("B: ",b)
print("C: ",c)

print("Semiperimetro:",s)
print("Area: ",area)
