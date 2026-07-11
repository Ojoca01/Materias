#hora trabalho 12/primeira questao

def fib(n):
    if n==0:return 0
    if n==1:return 1
    else: return fib(n-1)+fib(n-2)

#programa principal
n=int(input("digite o indice de fibonacci a ser encontrado: "))
print("sequencia de fib: ",fib(n))

# segunda questao 
def fat(n):
    if n==0:return 1
    if n==1:return 1
    else:return n*fat(n-1)
#programa principal
n=int(input("digite o indice a ser encontrado: "))
print("fatorial : ",fat(n))

#terceira questao 
def pot(x,n):
    if n==0:return 1
    else: return n*pot(x,n-1)
#programa principal
x=int(input("digite o numero a ser elevado: "))
n=int(input("digite o numero do expoente: "))
print("fatorial : ",pot(x,n))


#quarta questao
def contagem_regressiva(n):
    if n==0:return print("FOGOOO!!!!")
    else : 
        print(" ",n)  
        contagem_regressiva(n-1)
#programa principal
n=int(input("digite o numero da contagem : "))
print("fatorial : ",contagem_regressiva(n))
