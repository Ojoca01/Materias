#horatrabahlo 11
def fun_or (x):
    if x > 200 or x< 100:
        return True
    else:
        return False

def fun_com (x):
    if x > 200:
      return True
    else:
        if x < 100:
            return True
        else:
            return False

# programa principal
x = int(input("entre com o numero:"))
print("saida 1:", fun_or(x))
print("saida 2:", fun_com(x))

#primeira questão

def maiorIdade(n):
    return n>=18

#segunda e terceira questão

def maiorIdade(n):
    return n>=18

print(":",maiorIdade(24) )

print(":",maiorIdade(16) )

#quarta questão
def maiorIdade(n):
    if n>0:
        return n>=18
    else: print("o numero  inserido  nao eh positivo")



#quinta questão
print("A pessoa eh maior de idade:",maiorIdade(24) )

print("A pesssoa nao eh maior de idade:",maiorIdade(16) )

#sexta questão

def positivo(n):
    return n>0
def maiorIdade(n):
    return n>=18

print(": ",positivo(4))
print(": ",positivo(1))
print(": ",positivo(-1))

#setima questão

#programa principal 

n=int(input("digite sua idade: "))
if positivo(n) :
     if maiorIdade(n): print("A pessoa eh maior de idade",n)

     else: print("A pessoa nao eh maior de idade",n)

else : print("Esse numero nao pode ser a idade de uma pessoa:",n)