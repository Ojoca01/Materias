#entrada = input("Digite quatro números separados por espaço: ")
#a , b, c, d = entrada.split()
#a = int(a)
#b = int(b)
#c = int(c)
#d = int(d)

#print("media:", int(a + b + c + d)/4)

#entradacelcius=input("digite a temperatura em graus celcius: ")
#temp_celcius=int(entradacelcius)
#temp_farenheit= (temp_celcius*1.8)+32
#print(f"transformação celcius:{temp_celcius} farenheit:{temp_farenheit}")


#import math  # ← não esqueça de importar para usar sqrt()

#entradabhaskara = input("Digite os valores de A, B e C respectivamente: ")
#a, b, c = entradabhaskara.split()

#a = int(a)
#b = int(b)
#c = int(c)

# Cálculo do discriminante (delta)
#delta = b**2 - 4*a*c

# Verificação do delta
#if delta < 0:
#    print("A equação não possui raízes reais.")
#elif delta == 0:
 #   x = -b / (2*a)
 #   print("A equação possui uma raiz real:", x)
#else:
#    raiz_delta = math.sqrt(delta)
#    x1 = (-b + raiz_delta) / (2*a)
 #   x2 = (-b - raiz_delta) / (2*a)
 #   print("As raízes da equação são:", x1, "e", x2)

  #import math

# Entrada dos coeficientes
  #a = float(input("Digite o valor de a: "))
  #b = float(input("Digite o valor de b: "))
  #c = float(input("Digite o valor de c: "))

# Cálculo do discriminante (delta)
  #delta = b**2 - 4*a*c

# Verificação do delta
  #if delta < 0:
   #   print("A equação não possui raízes reais.")
  #elif delta == 0:
   #   x = -b / (2*a)
   #   print("A equação possui uma raiz real:", x)
  #else:
   #   raiz_delta = math.sqrt(delta)
   #   x1 = (-b + raiz_delta) / (2*a)
   #   x2 = (-b - raiz_delta) / (2*a)
   #   print("As raízes da equação são:", x1, "e", x2)

entrada = input("Digite suas quatro notas respectivamente separados por virgula: ")
a , b, c, d = entrada.split(",")
a = float(a)
b = float(b)
c = float(c)
d = float(d)


print("primeira nota:",a)
print("segunda nota:",b)
print("terceira nota:",c)
print("quarta nota:",d)
media=float((a + b + c + d)/4)
print(f"media:{media:.3f}")
#print(format(media, ".2f"))
