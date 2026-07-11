def eh_primo(num):
 
  
   if num<=1:
        return False
    

   else:
    i=2
    while i<num:
        if num % i == 0 :
            return False
        i += 1
    return True




#programa principal
num=int(input("Digite um numero inteir e maior que 1: "))

if eh_primo(num): 
     print(" o numero eh primo",num)
else :
     print("o numero nao eh primo",num)
