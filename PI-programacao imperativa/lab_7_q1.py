# primeira questão / Hora Trabalho#

#função para calcular a area de um triangulo

def areaTriangulo(base,altura):
    area=(base*altura)/2
    return area

#programa principal
b=0
h=0

print("para calcular a area digie dois valorer inteiros e positivos, maiores que zero")
while b<=0.0:
    b=float(input("entre com o valor da base em metros:"))
while h<=0.0:
    h=float(input("entre com o valor da altura em metros:"))
s=areaTriangulo(b,h)
print("O valor da area eh=",s)