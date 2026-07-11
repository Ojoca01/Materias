s = 0 # variável global
p = 0 # variável global

def somaprod (a, b):
    s = a + b
    p = a*b
    return s,p
print("s=", s)
print("p=", p)

# programa principal
x=3
y=5
s,p = somaprod(x,y)
print("s=", s)
print("p=", p)

# programa principal
x=s
y=p
s,p = somaprod(x,y)
print("s=", s)
print("p=", p)